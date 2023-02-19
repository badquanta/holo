#include <holo/sdl/EvtKeyCode.hh>
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
  /**also triggers SDL_Keycode handler if it exists */
  void SdlKeyCodeEvt::Trigger(SDL_Event& e) {
    if ((e.type != SDL_KEYDOWN) && (e.type != SDL_KEYUP)) {
      return;
    }
    SDL_Keycode sym = e.key.keysym.sym;
    if (Sym.contains(sym)) {
      Sym.at(sym)->Trigger(e);
    }
    SdlKeyPressEvt::Trigger(e);
  }

  /** returns existing or created SDL_Keycode handler */
  shared_ptr<SdlKeyPressEvt> SdlKeyCodeEvt::Code(SDL_Keycode code) {
    if (!Sym.contains(code)) {
      Sym[code] = make_shared<SdlKeyPressEvt>();
    }
    return Sym[code];
  }
  /** disconnect CallbackID from this and all SDL_Keycode handlers */
  void SdlKeyCodeEvt::Off(CallbackID id) {
    SdlKeyPressEvt::Off(id);
    for (auto pair : Sym) {
      pair.second->Off(id);
    }
  }

}