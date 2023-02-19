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

  /** Distinguish between mouse button up & down events.
   * \todo unit test
   * \ingroup sdl*/
  class SdlEvtMouseButton : public SdlEvtTypeSwitch {
    public:
      /** Handler for Mouse Button Up */
      shared_ptr<SdlEvt> const Up{ make_shared<SdlEvt>() };
      /** Handler for Mouse Button Down */
      shared_ptr<SdlEvt> const Down{ make_shared<SdlEvt>() };
      /** Setup type switch */
      SdlEvtMouseButton();
  };
  /** Distinguish between different buttons on a mouse.
   * \ingroup sdl*/
  class SdlEvtMouseButtonList : public SdlEvtMouseButton {
    public:
      /** @returns an existing or created designated handler for Mouse Button
       * ID. */
      shared_ptr<SdlEvtMouseButton>             Get(Uint8 buttonID);
      /** designate individual handlers for each Mouse Button ID. */
      map<Uint8, shared_ptr<SdlEvtMouseButton>> mapButtonIDs{};
      /** Trigger individual handlers for each event. */
      virtual void                              Trigger(SDL_Event&) override;
      /** Disconnect from all buttons. */
      virtual void                              Off(CallbackID) override;
  };
  /** Distinguish between Mouse Motion, Button, and Wheel events.
   * \ingroup sdl */
  class SdlEvtMouse : public SdlEvtTypeSwitch {
    public:
      /** handle all lateral motion. */
      shared_ptr<SdlEvt> const                Motion{ make_shared<SdlEvt>() };
      /** handle all buttons. */
      shared_ptr<SdlEvtMouseButtonList> const Button{
        make_shared<SdlEvtMouseButtonList>()
      };
      /** handle all scroll wheel motion*/
      shared_ptr<SdlEvt> const Wheel{ make_shared<SdlEvt>() };
      /** construct sdlEvtTypeSwitch */
      SdlEvtMouse();
      // virtual SDL_EventType ExtractSwitch(SDL_Event&) const override;
  };
  /** Distinguish between different "Mouse" devices.
   * \note mapMouseIDs is `static` because Devices are a global/shared
   * resources. \ingroup sdl
   */
  class SdlEvtMouseList : public SdlEvtMouse {
    public:
      /** Dispatch to designated MouseID handler. */
      virtual void                                Trigger(SDL_Event&) override;
      /** Disconnect from all Mice devices. */
      virtual void                                Off(CallbackID) override;
      /** @returns a existing or created designated handler for MouseID */
      static shared_ptr<SdlEvtMouse>              Get(Uint32 whichMouseID);
      /** designates handlers for each MouseID */
      static map<Uint32, shared_ptr<SdlEvtMouse>> mapMouseIDs;
  };
}