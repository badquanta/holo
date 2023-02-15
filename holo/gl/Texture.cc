#include <boost/log/trivial.hpp>
#include <holo/Arch.hh>
#include <holo/Gl.hh>
namespace holo {
  shared_ptr<GlTexture> GlTexture::Load(std::string path) {
    BOOST_LOG_TRIVIAL(info) << "GlTexture::Load('" << path << "')";
    std::string   found = Arch::FindPath(path);
    SdlSurfacePtr surf  = std::make_shared<SDL2pp::Surface>(found);
    return Create(surf);
  }

  shared_ptr<GlTexture> GlTexture::Create(SdlSurfacePtr surf) {
    sPtr created{ Create() };
    created->Set(surf);
    return created;
  }

  shared_ptr<GlTexture> GlTexture::Create() {
    GLuint ID;
    glGenTextures(1, &ID);
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
    GlNoErrors();
    return sPtr{ new GlTexture(ID) };
  }

  GlTexture::GlTexture(GLuint id)
    : ID{ id } {}

  void GlTexture::Bind() const {
    // BOOST_LOG_TRIVIAL(trace) << "Texture#"<<ID<<" Bound.";
    glBindTexture(GL_TEXTURE_2D, ID);
    //BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
    GlNoErrors();
  }

  void GlTexture::Set(SdlSurfacePtr surf) {
    Set(surf, GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
  }

  void GlTexture::Set(SdlSurfacePtr surf, GLint ws, GLint wt, GLint mf, GLint Mf) {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
    SdlSurface converted{ surf->Convert(SDL_PIXELFORMAT_RGBA32) };
    Bind();
    glTexImage2D(
      GL_TEXTURE_2D, 0, GL_RGBA, converted.GetWidth(), converted.GetHeight(), 0, GL_RGBA,
      GL_UNSIGNED_BYTE, (converted.Get()->pixels)
    );
    GlNoErrors();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ws);

    GlNoErrors();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wt);

    GlNoErrors();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mf);

    GlNoErrors();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Mf);

    GlNoErrors();
    glGenerateMipmap(GL_TEXTURE_2D);
    GlNoErrors();
  }

  GlTexture::~GlTexture() {
    glDeleteTextures(1, &ID);
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
    GlNoErrors();
  }
}