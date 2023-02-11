#include "Gl.hh"
#include "Arch.hh"
#include <boost/log/trivial.hpp>
#include <filesystem>

#include <stdexcept>
#include <string>
namespace holo {
  GlProgram::sPtr GlProgram::Create() {
    return sPtr(new GlProgram());
  }

  GlProgram::GlProgram()
    : ID{ glCreateProgram() } {
    if (ID == 0) {
      throw std::runtime_error("Unable to create GL Program");
    }
    BOOST_LOG_TRIVIAL(trace) << "GlProgram#" << ID << " created.";
  }

  GlProgram::~GlProgram() {
    BOOST_LOG_TRIVIAL(trace) << "GlProgram#" << ID << " destroyed.";
    glDeleteProgram(ID);
  }

  void GlProgram::Attach(GlShader::sPtr shader) {
    glAttachShader(ID, shader->ID);
  }

  bool GlProgram::GetLinkStatus() {
    GLint linkStatus = GL_FALSE;
    glGetProgramiv(ID, GL_LINK_STATUS, &linkStatus);
    BOOST_LOG_TRIVIAL(debug) << "GlProgram#" << ID << " link status: " << linkStatus;
    return linkStatus == GL_TRUE;
  }

  bool GlProgram::Link() {
    glLinkProgram(ID);
    return GetLinkStatus();
  }

  bool GlProgram::GetValidateStatus() {
    GLint validateStatus = GL_FALSE;
    glGetProgramiv(ID, GL_VALIDATE_STATUS, &validateStatus);
    BOOST_LOG_TRIVIAL(debug) << "GlProgram#" << ID << " validate status: " << validateStatus;
    return validateStatus == GL_TRUE;
  }
  bool GlProgram::Validate() {
    glValidateProgram(ID);
    return GetValidateStatus();
  }

  GLint GlProgram::GetAttribLocation(const std::string& name) {
    GLint loc = glGetAttribLocation(ID, name.c_str());
    if (loc == -1) {
      throw std::runtime_error("Unable to get attribute location of '" + name + "'.");
    }
    return loc;
  }

  GLint GlProgram::GetUniformLocation(const std::string& name) {
    GLint loc = glGetUniformLocation(ID, name.c_str());
    if (loc == -1) {
      throw std::runtime_error("Unable to get attribute location of '" + name + "'.");
    }
    return loc;
  }

  std::string GlProgram::GetLog() {
    if (glIsProgram(ID)) {
      int maxLength = 0, logLength = 0;
      glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &maxLength);
      char* logStr = new char[maxLength];
      glGetProgramInfoLog(ID, maxLength, &logLength, logStr);
      std::string log;
      if (logLength > 0) {
        log = logStr;
      }
      delete[] logStr;
      BOOST_LOG_TRIVIAL(debug) << "GlShader#" << ID << " LOG maxLength=" << maxLength
                               << " logLength=" << logLength << "\n"
                               << log;
      return log;
    } else {
      return "Invalid program ID";
    }
  }

  void GlProgram::Use() {
    glUseProgram(ID);
  }

  void GlProgram::StopUse() {
    glUseProgram(0);
  }

  void GlProgram::Set(const std::string& n, bool b) {
    glUniform1i(GetUniformLocation(n), (int)b);
  }

  void GlProgram::Set(const std::string& n, int i) {
    glUniform1i(GetUniformLocation(n), i);
  }

  void GlProgram::Set(const std::string& n, float f) {
    glUniform1f(GetUniformLocation(n), f);
  }

  int GlProgram::GetMaxAttributeLength() {
    int length;
    glGetProgramiv(ID, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &length);
    return length;
  }

  int GlProgram::GetAttributeCount() {
    int count;
    glGetProgramiv(ID, GL_ACTIVE_ATTRIBUTES, &count);
    return count;
  }

  int GlProgram::GetUniformCount() {
    int count;
    glGetProgramiv(ID, GL_ACTIVE_UNIFORMS, &count);
    return count;
  }

  std::string GlProgram::GetAttributeName(int index) {
    int    bufSize = GetMaxAttributeLength();
    char   name[bufSize];
    int    length;
    int    size;
    GLenum type;
    glGetActiveAttrib(ID, index, bufSize, &length, &size, &type, name);

    return std::string(name);
  }

  std::vector<std::string> GlProgram::GetAttributeList() {
    int count = GetAttributeCount();

    std::vector<std::string> list;
    for (int i = 0; i < count; i++) {
      list.push_back(GetAttributeName(i));
    }
    return list;
  }

}