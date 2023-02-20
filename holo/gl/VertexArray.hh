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
   * \ingroup gl
   */
  class GlVertexArray {
    public:
      /** \todo Stop using sPtr, remove. */
      using sPtr = std::shared_ptr<GlVertexArray>;
      /** \todo Stop using sPtr, refactor return value. */
      static sPtr  Create();
      /** Reference to the last ID that was passed to static Bind() */
      static GLuint BOUND;
      /** The ID of this Vertex Attribute Array*/
      GLuint const ID;

    private:
      /** Inaccessible, Use `Create`*/
      explicit GlVertexArray(GLuint);

    public:
      /** Shared destructor */
      virtual ~GlVertexArray();
      /** static global bind, stack unaffected, last updated.*/
      GLuint        Bind() const;
      /** Unset this one. \todo maybe implement a stack?*/
      GLuint        Unbind() const;
      /** Global rebinding, last call is saved as `BOUND`*/
      static GLuint Bind(GLuint);
      bool IsBound() const;
  };
}