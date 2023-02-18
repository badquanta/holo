#include <holo/Arch.hh>
#include <holo/gl/Errors.hh>
#include <holo/gl/SlProgram.hh>
namespace holo {
  GlSlProgram::sPtr GlSlProgram::Create() {
    return sPtr(new GlSlProgram());
  }

  shared_ptr<GlSlProgram> GlSlProgram::Build(string vertSrc, string fragSrc) {
    auto created = Create();
    auto vertShader{ GlSlShader::Load(GL_VERTEX_SHADER, vertSrc) };
    if (!vertShader->Compile()) {
      throw std::runtime_error(vertShader->GetLog());
    }
    auto fragShader{ GlSlShader::Load(GL_FRAGMENT_SHADER, fragSrc) };
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

  shared_ptr<GlSlProgram> GlSlProgram::Build(string name) {
    return Build(name + ".vs", name + ".fs");
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

  void GlSlProgram::Attach(GlSlShader::sPtr shader) {
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
      BOOST_LOG_TRIVIAL(debug) << "GlSlShader#" << ID << " LOG maxLength=" << maxLength
                               << " logLength=" << logLength << "\n"
                               << log;
      return log;
    } else {
      return "Invalid program ID";
    }
  }

  void GlSlProgram::Use() {
    glUseProgram(ID);
    GlNoErrors();
  }

  void GlSlProgram::StopUse() {
    glUseProgram(0);
    GlNoErrors();
  }

  void GlSlProgram::SetBool(const std::string& n, bool b) {
    glUniform1i(GetUniformLocation(n), (int)b);
    GlNoErrors();
  }

  void GlSlProgram::SetInt(const std::string& n, int i) {
    glUniform1i(GetUniformLocation(n), i);
    GlNoErrors();
  }

  void GlSlProgram::SetFloat(const std::string& n, float f) {
    glUniform1f(GetUniformLocation(n), f);
    GlNoErrors();
  }

  void GlSlProgram::SetVec2(const std::string& n, const vec2& v) {
    glUniform2fv(GetUniformLocation(n), 1, &v[0]);
    GlNoErrors();
  }

  void GlSlProgram::SetVec2(const string& n, float x, float y) {
    glUniform2f(GetUniformLocation(n), x, y);
    GlNoErrors();
  }

  void GlSlProgram::SetVec3(const string& n, const vec3& v) {
    glUniform3fv(GetUniformLocation(n), 1, &v[0]);
    GlNoErrors();
  }

  void GlSlProgram::SetVec3(const string& n, float x, float y, float z) {
    glUniform3f(GetUniformLocation(n), x, y, z);
    GlNoErrors();
  }

  void GlSlProgram::SetVec4(const string& n, const vec4& v) {
    glUniform4fv(GetUniformLocation(n), 1, &v[0]);
    GlNoErrors();
  }

  void GlSlProgram::SetVec4(const string& n, float x, float y, float z, float w) {
    glUniform4f(GetUniformLocation(n), x, y, z, w);
    GlNoErrors();
  }
  void GlSlProgram::SetMat2(const string& n, const mat2& m) {
    glUniformMatrix2fv(GetUniformLocation(n), 1, GL_FALSE, &m[0][0]);
    GlNoErrors();
  };

  void GlSlProgram::SetMat3(const string& n, const mat3& m) {
    glUniformMatrix3fv(GetUniformLocation(n), 1, GL_FALSE, &m[0][0]);
    GlNoErrors();
  };

  void GlSlProgram::SetMat4(const string& n, const mat4& m) {
    glUniformMatrix4fv(GetUniformLocation(n), 1, GL_FALSE, &m[0][0]);
    GlNoErrors();
  };
  ;

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