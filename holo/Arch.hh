#pragma once
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
/**
 * \author BadQuanta
 */

#include <holo/Evt.hh>
#include <holo/boostPrimitives.hh>
#include <holo/holo-cfg.hh>
namespace holo {
  struct ArchCFG {
      boost::program_options::options_description            option;
      boost::program_options::options_description            hidden;
      boost::program_options::options_description            config;
      boost::program_options::positional_options_description positional;
      boost::program_options::variables_map                  values;
      string                                                 name;
      filesystem::path                                       location;
      ArchCFG();
  };

  /** Program/Engine wrapper.
   * \ingroup general
   */
  class Arch {
    public:
      using sPtr    = std::shared_ptr<Arch>;
      using CliHelp = boost::program_options::options_description;
      static ArchCFG                   CFG;
      typedef steady_clock::time_point TimeoutID;

      static shared_ptr<Arch> Get();

      static bool Configure(
        filesystem::path fromFile, const vector<string>& suffixes = {},
        const vector<string>& prefixes  = {},
        const vector<string>& absolutes = {}
      );
      static bool Configure(int, char*[]);

      TimeoutID Timeout(unsigned int, EvtVoid::CallbackFunction);
      bool      CancelTimeout(TimeoutID);

    private:
      Arch();

      static weak_ptr<Arch> instance;
      static bool           exitRequested;
      static TimeoutID      exitRequestedAt;

      typedef std::map<TimeoutID, EvtVoid::CallbackFunction> TimeoutMap;

      TimeoutMap timedDispatches;

      void NextTimeouts();

      typedef high_resolution_clock::time_point Hrc_t;
      typedef uint64_t                          CycleID;
      CycleID                                   cycles{ 0 };
      CycleID const                             reportEvery{ 1000 };
      std::vector<microseconds>                 lastCycleTicks{ reportEvery,
                                                microseconds{ 0 } };

    public:
      virtual ~Arch();
      // SDL      sdl;
      // SDLTTF   ttf;
      // Renderer renderer;
      using EvtStepMs = EvtAbstractType<milliseconds>;
      shared_ptr<EvtVoid> const   NEXT{ make_shared<EvtVoid>() };
      shared_ptr<EvtVoid> const   Input{ make_shared<EvtVoid>() };
      shared_ptr<EvtStepMs> const Step{ make_shared<EvtStepMs>() };
      shared_ptr<EvtVoid> const   Output{ make_shared<EvtVoid>() };

      CycleID     GetCycle();
      void        MainLoop();
      static void RequestQuit();
      static void RequestQuitAt(milliseconds);
      void        CancelQuit();
  };
}