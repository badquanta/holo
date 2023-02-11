#include "Gl.hh"
#include "Arch.hh"
#include "boost/log/trivial.hpp"
namespace holo {
  GlTexture::sPtr GlTexture::Load(std::string path) {
    BOOST_LOG_TRIVIAL(info) << "GlTexture::Load('" << path << "')";
    std::string found = Arch::FindPath(path);
    SurfacePtr  surf  = std::make_shared<SDL2pp::Surface>(found);
    return Create(surf);
  }

  GlTexture::sPtr GlTexture::Create(SurfacePtr surf) {
    sPtr created{ Create() };
    created->Set(surf);
    return created;
  }

  GlTexture::sPtr GlTexture::Create() {
    GLuint ID;
    glGenTextures(1, &ID);
    return sPtr{ new GlTexture(ID) };
  }

  GlTexture::GlTexture(GLuint id)
    : ID{ id } {}

  void GlTexture::Bind() const {
    // BOOST_LOG_TRIVIAL(trace) << "Texture#"<<ID<<" Bound.";
    glBindTexture(GL_TEXTURE_2D, ID);
  }

  void GlTexture::Set(SurfacePtr surf) {
    Set(surf, GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
  }

  void GlTexture::Set(SurfacePtr surf, GLint ws, GLint wt, GLint mf, GLint Mf) {
    SDL2pp::Surface converted{ surf->Convert(SDL_PIXELFORMAT_RGBA32) };
    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ws);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wt);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mf);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Mf);
    glTexImage2D(
      GL_TEXTURE_2D, 0, GL_RGBA32I, converted.GetWidth(), converted.GetHeight(), 0, GL_RGBA32I,
      GL_UNSIGNED_BYTE, (converted.Get()->pixels)
    );
    glGenerateMipmap(GL_TEXTURE_2D);
  }

  GlTexture::~GlTexture() {
    glDeleteTextures(1, &ID);
  }
}