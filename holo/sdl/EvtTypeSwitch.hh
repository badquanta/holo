#pragma once
/** \copyright
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
  /** Provides a concrete specialization of EvtAbstractTypeSwitch for SDL_Event&
   * typed Events. \todo unit test \ingroup sdl*/
  class SdlEvtTypeSwitch
    : public EvtAbstractTypeSwitch<SDL_EventType, SDL_Event&> {
    public:
      /** Provides a static default Extractor, used if not otherwise
       * specified.*/
      static SwitchTypeExtractor DefaultExtractor;
      /** Specify an extractor to use and an initial list of special handlers.*/
      SdlEvtTypeSwitch(
        SwitchTypeExtractor extractor, const SpecialHandlers_t& sh = {}
      );
      /** Use the default extractor and a blank list of special handlers.*/
      SdlEvtTypeSwitch();
      /** Use the default extractor but specify inital handlers.*/
      SdlEvtTypeSwitch(const SpecialHandlers_t& sh);
  };
}
