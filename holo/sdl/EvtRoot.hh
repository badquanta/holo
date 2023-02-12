#pragma once
#include <holo/sdl/EvtWin.hh>
#include <holo/sdl/EvtKeyCode.hh>
namespace holo {
  /** \brief Breaks out SDL_Event(s) into their major sub-types.  */

  class SdlEvtRoot : public AbstractSpecialer<SDL_EventType, SDL_Event&> {
    public:
      shared_ptr<SdlEvt> const     Quit          = make_shared<SdlEvt>();
      shared_ptr<SdlEvt> const       App           = make_shared<SdlEvt>();
      shared_ptr<SdlEvt> const       LocaleChanged = make_shared<SdlEvt>();
      shared_ptr<SdlEvt> const       Display       = make_shared<SdlEvt>();
      shared_ptr<SdlEvt> const       SysWm         = make_shared<SdlEvt>();
      shared_ptr<SdlEvtWin> const Window        = make_shared<SdlEvtWin>();
      shared_ptr<SdlKeyCodeEvt> const    Key           = make_shared<SdlKeyCodeEvt>();
      shared_ptr<SdlEvt> const       Text          = make_shared<SdlEvt>();
      shared_ptr<SdlEvt> const       KeymapChanged = make_shared<SdlEvt>();
      shared_ptr<SdlEvt> const       Mouse         = make_shared<SdlEvt>();
      shared_ptr<SdlEvt> const       Joy           = make_shared<SdlEvt>();
      shared_ptr<SdlEvt> const       Controller    = make_shared<SdlEvt>();
      shared_ptr<SdlEvt> const       Finger        = make_shared<SdlEvt>();
      shared_ptr<SdlEvt> const       Gesture       = make_shared<SdlEvt>();
      shared_ptr<SdlEvt> const       Clipboard     = make_shared<SdlEvt>();
      shared_ptr<SdlEvt> const       Drop          = make_shared<SdlEvt>();
      shared_ptr<SdlEvt> const       Audio         = make_shared<SdlEvt>();
      shared_ptr<SdlEvt> const       Sensor        = make_shared<SdlEvt>();
      shared_ptr<SdlEvt> const       Render        = make_shared<SdlEvt>();
      SdlEvtRoot();
      virtual SDL_EventType ExtractSwitch(SDL_Event&) const override;
      // Trigger the event.
      // virtual void                        Trigger(SDL_Event& e) const override;
  };
}