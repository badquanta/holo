#pragma once
#include <holo/Evt.hh>
#include <SDL2/SDL_events.h>
#include <holo/sdl/Primitives.hh>
namespace holo {
  /** \brief Basic SDL_Event dispatcher */
  class SdlEvt : public EvtAbstractType<SDL_Event&> {
    public:
      /** \depreciated */
      using sPtr = shared_ptr<SdlEvt>;

      static Uint32 GetWindowID(SDL_Event&);
      static Uint32 GetMouseID(SDL_Event&);
  };
}
