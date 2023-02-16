#pragma once
#include <holo/sdl/EvtTypeSwitch.hh>
namespace holo {

  /** Dispatch between mouse many mice.*/
  class SdlEvtMouseButton : public SdlEvtTypeSwitch {
    public:
      shared_ptr<SdlEvt> const Up{ make_shared<SdlEvt>() };
      shared_ptr<SdlEvt> const Down{ make_shared<SdlEvt>() };
      SdlEvtMouseButton();
      // virtual SDL_EventType  ExtractSwitch(SDL_Event&e) const override;
  };
  /** Dispatch to individual MouseButtonIDs */
  class SdlEvtMouseButtonList : public SdlEvtMouseButton {
    public:
    shared_ptr<SdlEvtMouseButton> Get(Uint8 buttonID);
    map<Uint8,shared_ptr<SdlEvtMouseButton>> mapButtonIDs{};
    virtual void Trigger(SDL_Event&) override;
    virtual void Off(CallbackID) override;
  };
  /** Dispatch on any mouse related movements. */
  class SdlEvtMouse : public SdlEvtTypeSwitch {
    public:
      shared_ptr<SdlEvt> const Motion{ make_shared<SdlEvt>() };
      shared_ptr<SdlEvtMouseButtonList> const Button{ make_shared<SdlEvtMouseButtonList>() };
      shared_ptr<SdlEvt> const Wheel{ make_shared<SdlEvt>() };
      SdlEvtMouse();
      //virtual SDL_EventType ExtractSwitch(SDL_Event&) const override;
  };
  class SdlEvtMouseList : public SdlEvtMouse {
    public:
      virtual void                                Trigger(SDL_Event&) override;
      virtual void                                Off(CallbackID) override;
      static shared_ptr<SdlEvtMouse>              Get(Uint32 whichMouseID);
      static map<Uint32, shared_ptr<SdlEvtMouse>> mapMouseIDs;
  };
}