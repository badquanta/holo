#include <boost/log/trivial.hpp>
#include <fstream>
#include <holo/Arch.hh>
#include <holo/ShareFiles.hh>
#include <holo/gl/SlShader.hh>
#include <holo/gl/Errors.hh>
namespace holo {

  GlSlShader::sPtr GlSlShader::Create(GLenum type) {
    return sPtr(new GlSlShader(type));
  }

  GlSlShader::sPtr GlSlShader::Create(GLenum type, const GLchar* src) {
    sPtr created{ Create(type) };
    created->SetSource(src);
    return created;
  }

  GlSlShader::sPtr GlSlShader::Load(GLenum type, const std::string& srcFile) {

    std::string searchPath{ ShareFiles::Require(srcFile, {}, {"holo/gl/sl"}) };
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__ << srcFile;
    std::ifstream file(searchPath);
    if (!file.is_open()) {
      throw std::runtime_error("Unable to load source file.");
    }
    std::string source((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
    return Create(type, source.c_str());
  }

  GlSlShader::GlSlShader(GLenum type)
    : Type{ type }
    , ID{ glCreateShader(type) } {
    if (ID == 0) {
      throw std::runtime_error("Unable to create shader.");
    }
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__ << "#" << ID ;
  }

  GlSlShader::~GlSlShader() {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__ << "#" << ID ;
    glDeleteShader(ID);
    GlNoErrors();
  }

  void GlSlShader::SetSource(const GLchar* src) {
    BOOST_LOG_TRIVIAL(debug) << __PRETTY_FUNCTION__ << "#" << ID << "\n"
                             << src << std::endl;
    glShaderSource(ID, 1, &src, nullptr);
    GlNoErrors();
  }

  bool GlSlShader::GetCompileStatus() {
    GLint compileStatus = GL_FALSE;
    glGetShaderiv(ID, GL_COMPILE_STATUS, &compileStatus);
    BOOST_LOG_TRIVIAL(debug) << __PRETTY_FUNCTION__ << "#" << ID  << " compile status: " << compileStatus;
    return compileStatus == GL_TRUE;
  }

  bool GlSlShader::Compile() {
    glCompileShader(ID);
    return GetCompileStatus();
  }

  std::string GlSlShader::GetLog() {
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
      BOOST_LOG_TRIVIAL(debug) << __PRETTY_FUNCTION__ << "#" << ID  << " LOG maxLength=" << maxLength
                               << " logLength=" << logLength << "\n"
                               << log;
      return log;
    } else {
      BOOST_LOG_TRIVIAL(error) << __PRETTY_FUNCTION__ << "#" << ID  << " unable to get log.";
      return "Invalid shader ID";
    }
  }
}