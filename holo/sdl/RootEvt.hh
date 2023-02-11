#pragma once
#include "holo/sdl/Evt.hh"
namespace holo {
  /** \brief Breaks out SDL_Event(s) into their major sub-types.  */
  class SdlRootEvt : public AbstractSpecialer<SDL_EventType, SDL_Event&> {
    public:
      std::shared_ptr<SdlEvent> const       Quit          = std::make_shared<SdlEvent>();
      std::shared_ptr<SdlEvent> const       App           = std::make_shared<SdlEvent>();
      std::shared_ptr<SdlEvent> const       LocaleChanged = std::make_shared<SdlEvent>();
      std::shared_ptr<SdlEvent> const       Display       = std::make_shared<SdlEvent>();
      std::shared_ptr<SdlEvent> const       SysWm         = std::make_shared<SdlEvent>();
      std::shared_ptr<SdlWindowEvt> const Window        = std::make_shared<SdlWindowEvt>();
      std::shared_ptr<SdlKeyEvt> const    Key           = std::make_shared<SdlKeyEvt>();
      std::shared_ptr<SdlEvent> const       Text          = std::make_shared<SdlEvent>();
      std::shared_ptr<SdlEvent> const       KeymapChanged = std::make_shared<SdlEvent>();
      std::shared_ptr<SdlEvent> const       Mouse         = std::make_shared<SdlEvent>();
      std::shared_ptr<SdlEvent> const       Joy           = std::make_shared<SdlEvent>();
      std::shared_ptr<SdlEvent> const       Controller    = std::make_shared<SdlEvent>();
      std::shared_ptr<SdlEvent> const       Finger        = std::make_shared<SdlEvent>();
      std::shared_ptr<SdlEvent> const       Gesture       = std::make_shared<SdlEvent>();
      std::shared_ptr<SdlEvent> const       Clipboard     = std::make_shared<SdlEvent>();
      std::shared_ptr<SdlEvent> const       Drop          = std::make_shared<SdlEvent>();
      std::shared_ptr<SdlEvent> const       Audio         = std::make_shared<SdlEvent>();
      std::shared_ptr<SdlEvent> const       Sensor        = std::make_shared<SdlEvent>();
      std::shared_ptr<SdlEvent> const       Render        = std::make_shared<SdlEvent>();
      SdlRootEvt();
      virtual SDL_EventType ExtractSwitch(SDL_Event&) const override;
      // Trigger the event.
      //virtual void                        Trigger(SDL_Event& e) const override;
  };
}