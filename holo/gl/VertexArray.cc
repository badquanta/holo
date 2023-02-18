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
#include <boost/log/trivial.hpp>
#include <holo/gl/VertexArray.hh>
#include <holo/gl/Errors.hh>
namespace holo {
  /** \details Request open gl*/
  shared_ptr<GlVertexArray> GlVertexArray::Create() {
    GLuint id;
    glGenVertexArrays(1, &id);
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
    GlNoErrors();
    return sPtr(new GlVertexArray(id));
  }
  /** \details const instance constructor. */
  GlVertexArray::GlVertexArray(GLuint id)
    : ID{ id } {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__ <<"#" << ID;
  }
  /** \details const instance destructor. */
  GlVertexArray::~GlVertexArray() {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__ <<"#"<< ID ;
    glDeleteVertexArrays(1, &ID);
    GlNoErrors();
  }
  /**
   * \see https://docs.gl/gl3/glBindVertexArray
   */
  GLuint GlVertexArray::Bind(GLuint id) {
    glBindVertexArray(id);
    GlNoErrors();

    return id;
  }
  GLuint GlVertexArray::Bind() const {
    Bind(ID);
    GlNoErrors();
    return ID;
  }
}