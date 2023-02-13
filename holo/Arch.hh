/**
 * \author BadQuanta
 */
#pragma once
#include <holo/holo-cfg.hh>

#include <holo/AbstractDispatcher.hh>
#include <holo/boostPrimitives.hh>
namespace holo {

  /** Program/Engine wrapper.
   * \ingroup general
   */
  class Arch {
    public:
      using sPtr    = std::shared_ptr<Arch>;
      using CliHelp = boost::program_options::options_description;
      typedef steady_clock::time_point TimeoutID;
      static std::vector<string>       FileSearchPaths;

      static shared_ptr<Arch> Get();
      static bool             Configure(int, char*[]);
      static string           FindPath(const string&);
      static string           FindPath(const string& aPath, const vector<string>& searchPaths);

      TimeoutID Timeout(unsigned int, VoidDispatcher::CallbackFunction);

    private:
      Arch();

      static weak_ptr<Arch> instance;
      static bool           exitRequested;
      static TimeoutID      exitRequestedAt;

      typedef std::map<TimeoutID, VoidDispatcher::CallbackFunction> TimeoutMap;

      TimeoutMap timedDispatches;

      void NextTimeouts();

      typedef high_resolution_clock::time_point Hrc_t;
      typedef uint64_t                          CycleID;
      CycleID                                   cycles{ 0 };
      CycleID const                             reportEvery{ 1000 };
      std::vector<milliseconds>                 lastCycleTicks{ reportEvery, milliseconds{ 0 } };

    public:
      virtual ~Arch();
      // SDL      sdl;
      // SDLTTF   ttf;
      // Renderer renderer;

      shared_ptr<VoidDispatcher> const NEXT{ make_shared<VoidDispatcher>() };
      shared_ptr<VoidDispatcher> const Input{ make_shared<VoidDispatcher>() };
      shared_ptr<VoidDispatcher> const Step{ make_shared<VoidDispatcher>() };
      shared_ptr<VoidDispatcher> const Output{ make_shared<VoidDispatcher>() };

      CycleID     GetCycle();
      void        MainLoop();
      static void RequestQuit();
      static void RequestQuitAt(milliseconds);
      void        CancelQuit();
  };
}