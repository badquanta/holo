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
#include <holo/gl/base.hh>
namespace holo {
  /**
   * Array of memory allocated by the OpenGL context.
   * \see https://www.khronos.org/opengl/wiki/Vertex_Specification#Vertex_Buffer_Object
   * \see https://www.khronos.org/opengl/wiki/Buffer_Object
   * \ingroup gl
  */
  template<GLenum TARGET, typename ELEMENT_TYPE, GLenum USAGE>
  class GlBuffer {
    public:
      /** \todo Remove, stop using `sPtr` */
      using sPtr = std::shared_ptr<GlBuffer<TARGET, ELEMENT_TYPE, USAGE>>;
      /** Create a shared buffer without any data set. */
      static sPtr Create() {
        GLuint id;
        glGenBuffers(1, &id);
        return sPtr{ new GlBuffer(id) };
      };
      /** Create a shared buffer using data from a vector. */
      static sPtr Create(const vector<ELEMENT_TYPE>& data) {
        sPtr created{ Create() };
        created->Data(data);
        return created;
      };

    private:
      /** Inaccessible, utilize `Create` to initialize new buffer wrapper. */
      explicit GlBuffer(GLuint id)
        : ID{ id }
        , Target{ TARGET }
        , Usage{ USAGE } {};
      /** The ID/name of the OpenGL buffer*/
      GLuint const ID;
      /** \todo document what this does...*/
      GLenum const Target;
      /** \todo document what this does...*/
      GLenum const Usage;

    public:
      /** ensure `glDeleteBuffers` is called. */
      ~GlBuffer() { glDeleteBuffers(1, &ID); };
      /** Bind this buffer to `Target` */
      void Bind() { glBindBuffer(Target, ID); };
      /** Set the contents of the buffer from vector of element types. **/
      void Data(const vector<ELEMENT_TYPE>& data) { Data(data.size(), data.data()); }
      /** Set the contents of the buffer. */
      void Data(int length, const ELEMENT_TYPE data[]) {
        Bind();
        glBufferData(Target, length * sizeof(ELEMENT_TYPE), data, Usage);
      };
  };
  /** OpenGL buffer with `GL_ARRAY_BUFFER` as `Target` and `GL_STATIC_DRAW` as `Usage`.  \ingroup gl */
  using GlArrayBuffer = GlBuffer<GL_ARRAY_BUFFER, float, GL_STATIC_DRAW>;
  /** OpenGL buffer with `GL_ELEMENT_ARRAY_BUFFER` as `Target` and `GL_STATIC_DRAW` as `Usage`.  \ingroup gl */
  using GlElementArrayBuffer = GlBuffer<GL_ELEMENT_ARRAY_BUFFER, unsigned int, GL_STATIC_DRAW>;
}