#include "Arch.hh"
#include "Pane.hh"
#include <boost/dll/runtime_symbol_info.hpp>
#include <boost/format.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <filesystem>

#include <stdlib.h>
#include <numeric>
namespace holo {
  Arch::sPtr               Arch::instance;
  std::vector<std::string> Arch::FileSearchPaths{};

  Uint32 Arch::exitRequestedAt{ 0 };
  bool   Arch::Configure(int ac, char* av[]) {
    namespace logging = boost::log;
    namespace po      = boost::program_options;
    FileSearchPaths.push_back(boost::dll::program_location().parent_path().parent_path().string());
    FileSearchPaths.push_back((boost::filesystem::path(CMAKE_BINARY_DIR) / "share").string());
    std::string share_path =
      (boost::dll::program_location().parent_path().parent_path() / "share").string();
    if (std::filesystem::exists(share_path))
      FileSearchPaths.push_back(share_path);
    for (int i = 0; i < FileSearchPaths.size(); i++) {
      BOOST_LOG_TRIVIAL(info) << "File Search Paths[" << i << "] ='" << FileSearchPaths[i] << "'";
    }

    po::options_description desc("Allowed options");
    desc.add_options()                 //
      ("help", "produce help message") //
      ("log", po::value<int>()->default_value(2), "set log level");
    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);
    if (vm.count("help")) {
      RequestQuitAt(0);
      throw desc;
    }
    int logLvl = vm["log"].as<int>();
    switch (logLvl) {
      case 5:
        logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::trace);
        break;
      case 4:
        logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::debug);
        break;
      case 3:
        logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::info);
        break;
      case 2:
        logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::warning);
        break;
      case 1:
        logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::error);
        break;
      case 0:
        logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::fatal);
        break;
      default:
        char buffer[50];
        snprintf(buffer, 50, "Invalid log level: %d", logLvl);
        throw std::runtime_error(std::string(buffer));
    }
    BOOST_LOG_TRIVIAL(trace) << "Program::Configure()";
    return true;
  }
  Arch::sPtr Arch::Get() {
    if (!instance) {
      instance = std::shared_ptr<Arch>(new Arch());
    }
    return instance;
  }

  Arch::Arch() {
    BOOST_LOG_TRIVIAL(trace) << "Arch Startup";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // mainRenderer = std::make_shared<SDL2pp::Renderer>(*mainWindow, -1, SDL_RENDERER_ACCELERATED);
  }

  Arch::~Arch() {
    BOOST_LOG_TRIVIAL(trace) << "Arch Shutdown";
  }

  void Arch::CallTimeouts() {
    Uint32 startTime = SDL_GetTicks();
    std::vector<Uint32> eraseLater;
    for (auto pair : timedDispatches) {
      if (SDL_TICKS_PASSED(pair.first, startTime)) {
        NEXT->On(pair.second);
        eraseLater.push_back(pair.first);
      }
    }
    for (Uint32 eraseID: eraseLater){
      timedDispatches.erase(eraseID);
    }
  }

  CallbackID Arch::Timeout(unsigned int timeout, VoidDispatcher::CallbackFunction callback) {
    TimeoutID const wanted = SDL_GetTicks() + timeout;
    TimeoutID       actual = wanted;
    // if there is a callback already scheduled at this
    while (timedDispatches.contains(actual)) {
      actual++;
    }
    timedDispatches[actual] = callback;
    if (actual != wanted) {
      BOOST_LOG_TRIVIAL(debug) << "Arch::Timeout postponed by " << actual - wanted << "ms.";
    }
    return actual;
  }
  Uint64 Arch::GetCycle() {
    return cycles;
  }
  void Arch::MainLoop() {
    CancelQuit();
    while ((exitRequestedAt == 0) || (exitRequestedAt > SDL_GetTicks())) {
      Uint64    loopStartTime = SDL_GetPerformanceCounter();
      NEXT->Trigger();
      NEXT->Clear();
      Uint64    loopNextTime = SDL_GetPerformanceCounter();
      SDL_Event evt;
      prePoll->Trigger();
      while (SDL_PollEvent(&evt)) {
        events->Trigger(evt);
        Pane::Dispatch(evt);
      }
      Uint64    loopPollingTime = SDL_GetPerformanceCounter();
      preRender->Trigger();
      Pane::RenderAll();
      Uint64    loopRenderingTime = SDL_GetPerformanceCounter();
      Arch::CallTimeouts();

      Uint32 loopEndTime                             = SDL_GetTicks();
      Uint32 cycleReportId = cycles % reportEvery;
      lastCycleTicks[cycleReportId] = loopEndTime - loopStartTime;
      if ((cycles % reportEvery) == (reportEvery - 1)) {
        Uint64 sumTicks = std::accumulate(lastCycleTicks.begin(), lastCycleTicks.end(), 0);
        Uint64 avgTicks = (sumTicks/reportEvery);
        Uint64 frequency = SDL_GetPerformanceFrequency();
        BOOST_LOG_TRIVIAL(debug) << "Loop Cycle #" << cycles << ", avg:" << avgTicks*(frequency/1000.0f) << " ms.";
      }
      cycles++;
    }
  }
  void Arch::CancelQuit() {
    exitRequestedAt = 0;
  }
  void Arch::RequestQuitAt(Uint32 at) {
    exitRequestedAt = SDL_GetTicks() + at;
    BOOST_LOG_TRIVIAL(debug) << "Arch::RequestQuit in " << at << " ticks.";
  }
  /** \details to quitting after 100ms delay to allow system fully deinitialize */
  void Arch::RequestQuit() {
    RequestQuitAt(100);
  }
  /** \details Load image from disk. */
  SurfacePtr Arch::LoadImage(std::string image) {
    return SurfacePtr{ new SDL2pp::Surface(FindPath(image)) };
  }
  /** \details */
  std::string Arch::FindPath(const std::string& path) {
    return FindPath(path, FileSearchPaths);
  }
  std::string Arch::FindPath(
    const std::string& originalPath, const std::vector<std::string>& searchPaths
  ) {
    using std::filesystem::exists;
    using std::filesystem::path;
    // First just check if the string we got works:
    if (std::filesystem::exists(originalPath)) {
      return originalPath;
    } else {
      for (std::string parent : searchPaths) {
        path search = path(parent) / originalPath;
        if (exists(search)) {
          return search.string();
        }
      }
      throw std::runtime_error("Unable to find file path for: `" + originalPath + "`.");
    }
  }

}