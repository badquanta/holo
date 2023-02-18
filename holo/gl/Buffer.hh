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
  template<GLenum BufferType, typename DataType, GLenum DataUsage>
  class GlBuffer {
    public:
      using sPtr = std::shared_ptr<GlBuffer>;
      static sPtr Create() {
        GLuint id;
        glGenBuffers(1, &id);
        return sPtr{ new GlBuffer(id) };
      };
      static sPtr Create(const std::vector<DataType>& data) {
        sPtr created{ Create() };
        created->Data(data);
        return created;
      };

    private:
      explicit GlBuffer(GLuint id)
        : ID{ id }
        , Kind{ BufferType }
        , Usage{ DataUsage } {};
      GLuint const ID;
      GLenum const Kind;
      GLenum const Usage;

    public:
      ~GlBuffer() { glDeleteBuffers(1, &ID); };
      void Bind() { glBindBuffer(Kind, ID); };
      void Data(const std::vector<DataType>& data) { Data(data.size(), data.data()); }
      void Data(int length, const DataType data[]) {
        Bind();
        glBufferData(Kind, length * sizeof(DataType), data, Usage);
      };
  };
}