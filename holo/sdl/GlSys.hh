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

#include <holo/sdl/Sys.hh>
namespace holo {

  /**
   * Encapsulates SDL & OpenGL integration initialization and shutdown.
   * \note singleton.
   * \todo Refactoring: I don't like "Sys" but I am not sure what we should call
   * it instead yet. Will revisit after `Gtk` integration. \ingroup sdl-gl
   */
  class SdlGlSys {
    public:
      /** This system requires that `SdlSys` is initialized. */
      shared_ptr<SdlSys> const    sdlSys{ SdlSys::Get() };
      /** Get/initialize a reference to `SdlGlSys`.  */
      static shared_ptr<SdlGlSys> Get();

    protected:
      /** inaccessible constructor to enforce singleton. */
      SdlGlSys();
      /** singleton reference */
      static weak_ptr<SdlGlSys> instance;

    public:
      /** accessible destructor */
      ~SdlGlSys();
  };
}