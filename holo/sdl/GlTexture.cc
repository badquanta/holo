#include <holo/boostPrimitives.hh>
#include <holo/gl/Errors.hh>
#include <holo/sdl/GlTexture.hh>
#include <holo/Arch.hh>
namespace holo {
  SdlGlTexture::SdlGlTexture(GLuint id)
    : GlTexture(id) {}

  shared_ptr<SdlGlTexture> SdlGlTexture::Load(std::string path) {
    BOOST_LOG_TRIVIAL(info) << __PRETTY_FUNCTION__ << path << "')";
    std::string   found = Arch::FindPath(path);
    SdlSurfacePtr surf  = std::make_shared<SDL2pp::Surface>(found);
    return Create(surf);
  }

  shared_ptr<SdlGlTexture> SdlGlTexture::Create() {
    return shared_ptr<SdlGlTexture>{ new SdlGlTexture(CreateID()) };
  }

  shared_ptr<SdlGlTexture> SdlGlTexture::Create(SdlSurfacePtr surf) {
    auto created{ Create() };
    created->Set(surf);
    return created;
  }

  void SdlGlTexture::Set(SdlSurfacePtr surf) {
    Set(surf, GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
  }

  void SdlGlTexture::Set(SdlSurfacePtr surf, GLint ws, GLint wt, GLint mf, GLint Mf) {
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
}