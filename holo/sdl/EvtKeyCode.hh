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
  /** \brief */
  class SdlKeyCodeEvt : public SdlKeyPressEvt {
    public:
      map<SDL_Keycode, SdlKeyPressEvt::sPtr> Sym;
      shared_ptr<SdlKeyPressEvt>             Code(SDL_Keycode code);
      virtual void                           Trigger(SDL_Event&) override;
      virtual void                           Off(CallbackID id) override;
  };
}