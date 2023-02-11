#pragma once
#include <holo/AbstractDispatcher.hh>
#include <SDL2/SDL_events.h>
namespace holo {
  /** \brief Basic SDL_Event dispatcher */
  class SdlEvt : public TypeDispatcher<SDL_Event&> {};
}
