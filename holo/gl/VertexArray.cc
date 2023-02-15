#include <boost/log/trivial.hpp>
#include <holo/Gl.hh>

namespace holo {
  /** \details Request open gl*/
  shared_ptr<GlVertexArray> GlVertexArray::Create() {
    GLuint id;
    glGenVertexArrays(1, &id);
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
    GlNoErrors();
    return sPtr(new GlVertexArray(id));
  }
  /** \details const instance constructor. */
  GlVertexArray::GlVertexArray(GLuint id)
    : ID{ id } {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__ <<"#" << ID;
  }
  /** \details const instance destructor. */
  GlVertexArray::~GlVertexArray() {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__ <<"#"<< ID ;
    glDeleteVertexArrays(1, &ID);
    GlNoErrors();
  }
  /**
   * \see https://docs.gl/gl3/glBindVertexArray
   */
  GLuint GlVertexArray::Bind(GLuint id) {
    glBindVertexArray(id);
    GlNoErrors();

    return id;
  }
  GLuint GlVertexArray::Bind() const {
    Bind(ID);
    GlNoErrors();
    return ID;
  }
}