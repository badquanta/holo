#pragma once
#include <holo/sdl/EvtKeyPress.hh>
namespace holo {
  /** \brief */
  class SdlKeyCodeEvt : public SdlKeyPressEvt {
    public:
      map<SDL_Keycode, SdlKeyPressEvt::sPtr> Sym;
      shared_ptr<SdlKeyPressEvt>             Code(SDL_Keycode code);
      virtual void                           Trigger(SDL_Event&) override;
      virtual void                           Off(CallbackID id) override;
  };
}