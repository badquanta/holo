#include "Arch.hh"
#include "sdl/Pane.hh"

#include <boost/dll/runtime_symbol_info.hpp>
#include <boost/format.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <filesystem>

#include <numeric>
#include <stdlib.h>
namespace holo {
  weak_ptr<Arch> Arch::instance;
  vector<string> Arch::FileSearchPaths{};

  Arch::TimeoutID Arch::exitRequestedAt;
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
      RequestQuitAt(milliseconds(0));
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
  shared_ptr<Arch> Arch::Get() {
    if (instance.expired()) {
      shared_ptr<Arch> created{ new Arch() };
      instance = created;
      return created;
    }
    return instance.lock();
  }

  Arch::Arch() {
    BOOST_LOG_TRIVIAL(trace) << "Arch Startup";

    // mainRenderer = std::make_shared<SDL2pp::Renderer>(*mainWindow, -1, SDL_RENDERER_ACCELERATED);
  }

  Arch::~Arch() {
    BOOST_LOG_TRIVIAL(trace) << "Arch Shutdown";
  }

  void Arch::NextTimeouts() {
    TimeoutID              startTime = steady_clock::now();
    // Uint32              startTime = SDL_GetTicks();
    std::vector<TimeoutID> eraseLater;
    for (auto pair : timedDispatches) {
      if (pair.first <= startTime) {
        NEXT->On(pair.second);
        eraseLater.push_back(pair.first);
      }
    }
    for (TimeoutID eraseID : eraseLater) {
      timedDispatches.erase(eraseID);
    }
  }

  Arch::TimeoutID Arch::Timeout(unsigned int timeout, VoidDispatcher::CallbackFunction callback) {
    // TimeoutID const wanted = SDL_GetTicks() + timeout;
    TimeoutID wanted = steady_clock::now() + duration<int, std::milli>(timeout);
    TimeoutID actual = wanted;
    // if there is a callback already scheduled at this
    while (timedDispatches.contains(actual)) {
      actual++;
    }
    timedDispatches[actual] = callback;
    if (actual != wanted) {
      BOOST_LOG_TRIVIAL(debug) << "Arch::Timeout postponed by "
                               << actual - wanted << "ms.";
    }
    return actual;
  }
  Arch::CycleID Arch::GetCycle() {
    return cycles;
  }
  void Arch::MainLoop() {
    CancelQuit();
    while ((!exitRequested) || (exitRequestedAt > steady_clock::now())) {
      Hrc_t loopStartTime = high_resolution_clock::now();
      NEXT->Trigger();
      NEXT->Clear();

      Input->Trigger();
      Step->Trigger();
      Output->Trigger();
      NextTimeouts();

      Hrc_t   loopEndTime           = high_resolution_clock::now();
      CycleID cycleReportId         = cycles % reportEvery;
      lastCycleTicks[cycleReportId] = duration_cast<milliseconds>(loopEndTime - loopStartTime);
      if ((cycles % reportEvery) == (reportEvery - 1)) {
        milliseconds sumTicks  = std::accumulate(lastCycleTicks.begin(), lastCycleTicks.end(), milliseconds(0));
        milliseconds avgTicks  = (sumTicks / reportEvery);
        BOOST_LOG_TRIVIAL(debug) << "Loop Cycle #" << cycles
                                 << ", avg:" << avgTicks  << " ms.";
      }
      cycles++;
    }
  }
  void Arch::CancelQuit() {
    exitRequested=false;
    exitRequestedAt;
  }
  void Arch::RequestQuitAt(milliseconds at) {
    exitRequestedAt = steady_clock::now() + at;
    BOOST_LOG_TRIVIAL(debug) << "Arch::RequestQuit in " << at << " ticks.";
  }
  /** \details to quitting after 100ms delay to allow system fully deinitialize */
  void Arch::RequestQuit() {
    RequestQuitAt(milliseconds(100));
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
