#pragma once
#include "AbstractDispatcher.hh"
#include "SDL2/SDL_events.h"
namespace holo {

  /** \brief Up & Down Key dispatcher */
  class SdlKeyPressEvt : public SdlEvt {
    public:
      using sPtr = std::shared_ptr<SdlKeyPressEvt>;
      SdlEvt::sPtr Up{ std::make_shared<SdlEvt>() };
      SdlEvt::sPtr Down{ std::make_shared<SdlEvt>() };
      virtual void Trigger(SDL_Event&) const override;
  };
  /** \brief */
  class SdlKeyEvt : public SdlKeyPressEvt {
    public:
      std::map<SDL_Keycode, SdlKeyPressEvt::sPtr> Sym;
      SdlKeyPressEvt::sPtr                        Code(SDL_Keycode code);
      virtual void                                Trigger(SDL_Event&) const override;
  };

}