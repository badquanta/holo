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
  class SdlGlTexture : public GlTexture {
    public:
      static shared_ptr<SdlGlTexture> Create();
      /** Create a new texture from SDL Surface data.*/
      static shared_ptr<SdlGlTexture> Create(SdlSurfacePtr);
      /** Load a texture from the hard drive.*/
      static shared_ptr<SdlGlTexture> Load(std::string);
      void                            Set(SdlSurfacePtr);
      void                            Set(SdlSurfacePtr, GLint ws, GLint wt, GLint mf, GLint Mf);
    protected:
      SdlGlTexture(GLuint);
  };
}