#pragma once
#include <holo/sdl/Evt.hh>
namespace holo {

  /** \brief SDL_Event dispatcher for window events */
  class SdlWindowEvt : public AbstractSpecialer<SDL_WindowEventID, SDL_Event&> {
    public:
      std::shared_ptr<SdlEvt> const Shown          = std::make_shared<SdlEvt>();
      std::shared_ptr<SdlEvt> const Hidden         = std::make_shared<SdlEvt>();
      std::shared_ptr<SdlEvt> const Exposed        = std::make_shared<SdlEvt>();
      std::shared_ptr<SdlEvt> const Moved          = std::make_shared<SdlEvt>();
      std::shared_ptr<SdlEvt> const Resized        = std::make_shared<SdlEvt>();
      std::shared_ptr<SdlEvt> const SizeChanged    = std::make_shared<SdlEvt>();
      std::shared_ptr<SdlEvt> const Minimized      = std::make_shared<SdlEvt>();
      std::shared_ptr<SdlEvt> const Maximized      = std::make_shared<SdlEvt>();
      std::shared_ptr<SdlEvt> const Restored       = std::make_shared<SdlEvt>();
      std::shared_ptr<SdlEvt> const Enter          = std::make_shared<SdlEvt>();
      std::shared_ptr<SdlEvt> const Leave          = std::make_shared<SdlEvt>();
      std::shared_ptr<SdlEvt> const FocusGained    = std::make_shared<SdlEvt>();
      std::shared_ptr<SdlEvt> const FocusLost      = std::make_shared<SdlEvt>();
      std::shared_ptr<SdlEvt> const Close          = std::make_shared<SdlEvt>();
      std::shared_ptr<SdlEvt> const TakeFocus      = std::make_shared<SdlEvt>();
      std::shared_ptr<SdlEvt> const HitTest        = std::make_shared<SdlEvt>();
      std::shared_ptr<SdlEvt> const IccChanged     = std::make_shared<SdlEvt>();
      std::shared_ptr<SdlEvt> const DisplayChanged = std::make_shared<SdlEvt>();
      SdlWindowEvt();
      virtual SDL_WindowEventID     ExtractSwitch(SDL_Event&) const override;
  };
}