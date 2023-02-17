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
#include <holo/sdl/EvtTypeSwitch.hh>
namespace holo {
  SdlEvtTypeSwitch::SwitchTypeExtractor SdlEvtTypeSwitch::DefaultExtractor{
    [](SDL_Event& e) -> SDL_EventType { return (SDL_EventType)e.type; }
  };
  SdlEvtTypeSwitch::SdlEvtTypeSwitch(SwitchTypeExtractor extractor, const SpecialHandlers_t& sh)
    : EvtAbstractTypeSwitch<SDL_EventType, SDL_Event&>::EvtAbstractTypeSwitch(extractor, sh) {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }
  SdlEvtTypeSwitch::SdlEvtTypeSwitch()
    : SdlEvtTypeSwitch(DefaultExtractor, {}) {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }
  SdlEvtTypeSwitch::SdlEvtTypeSwitch(const SpecialHandlers_t& sh)
    : SdlEvtTypeSwitch(DefaultExtractor, sh) {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }
}