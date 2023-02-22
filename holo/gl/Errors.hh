#pragma once
#include <holo/gl/base.hh>
namespace holo {
  /**
   * Check for any OpenGL errors.
   * If any, throw them as a runtime exception.
   *
   * \todo Implement a version that simply checks for errors and logs if any.
   * \todo Implement a MACRO or other means to report the file & line this was called FROM.
  */
  void GlNoErrors(string msg = __FUNCTION__);
}