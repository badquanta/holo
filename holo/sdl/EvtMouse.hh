#pragma once
/** \file
 *  \copyright
holo
Copyright (C) 2023  Jon David Sawyer

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/
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