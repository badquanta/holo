#include "holo/sdl/EvtKeyPress.hh"
namespace holo {

  void SdlKeyPressEvt::Trigger(SDL_Event& e) const {
    assert((e.type == SDL_KEYDOWN) || (e.type == SDL_KEYUP));
    switch (e.type) {
      case SDL_KEYDOWN:
        Down->Trigger(e);
        break;
      case SDL_KEYUP:
        Up->Trigger(e);
        break;
      default:
        unreachable();
    }
    SdlEvt::Trigger(e);
  }
}