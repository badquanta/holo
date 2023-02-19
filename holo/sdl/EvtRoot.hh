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
#include <holo/sdl/EvtKeyCode.hh>
#include <holo/sdl/EvtMouse.hh>
#include <holo/sdl/EvtWin.hh>
namespace holo {
  /** \brief Breaks out SDL_Event(s) into their major sub-types.
   * \todo unit test
   * \ingroup sdl  */
  class SdlEvtRoot : public SdlEvtTypeSwitch {
    public:
      /** SDL_QUIT */
      shared_ptr<SdlEvt> const          Quit          = make_shared<SdlEvt>();
      /** All of the APP events (low mem, background, foreground, etc.)*/
      shared_ptr<SdlEvt> const          App           = make_shared<SdlEvt>();
      /** Locale Changed event */
      shared_ptr<SdlEvt> const          LocaleChanged = make_shared<SdlEvt>();
      /** All display events. \todo specialized Display Events handler */
      shared_ptr<SdlEvt> const          Display       = make_shared<SdlEvt>();
      /** All syswm events, no specialized handler. */
      shared_ptr<SdlEvt> const          SysWm         = make_shared<SdlEvt>();
      /** All window-related events. */
      shared_ptr<SdlEvtWin> const       Window = make_shared<SdlEvtWin>();
      /** All key up/down events. */
      shared_ptr<SdlKeyCodeEvt> const   Key    = make_shared<SdlKeyCodeEvt>();
      /** All text events (editing/input.) */
      shared_ptr<SdlEvt> const          Text   = make_shared<SdlEvt>();
      /** Keymap changed event. */
      shared_ptr<SdlEvt> const          KeymapChanged = make_shared<SdlEvt>();
      /** All mouse (button, motion, wheel) events. */
      shared_ptr<SdlEvtMouseList> const Mouse = make_shared<SdlEvtMouseList>();
      /** All joystick related events. */
      shared_ptr<SdlEvt> const          Joy   = make_shared<SdlEvt>();
      /** All game controller related events. */
      shared_ptr<SdlEvt> const          Controller = make_shared<SdlEvt>();
      /** All Finger events. \todo possibly refactor. */
      shared_ptr<SdlEvt> const          Finger     = make_shared<SdlEvt>();
      /** All Gesture events. \todo probably refactor. */
      shared_ptr<SdlEvt> const          Gesture    = make_shared<SdlEvt>();
      /** Clipboard update event.*/
      shared_ptr<SdlEvt> const          Clipboard  = make_shared<SdlEvt>();
      /** All drag & drop events. */
      shared_ptr<SdlEvt> const          Drop       = make_shared<SdlEvt>();
      /** Audio device added/removed events. */
      shared_ptr<SdlEvt> const          Audio      = make_shared<SdlEvt>();
      /** Sensor events. */
      shared_ptr<SdlEvt> const          Sensor     = make_shared<SdlEvt>();
      /** Renderer events. */
      shared_ptr<SdlEvt> const          Render     = make_shared<SdlEvt>();
      /** Construct major event type switch. */
      SdlEvtRoot();
  };
}