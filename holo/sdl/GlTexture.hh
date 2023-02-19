#pragma once
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
#include <holo/gl/Texture.hh>
#include <holo/sdl/Primitives.hh>
namespace holo {
  /** Wraps OpenGL texture resource management.
   * \todo unit test `SdlGlTexture`
   * \ingroup sdl-gl
   */
  class SdlGlTexture : public GlTexture {
    public:
      /** Basic constructor, no data set. */
      static shared_ptr<SdlGlTexture> Create();
      /** Create a new texture from SDL Surface data.*/
      static shared_ptr<SdlGlTexture> Create(SdlSurfacePtr);
      /** Load a texture from the hard drive.*/
      static shared_ptr<SdlGlTexture> Load(
        std::string, const vector<string>& ts = {},
        const vector<string>& tp = {}, const vector<string>& ta = {}
      );
      /** Set data from SdlSurfacePtr */
      void Set(SdlSurfacePtr);
      /** Set data from SdlSurfacePtr
       * \todo IMPORTANT REFACTOR parameters into struct past by const ref for
       * brevity.
       */
      void Set(SdlSurfacePtr, GLint ws, GLint wt, GLint mf, GLint Mf);

    protected:
      /** inaccessible constructor to encourage use of static `Create()`
       * functions. */
      SdlGlTexture(GLuint);
  };
}