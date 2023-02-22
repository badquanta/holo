#include <holo/gl/Errors.hh>
#include <holo/boostPrimitives.hh>
namespace holo {
  /** Simply calls `glGetError` and if not GL_NO_ERROR it throws a runtime error with the error name.*/
  void GlNoErrors(string loc) {
    GLenum errStatus{ glGetError() };
    if (!errStatus == GL_NO_ERROR) {
      string msg;
      switch (errStatus) {
        case GL_INVALID_ENUM:
          msg = " GLError: Invalid Enum";
          break;
        case GL_INVALID_VALUE:
          msg = " GLError: Invalid Value";
          break;
        case GL_INVALID_OPERATION:
          msg = " GLError: Invalid Operation";
          break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
          msg = " GLError: Invalid Framebuffer Operation";
          break;
        case GL_OUT_OF_MEMORY:
          msg = " GLError: Out of memory.";
          break;
        case GL_STACK_UNDERFLOW:
          msg = " GLError: Stack underflow.";
          break;
        case GL_STACK_OVERFLOW:
          msg = " GLError: Stack overflow.";
          break;
        default:
          msg = " GLError: UNKNOWN ERROR VALUE ";
      };
      BOOST_LOG_TRIVIAL(error) << __PRETTY_FUNCTION__ << msg;
      throw runtime_error(msg);
    }
    //BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__ << " No errors.";
  }
}