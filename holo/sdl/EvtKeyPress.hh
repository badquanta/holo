#pragma once
#include <holo/sdl/Evt.hh>
namespace holo {
  /** \brief Up & Down Key dispatcher */
  class SdlKeyPressEvt : public SdlEvt {
    public:
      using sPtr = std::shared_ptr<SdlKeyPressEvt>;
      SdlEvt::sPtr Up{ std::make_shared<SdlEvt>() };
      SdlEvt::sPtr Down{ std::make_shared<SdlEvt>() };
      SdlEvt::sPtr FirstDown{ std::make_shared<SdlEvt>() };
      virtual void Trigger(SDL_Event&) override;
      virtual void Off(CallbackID) override;
  };
}