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
#include <holo/sdl/EvtKeyPress.hh>
namespace holo {
  /** \brief break out events by keycode to specific handlers
   * \todo unit test
   * \ingroup sdl */
  class SdlKeyCodeEvt : public SdlKeyPressEvt {
    public:
      /** connect SDL_Keycode values to SdlKeyPressEvt handlers.
       * \todo Perhaps this should be private or protected?
       */
      map<SDL_Keycode, SdlKeyPressEvt::sPtr> Sym;
      /** Return the SdlKeyPressEvt handler for this specific keycode.
       * \note if it does not yet exist it will be created and returned.
       */
      shared_ptr<SdlKeyPressEvt>             Code(SDL_Keycode code);
      /** dispatches to handler for each specific SDL_Keycode value if a handler
       * exists. **/
      virtual void                           Trigger(SDL_Event&) override;
      /** disconnects this callback ID from this and all specialized handlers.
       */
      virtual void                           Off(CallbackID id) override;
  };
}