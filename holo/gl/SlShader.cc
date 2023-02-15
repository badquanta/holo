#include <boost/log/trivial.hpp>
#include <fstream>
#include <holo/Arch.hh>
#include <holo/Gl.hh>
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

    std::string searchPath{ Arch::FindPath(srcFile) };
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__ << srcFile;
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
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__ << "#" << ID ;
  }

  GlShader::~GlShader() {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__ << "#" << ID ;
    glDeleteShader(ID);
    GlNoErrors();
  }

  void GlShader::SetSource(const GLchar* src) {
    BOOST_LOG_TRIVIAL(debug) << __PRETTY_FUNCTION__ << "#" << ID << "\n"
                             << src << std::endl;
    glShaderSource(ID, 1, &src, nullptr);
    GlNoErrors();
  }

  bool GlShader::GetCompileStatus() {
    GLint compileStatus = GL_FALSE;
    glGetShaderiv(ID, GL_COMPILE_STATUS, &compileStatus);
    BOOST_LOG_TRIVIAL(debug) << __PRETTY_FUNCTION__ << "#" << ID  << " compile status: " << compileStatus;
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