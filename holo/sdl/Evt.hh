#pragma once
#include <holo/Evt.hh>
#include <SDL2/SDL_events.h>
#include <holo/sdl/Primitives.hh>
#include <holo/boostPrimitives.hh>
namespace holo {
  /** \brief Basic SDL_Event dispatcher */
  class SdlEvt : public EvtAbstractType<SDL_Event&> {
    public:
      /** \depreciated */
      using sPtr = shared_ptr<SdlEvt>;

      static function<void(SDL_Event&)> PrintTo(std::ostream&);
      static void PrintString(SDL_Event&);
      static string GetString(SDL_Event&);
      static string GetEventID_string(SDL_EventType);
      static Uint32 GetWindowID(SDL_Event&);
      static Uint32 GetMouseID(SDL_Event&);
  };
}
