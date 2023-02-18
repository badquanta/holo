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
#pragma once
#include <holo/gl/base.hh>
namespace holo {
  /**
   * \see https://www.opengl.org/sdk/docs/tutorials/CodeColony/vertexarrays.php
   */
  class GlVertexArray {
    public:
      using sPtr = std::shared_ptr<GlVertexArray>;
      static sPtr  Create();
      GLuint const ID;

    private:
      explicit GlVertexArray(GLuint);

    public:
      virtual ~GlVertexArray();
      /** static global bind, stack unaffected, last updated.*/
      GLuint        Bind() const;
      static GLuint Bind(GLuint);
  };
}