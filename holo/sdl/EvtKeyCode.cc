#include <holo/sdl/EvtKeyCode.hh>
namespace holo {

  void SdlKeyCodeEvt::Trigger(SDL_Event& e) {
    if ((e.type != SDL_KEYDOWN) && (e.type != SDL_KEYUP)) {
      return;
    }
    SDL_Keycode sym = e.key.keysym.sym;
    if (Sym.contains(sym)) {
      Sym.at(sym)->Trigger(e);
    }
    SdlKeyPressEvt::Trigger(e);
  }

  shared_ptr<SdlKeyPressEvt> SdlKeyCodeEvt::Code(SDL_Keycode code) {
    if (!Sym.contains(code)) {
      Sym[code] = make_shared<SdlKeyPressEvt>();
    }
    return Sym[code];
  }

  void SdlKeyCodeEvt::Off(CallbackID id) {
    SdlKeyPressEvt::Off(id);
    for (auto pair : Sym) {
      pair.second->Off(id);
    }
  }

}