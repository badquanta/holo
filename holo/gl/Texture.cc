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
#include <holo/Arch.hh>
#include <holo/gl/Texture.hh>
#include <holo/gl/Errors.hh>
namespace holo {

  GLuint GlTexture::CreateID(){
    GLuint ID;
    glGenTextures(1, &ID);
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
    GlNoErrors();
    return ID;
  }


  shared_ptr<GlTexture> GlTexture::Create() {
    return sPtr{ new GlTexture(CreateID()) };
  }

  GlTexture::GlTexture(GLuint id)
    : ID{ id } {}

  void GlTexture::Bind() const {
    // BOOST_LOG_TRIVIAL(trace) << "Texture#"<<ID<<" Bound.";
    glBindTexture(GL_TEXTURE_2D, ID);
    //BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
    GlNoErrors();
  }

  void GlTexture::Bind(GLuint T_NUM) const {
    glActiveTexture(T_NUM);
    GlNoErrors();
    Bind();
  }


  GlTexture::~GlTexture() {
    glDeleteTextures(1, &ID);
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
    GlNoErrors();
  }
}