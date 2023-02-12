#pragma once
#include <holo/AbstractDispatcher.hh>
#include <SDL2/SDL_events.h>
#include <holo/sdl/Primitives.hh>
namespace holo {
  /** \brief Basic SDL_Event dispatcher */
  class SdlEvt : public TypeDispatcher<SDL_Event&> {
    public:
      /** \depreciated */
      using sPtr = shared_ptr<SdlEvt>;
  };
}
