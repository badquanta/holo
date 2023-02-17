#include <holo/sdl/EvtMouse.hh>
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
  SdlEvtMouseButton::SdlEvtMouseButton() {
    SpecialHandlers = SpecialHandlers_t{
      {SDL_MOUSEBUTTONDOWN,   Up},
      {  SDL_MOUSEBUTTONUP, Down}
    };
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }

  shared_ptr<SdlEvtMouseButton> SdlEvtMouseButtonList::Get(Uint8 buttonID) {
    if (!mapButtonIDs.contains(buttonID)) {
      mapButtonIDs[buttonID] = make_shared<SdlEvtMouseButton>();
    }
    return mapButtonIDs[buttonID];
  }
  void SdlEvtMouseButtonList::Trigger(SDL_Event& e) {
    SdlEvtMouseButton::Trigger(e);
    Get(e.button.button)->Trigger(e);
  }
  void SdlEvtMouseButtonList::Off(CallbackID id) {
    SdlEvtMouseButton::Off(id);
    for (auto pair : mapButtonIDs) {
      pair.second->Off(id);
    }
  }

  SdlEvtMouse::SdlEvtMouse(){
    SpecialHandlers = SpecialHandlers_t{
      {    SDL_MOUSEMOTION, Motion},
      {SDL_MOUSEBUTTONDOWN, Button},
      {  SDL_MOUSEBUTTONUP, Button},
      {     SDL_MOUSEWHEEL,  Wheel}
    };
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }

  /** SdlEvtMouseList*/
  map<Uint32, shared_ptr<SdlEvtMouse>> SdlEvtMouseList::mapMouseIDs{};
  void                                 SdlEvtMouseList::Trigger(SDL_Event& e) {
    SdlEvtMouse::Trigger(e);
    Uint32 mid = SdlEvt::GetMouseID(e);
    if (mid != 0) {
      Get(mid)->Trigger(e);
    }
  }
  void SdlEvtMouseList::Off(CallbackID id) {
    SdlEvtMouseList::Off(id);
    for (auto pair : mapMouseIDs) {
      pair.second->Off(id);
    }
  }
  shared_ptr<SdlEvtMouse> SdlEvtMouseList::Get(Uint32 whichMouseID) {
    if (!mapMouseIDs.contains(whichMouseID)) {
      mapMouseIDs[whichMouseID] = make_shared<SdlEvtMouse>();
    }
    return mapMouseIDs[whichMouseID];
  }

}