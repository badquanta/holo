#pragma once
#include "SdlEvt.hh"
namespace holo {
  /** \brief Breaks out SDL_Event(s) into their major sub-types.  */
  class SdlRootEvt : public AbstractSpecializer<SDL_EventType, SDL_Event&> {
    public:
      std::shared_ptr<SdlEvt> const       Quit          = std::make_shared<SdlEvt>();
      std::shared_ptr<SdlEvt> const       App           = std::make_shared<SdlEvt>();
      std::shared_ptr<SdlEvt> const       LocaleChanged = std::make_shared<SdlEvt>();
      std::shared_ptr<SdlEvt> const       Display       = std::make_shared<SdlEvt>();
      std::shared_ptr<SdlEvt> const       SysWm         = std::make_shared<SdlEvt>();
      std::shared_ptr<SdlWindowEvt> const Window        = std::make_shared<SdlWindowEvt>();
      std::shared_ptr<SdlKeyEvt> const    Key           = std::make_shared<SdlKeyEvt>();
      std::shared_ptr<SdlEvt> const       Text          = std::make_shared<SdlEvt>();
      std::shared_ptr<SdlEvt> const       KeymapChanged = std::make_shared<SdlEvt>();
      std::shared_ptr<SdlEvt> const       Mouse         = std::make_shared<SdlEvt>();
      std::shared_ptr<SdlEvt> const       Joy           = std::make_shared<SdlEvt>();
      std::shared_ptr<SdlEvt> const       Controller    = std::make_shared<SdlEvt>();
      std::shared_ptr<SdlEvt> const       Finger        = std::make_shared<SdlEvt>();
      std::shared_ptr<SdlEvt> const       Gesture       = std::make_shared<SdlEvt>();
      std::shared_ptr<SdlEvt> const       Clipboard     = std::make_shared<SdlEvt>();
      std::shared_ptr<SdlEvt> const       Drop          = std::make_shared<SdlEvt>();
      std::shared_ptr<SdlEvt> const       Audio         = std::make_shared<SdlEvt>();
      std::shared_ptr<SdlEvt> const       Sensor        = std::make_shared<SdlEvt>();
      std::shared_ptr<SdlEvt> const       Render        = std::make_shared<SdlEvt>();
      SdlRootEvt();
      virtual SDL_EventType ExtractSwitch(SDL_Event&) const override;
      // Trigger the event.
      //virtual void                        Trigger(SDL_Event& e) const override;
  };
}