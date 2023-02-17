/**
 * \author BadQuanta
 */
#pragma once
#include <holo/Evt.hh>
#include <holo/boostPrimitives.hh>
#include <holo/holo-cfg.hh>
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
      CycleID const                             reportEvery{ 10000 };
      std::vector<microseconds>                 lastCycleTicks{ reportEvery, microseconds{ 0 } };

    public:
      virtual ~Arch();
      // SDL      sdl;
      // SDLTTF   ttf;
      // Renderer renderer;
      using EvtStepMs = EvtAbstractType<milliseconds>;
      shared_ptr<EvtVoid> const NEXT{ make_shared<EvtVoid>() };
      shared_ptr<EvtVoid> const Input{ make_shared<EvtVoid>() };
      shared_ptr<EvtStepMs> const Step{ make_shared<EvtStepMs>() };
      shared_ptr<EvtVoid> const Output{ make_shared<EvtVoid>() };

      CycleID     GetCycle();
      void        MainLoop();
      static void RequestQuit();
      static void RequestQuitAt(milliseconds);
      void        CancelQuit();
  };
}