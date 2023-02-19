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
#include <holo/sdl/Evt.hh>
namespace holo {
  /** \brief Up & Down Key dispatcher
   * \todo unit test
   * \ingroup sdl */
  class SdlKeyPressEvt : public SdlEvt {
    public:
      /** \todo Remove all sPtr ??? */
      using sPtr = std::shared_ptr<SdlKeyPressEvt>;
      /** Key Up handler */
      SdlEvt::sPtr Up{ std::make_shared<SdlEvt>() };
      /** Key Down handler */
      SdlEvt::sPtr Down{ std::make_shared<SdlEvt>() };
      /** Key Down handler, only dispatches if `repeat` is 0. */
      SdlEvt::sPtr FirstDown{ std::make_shared<SdlEvt>() };
      /** Dispatch between Up, Down, & FirstDown. */
      virtual void Trigger(SDL_Event&) override;
      /** Disconnect from Up, Down, & FirstDown. */
      virtual void Off(CallbackID) override;
  };
}