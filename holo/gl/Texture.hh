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
#include<holo/gl/base.hh>
namespace holo {

  /** Manage the lifetime of a texture via shared_ptr */
  class GlTexture {
    public:
      using sPtr = std::shared_ptr<GlTexture>;

      /** Create an empty texture. */
      static sPtr  Create();

      /** Read-only ID*/
      const GLuint ID;

      /** \todo implement or remove*/
      string type{"TODO"};
      /** \todo implement or remove*/
      string path{"TODO"};

    protected:
      /** inaccessible, use `Create()` */
      GlTexture(GLuint);
      static GLuint CreateID();

    public:
      ~GlTexture();
      void Bind() const;
      void Bind(GLenum TEXTURE_NUMBER) const;
  };
}