/** \file
 * \copyright
holo
Copyright (C) 2023  Jon David Sawyer

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/
#include <boost/dll/runtime_symbol_info.hpp>
#include <boost/format.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <holo/Arch.hh>
#include <holo/ShareFiles.hh>
namespace holo {
  weak_ptr<Arch> Arch::instance;
  vector<string> Arch::FileSearchPaths{};

  Arch::TimeoutID Arch::exitRequestedAt;
  bool Arch::exitRequested{false};
  bool            Arch::Configure(int ac, char* av[]) {
    namespace logging = boost::log;
    namespace po      = boost::program_options;
    FileSearchPaths.push_back(boost::dll::program_location().parent_path().parent_path().string());
    ShareFiles::SearchAbsolutes.push_back(boost::dll::program_location().parent_path().parent_path().string());
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
      ("log", po::value<int>()->default_value(5), "set log level");
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
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
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
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;

    // mainRenderer = std::make_shared<SDL2pp::Renderer>(*mainWindow, -1, SDL_RENDERER_ACCELERATED);
  }

  Arch::~Arch() {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
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

  Arch::TimeoutID Arch::Timeout(unsigned int timeout, EvtVoid::CallbackFunction callback) {
    // TimeoutID const wanted = SDL_GetTicks() + timeout;
    TimeoutID wanted = steady_clock::now() + duration<int, std::milli>(timeout);
    TimeoutID actual = wanted;
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

  bool Arch::CancelTimeout(Arch::TimeoutID id){
    if(timedDispatches.contains(id)){
      return (timedDispatches.erase(id) > 0);
    }
    return false;
  }


  Arch::CycleID Arch::GetCycle() {
    return cycles;
  }
  void Arch::MainLoop() {
    CancelQuit();
    Hrc_t lastLoopStep = high_resolution_clock::now();
    while ((!exitRequested) || (exitRequestedAt > steady_clock::now())) {
      Hrc_t loopStartTime = high_resolution_clock::now();
      NEXT->Trigger();
      NEXT->Clear();

      Input->Trigger();
      Hrc_t thisLoopStep = high_resolution_clock::now();
      Step->Trigger(duration_cast<milliseconds>(thisLoopStep-lastLoopStep));
      lastLoopStep = thisLoopStep;
      Output->Trigger();
      NextTimeouts();

      Hrc_t   loopEndTime           = high_resolution_clock::now();
      CycleID cycleReportId         = cycles % reportEvery;
      lastCycleTicks[cycleReportId] = duration_cast<microseconds>(loopEndTime - loopStartTime);
      if ((cycles % reportEvery) == (reportEvery - 1)) {
        microseconds sumTicks =
          std::accumulate(lastCycleTicks.begin(), lastCycleTicks.end(), microseconds(0));
        milliseconds avgTicks = duration_cast<milliseconds>(sumTicks / reportEvery);
        BOOST_LOG_TRIVIAL(debug) << "Loop Cycle #" << cycles << ", avg:" << avgTicks;
      }
      cycles++;
    }
  }
  void Arch::CancelQuit() {
    exitRequested = false;
    exitRequestedAt;
  }
  void Arch::RequestQuitAt(milliseconds at) {
    exitRequestedAt = steady_clock::now() + at;
    exitRequested = true;
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
