#include "holo/sdl/EvtKeyPress.hh"
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
namespace holo {
  /**
   * \todo review use of `unreachable`, is it needed?
   */
  void SdlKeyPressEvt::Trigger(SDL_Event& e) {
    assert((e.type == SDL_KEYDOWN) || (e.type == SDL_KEYUP));
    switch (e.type) {
      case SDL_KEYDOWN:
        if (e.key.repeat == 0) {
          FirstDown->Trigger(e);
        }
        Down->Trigger(e);
        break;
      case SDL_KEYUP:
        Up->Trigger(e);
        break;
      default:
        unreachable();
    }
    SdlEvt::Trigger(e);
  }

  /** propagate off to Down, FirstDown, & Up */
  void SdlKeyPressEvt::Off(CallbackID id) {
    SdlEvt::Off(id);
    ;
    Down->Off(id);
    Up->Off(id);
  }
}