#pragma once
#include "AbstractDispatcher.hh"
#include "SDL2/SDL_events.h"
namespace holo {
  /** \brief Basic SDL_Event dispatcher */
  class SdlEvt : public BaseDispatcher<SDL_Event&> {};
  /** \brief SDL_Event dispatcher for window events */
  class SdlWindowEvt : public SdlEvt {
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
      virtual void                  Trigger(SDL_Event&) const override;
  };
  /** \brief Up & Down Key dispatcher */
  class SdlKeyPressEvt : public SdlEvt {
    public:
      SdlEvt::sPtr Up{ std::make_shared<SdlEvt>() };
      SdlEvt::sPtr Down{ std::make_shared<SdlEvt>() };
      virtual void Trigger(SDL_Event&) const override;
  };
  /** \brief */
  class SdlKeyEvt : public SdlKeyPressEvt {
    public:
      std::map<SDL_Keycode, SdlKeyPressEvt::sPtr> Sym;
      SdlKeyPressEvt::sPtr                        Key(SDL_Keycode code);
      virtual void                                Trigger(SDL_Event&) const override;
  };

}