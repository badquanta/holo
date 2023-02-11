#include "SdlEvt.hh"
#include <utility>
#include <assert.h>
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
        std::unreachable();
    }
    SdlEvent::Trigger(e);
  }

  void SdlKeyEvt::Trigger(SDL_Event& e) const {
    assert((e.type == SDL_KEYDOWN) || (e.type == SDL_KEYUP));
    SDL_Keycode sym = e.key.keysym.sym;
    if (Sym.contains(sym)) {
      Sym.at(sym)->Trigger(e);
    }
    SdlKeyPressEvt::Trigger(e);
  }

  SdlKeyPressEvt::sPtr SdlKeyEvt::Code(SDL_Keycode code) {
    if (!Sym.contains(code)) {
      Sym[code] = std::make_shared<SdlKeyPressEvt>();
    }
    return Sym[code];
  }
}