/** \file
 * \copyright
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
#include <holo/sdl/Sys.hh>
#include <holo/sdl/Window.hh>
namespace holo {
  /** Protected singleton reference.  */
  weak_ptr<SdlSys>                  SdlSys::instance;
  /** Map of WindowID values to weak references of SdlEvtRoot instances. */
  map<Uint32, weak_ptr<SdlEvtRoot>> SdlSys::mapWindowIdEvt;
  /** Protected constructor.
   * \note Always binds `arch->Input` to `this->Input` on creation.
   * \todo replace logging with unit testing.
   * */
  SdlSys::SdlSys()
    : InputID{ arch->Input->On(bind(&SdlSys::Input, this)) } {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }
  /** Public destructor.
   * \todo replace logging with unit testing. */
  SdlSys::~SdlSys() {
    arch->Input->Off(InputID);
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }
  /** Override Input handler.
   * \note uses `GetWindowID` to extract ID.
   * \note uses `mapWindowIdEvt`
   * \todo I think that `mapWindowIdEvt` and `open` are being conflated.
   * If the ID is NOT 0, it dispatches to ONLY that `SdlEvtRoot`.
   * Otherwise if the ID is 0, it dispatches to EVERY `SdlEvtRoot`.
   */
  void SdlSys::Input() {
    SDL_Event evt;
    while (SDL_PollEvent(&evt)) {
      events->Trigger(evt);
      Uint32 winId = SdlEvt::GetWindowID(evt);
      if (winId != 0) {
        // Dispatch ONLY to the specified window ID
        if (mapWindowIdEvt.contains(winId)) {
          if (!(mapWindowIdEvt.at(winId).expired())) {
            mapWindowIdEvt[winId].lock()->Trigger(evt);
          }
        }
      } else {
        // Dispatch to ALL windows
        for (auto pair : mapWindowIdEvt) {
          if (!pair.second.expired())
            pair.second.lock()->Trigger(evt);
        }
      }
    }
  }
  /** Get, or create, and return singleton.
   * @returns shared initialization.
   */
  shared_ptr<SdlSys> SdlSys::Get() {
    shared_ptr<SdlSys> loaded;
    if (instance.expired()) {
      loaded   = shared_ptr<SdlSys>(new SdlSys());
      instance = loaded;
      return loaded;
    } else {
      loaded = instance.lock();
    }

    return loaded;
  }
}