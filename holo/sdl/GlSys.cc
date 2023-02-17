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
#include <holo/sdl/GlSys.hh>

namespace holo {

  weak_ptr<SdlGlSys> SdlGlSys::instance;
  SdlGlSys::SdlGlSys() {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }

  SdlGlSys::~SdlGlSys() {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }

  shared_ptr<SdlGlSys> SdlGlSys::Get() {
    shared_ptr<SdlGlSys> loaded;
    if (instance.expired()) {
      loaded   = shared_ptr<SdlGlSys>(new SdlGlSys());
      instance = loaded;
      return loaded;
    } else {
      loaded = instance.lock();
    }

    return loaded;
  }
}