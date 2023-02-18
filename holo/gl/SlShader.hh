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
  class GlSlShader {
    public:
      using sPtr = std::shared_ptr<GlSlShader>;
      static sPtr Load(GLenum, const std::string&);
      static sPtr Create(GLenum);
      static sPtr Create(GLenum, const GLchar*);

    private:
      GlSlShader(GLenum type);

    public:
      ~GlSlShader();
      void         SetSource(const GLchar*);
      void         LoadSource(std::string);
      bool         GetCompileStatus();
      bool         Compile();
      std::string  GetLog();
      GLuint const ID;
      GLenum const Type;
  };
}