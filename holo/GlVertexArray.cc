#include "Gl.hh"
#include <boost/log/trivial.hpp>
namespace holo {
  /** \details Request open gl*/
  GlVertexArray::sPtr GlVertexArray::Create() {
    GLuint id;
    glGenVertexArrays(1, &id);
    return sPtr(new GlVertexArray(id));
  }
  /** \details const instance constructor. */
  GlVertexArray::GlVertexArray(GLuint id)
    : ID{ id } {
    BOOST_LOG_TRIVIAL(trace) << "GlVertexArray#" << ID << " created.";
  }
  /** \details const instance destructor. */
  GlVertexArray::~GlVertexArray() {
    BOOST_LOG_TRIVIAL(trace) << "GlVertexArray#" << ID << " destroyed.";
    glDeleteVertexArrays(1, &ID);
  }
  /** \details set as active renderer. */
  void GlVertexArray::Bind() const {
    glBindVertexArray(ID);
  }
}