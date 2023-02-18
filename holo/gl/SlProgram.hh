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
#include <holo/gl/SlShader.hh>
#include <holo/gl/math.hh>
namespace holo {
  class GlSlProgram {
    public:
      using sPtr = shared_ptr<GlSlProgram>;
      const GLuint                        ID;
      static shared_ptr<GlSlProgram> Create();
      static shared_ptr<GlSlProgram> Build(string vertSrc, string fragSrc);
      static shared_ptr<GlSlProgram> Build(string name);

    private:
      GlSlProgram();

    public:
      ~GlSlProgram();
      void           Attach(GlSlShader::sPtr);
      bool           Link();
      bool           GetLinkStatus();
      bool           Validate();
      bool           GetValidateStatus();
      int            GetAttributeCount();
      int            GetUniformCount();
      int            GetMaxAttributeLength();
      vector<string> GetAttributeList();
      string         GetAttributeName(int index);
      string         GetLog();
      GLint          GetAttribLocation(const string&);
      GLint          GetUniformLocation(const string&);
      void           Use();
      static void    StopUse();

      void SetBool(const string&, bool);
      void SetInt(const string&, int);
      void SetFloat(const string&, float);
      void SetVec2(const string&, const vec2&);
      void SetVec2(const string&, float, float);
      void SetVec3(const string&, const vec3&);
      void SetVec3(const string&, float, float, float);
      void SetVec4(const string&, const vec4&);
      void SetVec4(const string&, float, float, float, float);
      void SetMat2(const string&, const mat2&);
      void SetMat3(const string&, const mat3&);
      void SetMat4(const string&, const mat4&);
  };
}