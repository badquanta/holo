#include "GlProgram.hh"
#include "Program.hh"
#include <boost/log/trivial.hpp>
#include <fstream>
#include <stdexcept>
#include <filesystem>
#include <string>
namespace holo {

  GlShader::sPtr GlShader::Create(GLenum type) {
    return sPtr(new GlShader(type));
  }

  GlShader::sPtr GlShader::Create(GLenum type, const GLchar* src) {
    sPtr created{ Create(type) };
    created->SetSource(src);
    return created;
  }

  GlShader::sPtr GlShader::Load(GLenum type, const std::string& srcFile) {
    std::string searchPath{(Program::location / "share" / srcFile).string()};
    if(!std::filesystem::exists(searchPath)){
      throw std::runtime_error(searchPath+" Does not exist");
    };

    std::ifstream file(searchPath);
    if (!file.is_open()) {
      throw std::runtime_error("Unable to load source file.");
    }
    std::string source((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
    return Create(type, source.c_str());
  }

  GlShader::GlShader(GLenum type)
    : Type{ type }
    , ID{ glCreateShader(type) } {
    if (ID == 0) {
      throw std::runtime_error("Unable to create shader.");
    }
    BOOST_LOG_TRIVIAL(trace) << "GlShader#" << ID << " created.";
  }

  GlShader::~GlShader() {
    BOOST_LOG_TRIVIAL(trace) << "GlShader#" << ID << " destroyed.";
    glDeleteShader(ID);
  }

  void GlShader::SetSource(const GLchar* src) {
    BOOST_LOG_TRIVIAL(debug) << "GlShader#" << ID << " source set:\n" << src << std::endl;
    glShaderSource(ID, 1, &src, nullptr);
  }

  bool GlShader::GetCompileStatus() {
    GLint compileStatus = GL_FALSE;
    glGetShaderiv(ID, GL_COMPILE_STATUS, &compileStatus);
    BOOST_LOG_TRIVIAL(debug) << "GlShader#" << ID << " compile status: " << compileStatus;
    return compileStatus == GL_TRUE;
  }

  bool GlShader::Compile() {
    glCompileShader(ID);
    return GetCompileStatus();
  }

  std::string GlShader::GetLog() {
    if (glIsShader(ID)) {
      int maxLength = 0, logLength = 0;
      glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &maxLength);
      char* logStr = new char[maxLength];
      glGetShaderInfoLog(ID, maxLength, &logLength, logStr);
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
      BOOST_LOG_TRIVIAL(error) << "GlShader#" << ID << " unable to get log.";
      return "Invalid shader ID";
    }
  }

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

  GLint GlProgram::GetAttribLocation(std::string name) {
    GLint loc = glGetAttribLocation(ID, name.c_str());
    if (loc == -1) {
      throw std::runtime_error("Unable to get attribute location.");
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

}