#include <filesystem>
#include <holo/Arch.hh>
#include <holo/Gl.hh>

#include <stdexcept>
#include <string>
namespace holo {
  GlSlProgram::sPtr GlSlProgram::Create() {
    return sPtr(new GlSlProgram());
  }

  shared_ptr<GlSlProgram> GlSlProgram::Build(string vertSrc, string fragSrc) {
    auto created = Create();
    auto vertShader{ GlShader::Load(GL_VERTEX_SHADER, vertSrc) };
    if (!vertShader->Compile()) {
      throw std::runtime_error(vertShader->GetLog());
    }
    auto fragShader{ GlShader::Load(GL_FRAGMENT_SHADER, fragSrc) };
    if (!fragShader->Compile()) {
      throw std::runtime_error(fragShader->GetLog());
    }
    created->Attach(vertShader);
    created->Attach(fragShader);
    if (!created->Link()) {
      throw std::runtime_error(created->GetLog());
    }
    if (!created->Validate()) {
      throw std::runtime_error(created->GetLog());
    };

    return created;
  }

  GlSlProgram::GlSlProgram()
    : ID{ glCreateProgram() } {
    if (ID == 0) {
      throw std::runtime_error("Unable to create GL Program");
    }
    BOOST_LOG_TRIVIAL(trace) << "GlSlProgram#" << ID << " created.";
  }

  GlSlProgram::~GlSlProgram() {
    BOOST_LOG_TRIVIAL(trace) << "GlSlProgram#" << ID << " destroyed.";
    glDeleteProgram(ID);
  }

  void GlSlProgram::Attach(GlShader::sPtr shader) {
    glAttachShader(ID, shader->ID);
  }

  bool GlSlProgram::GetLinkStatus() {
    GLint linkStatus = GL_FALSE;
    glGetProgramiv(ID, GL_LINK_STATUS, &linkStatus);
    BOOST_LOG_TRIVIAL(debug) << "GlSlProgram#" << ID << " link status: " << linkStatus;
    return linkStatus == GL_TRUE;
  }

  bool GlSlProgram::Link() {
    glLinkProgram(ID);
    return GetLinkStatus();
  }

  bool GlSlProgram::GetValidateStatus() {
    GLint validateStatus = GL_FALSE;
    glGetProgramiv(ID, GL_VALIDATE_STATUS, &validateStatus);
    BOOST_LOG_TRIVIAL(debug) << "GlSlProgram#" << ID << " validate status: " << validateStatus;
    return validateStatus == GL_TRUE;
  }
  bool GlSlProgram::Validate() {
    glValidateProgram(ID);
    return GetValidateStatus();
  }

  GLint GlSlProgram::GetAttribLocation(const std::string& name) {
    GLint loc = glGetAttribLocation(ID, name.c_str());
    if (loc == -1) {
      throw std::runtime_error("Unable to get attribute location of '" + name + "'.");
    }
    return loc;
  }

  GLint GlSlProgram::GetUniformLocation(const std::string& name) {
    GLint loc = glGetUniformLocation(ID, name.c_str());
    if (loc == -1) {
      throw std::runtime_error("Unable to get attribute location of '" + name + "'.");
    }
    return loc;
  }

  std::string GlSlProgram::GetLog() {
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

  void GlSlProgram::Use() {
    glUseProgram(ID);
  }

  void GlSlProgram::StopUse() {
    glUseProgram(0);
  }

  void GlSlProgram::Set(const std::string& n, bool b) {
    glUniform1i(GetUniformLocation(n), (int)b);
  }

  void GlSlProgram::Set(const std::string& n, int i) {
    glUniform1i(GetUniformLocation(n), i);
  }

  void GlSlProgram::Set(const std::string& n, float f) {
    glUniform1f(GetUniformLocation(n), f);
  }

  int GlSlProgram::GetMaxAttributeLength() {
    int length;
    glGetProgramiv(ID, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &length);
    return length;
  }

  int GlSlProgram::GetAttributeCount() {
    int count;
    glGetProgramiv(ID, GL_ACTIVE_ATTRIBUTES, &count);
    return count;
  }

  int GlSlProgram::GetUniformCount() {
    int count;
    glGetProgramiv(ID, GL_ACTIVE_UNIFORMS, &count);
    return count;
  }

  std::string GlSlProgram::GetAttributeName(int index) {
    int    bufSize = GetMaxAttributeLength();
    char   name[bufSize];
    int    length;
    int    size;
    GLenum type;
    glGetActiveAttrib(ID, index, bufSize, &length, &size, &type, name);

    return std::string(name);
  }

  std::vector<std::string> GlSlProgram::GetAttributeList() {
    int count = GetAttributeCount();

    std::vector<std::string> list;
    for (int i = 0; i < count; i++) {
      list.push_back(GetAttributeName(i));
    }
    return list;
  }

}