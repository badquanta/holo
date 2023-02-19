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
#include <SDL2/SDL_events.h>
#include <holo/Evt.hh>
#include <holo/boostPrimitives.hh>
#include <holo/sdl/Primitives.hh>
namespace holo {
  /** \brief Basic SDL_Event dispatcher.
   * \ingroup sdl
   * \todo unit test
   */
  class SdlEvt : public EvtAbstractType<SDL_Event&> {
    public:
      /** \deprecate \todo remove */
      using sPtr = shared_ptr<SdlEvt>;
      /** Creates a function that outputs events to a ostream */
      static function<void(SDL_Event&)> PrintTo(std::ostream&);
      /** Converts an SDL_Event to a string */
      static string                     GetString(SDL_Event&);
      /** Gets the name of the SDL_Event type field as a string*/
      static string                     GetEventID_string(SDL_EventType);
      /** Pulls out the WindowID an event may have. */
      static Uint32                     GetWindowID(SDL_Event&);
      /** Pulls out a MouseID an event may have. */
      static Uint32                     GetMouseID(SDL_Event&);
  };
}
