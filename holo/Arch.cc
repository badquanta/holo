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
#include <fstream>
#include <holo/Arch.hh>
#include <holo/ShareFiles.hh>
namespace holo {
  weak_ptr<Arch>  Arch::instance;
  Arch::TimeoutID Arch::exitRequestedAt;
  bool            Arch::exitRequested{ false };
  ArchCFG         Arch::CFG;

  ArchCFG::ArchCFG()
    : option(boost::dll::program_location().filename().string())
    , name{ boost::dll::program_location().filename().string() }
    , location{ boost::dll::program_location().parent_path().string() } {
    this->option.add_options()         //
      ("help", "produce help message") //
      ;
    this->config.add_options() //
      ("log", boost::program_options::value<int>()->default_value(5),
       "set log level") //
      ;
  }

  bool Arch::Configure(
    filesystem::path fromFile, const vector<string>& suffixes,
    const vector<string>& prefixes, const vector<string>& absolutes
  ) {
    string found{ ShareFiles::Find(fromFile, suffixes, prefixes, absolutes) };
    if (found == "") {
      return false;
    }
    std::ifstream ifs(found);
    if (!ifs) {
      throw runtime_error("Unable to open:" + found);
    }
    namespace po = boost::program_options;
    po::options_description config;
    config.add(CFG.config);
    config.add(CFG.hidden);
    po::store(po::parse_config_file(ifs, config), CFG.values);
    po::notify(CFG.values);
    return true;
  }

  bool Arch::Configure(int ac, char* av[]) {
    namespace logging = boost::log;
    namespace po      = boost::program_options;
    po::options_description cli;
    cli.add(CFG.option);
    cli.add(CFG.config);
    cli.add(CFG.hidden);
    po::store(
      po::command_line_parser(ac, av)
        .options(cli)
        .positional(CFG.positional)
        .run(),
      CFG.values
    );
    po::notify(CFG.values);
    if (CFG.values.count("help")) {
      throw cli;
    }
    int logLvl = CFG.values["log"].as<int>();
    switch (logLvl) {
      case 5:
        logging::core::get()->set_filter(
          logging::trivial::severity >= logging::trivial::trace
        );
        break;
      case 4:
        logging::core::get()->set_filter(
          logging::trivial::severity >= logging::trivial::debug
        );
        break;
      case 3:
        logging::core::get()->set_filter(
          logging::trivial::severity >= logging::trivial::info
        );
        break;
      case 2:
        logging::core::get()->set_filter(
          logging::trivial::severity >= logging::trivial::warning
        );
        break;
      case 1:
        logging::core::get()->set_filter(
          logging::trivial::severity >= logging::trivial::error
        );
        break;
      case 0:
        logging::core::get()->set_filter(
          logging::trivial::severity >= logging::trivial::fatal
        );
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

    // mainRenderer = std::make_shared<SDL2pp::Renderer>(*mainWindow, -1,
    // SDL_RENDERER_ACCELERATED);
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

  Arch::TimeoutID Arch::Timeout(
    unsigned int timeout, EvtVoid::CallbackFunction callback
  ) {
    // TimeoutID const wanted = SDL_GetTicks() + timeout;
    TimeoutID wanted = steady_clock::now() + duration<int, std::milli>(timeout);
    TimeoutID actual = wanted;
    // if there is a callback already scheduled at this
    while (timedDispatches.contains(actual)) {
      actual++;
    }
    timedDispatches[actual] = callback;
    if (actual != wanted) {
      BOOST_LOG_TRIVIAL(debug)
        << "Arch::Timeout postponed by " << actual - wanted << "ms.";
    }
    return actual;
  }

  bool Arch::CancelTimeout(Arch::TimeoutID id) {
    if (timedDispatches.contains(id)) {
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
      Step->Trigger(duration_cast<milliseconds>(thisLoopStep - lastLoopStep));
      lastLoopStep = thisLoopStep;
      Output->Trigger();
      NextTimeouts();

      Hrc_t   loopEndTime   = high_resolution_clock::now();
      CycleID cycleReportId = cycles % reportEvery;
      lastCycleTicks[cycleReportId] =
        duration_cast<microseconds>(loopEndTime - loopStartTime);
      if ((cycles % reportEvery) == (reportEvery - 1)) {
        microseconds sumTicks = std::accumulate(
          lastCycleTicks.begin(), lastCycleTicks.end(), microseconds(0)
        );
        milliseconds avgTicks =
          duration_cast<milliseconds>(sumTicks / reportEvery);
        //BOOST_LOG_TRIVIAL(debug)
        //  << "Loop Cycle #" << cycles << ", avg:" << avgTicks;
      }
      cycles++;
    }
  }
  void Arch::CancelQuit() {
    exitRequested = false;
  }
  void Arch::RequestQuitAt(milliseconds at) {
    exitRequestedAt = steady_clock::now() + at;
    exitRequested   = true;
    BOOST_LOG_TRIVIAL(debug) << "Arch::RequestQuit in " << at << " ticks.";
  }
  /** \details to quitting after 100ms delay to allow system fully deinitialize
   */
  void Arch::RequestQuit() {
    RequestQuitAt(milliseconds(100));
  }

}
