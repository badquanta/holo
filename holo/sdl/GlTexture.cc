#include <holo/Arch.hh>
#include <holo/ShareFiles.hh>
#include <holo/boostPrimitives.hh>
#include <holo/gl/Errors.hh>
#include <holo/sdl/GlTexture.hh>
namespace holo {
  SdlGlTexture::SdlGlTexture(GLuint id)
    : GlTexture(id) {}

  /// @brief Find and open an image file as an `SDL2pp::Surface`.
  /// @param path path to search for
  /// @param ts additional suffix variations to search for if not found
  /// @param tp additional prefix variations to search for if not found
  /// @param ta additional absolute prefix variations to search for if not found
  /// @return sdl surface
  /// @note checks for path without modification from current working directory
  /// FIRST.
  /// @todo Possible bug: If program changes CWD then ShareFiles::Found might be
  /// broken. Might be able to fix with absolute indexes stored?
  shared_ptr<SdlGlTexture> SdlGlTexture::Load(
    std::string path, const vector<string>& ts, const vector<string>& tp,
    const vector<string>& ta
  ) {
    BOOST_LOG_TRIVIAL(info) << __PRETTY_FUNCTION__ << path << "')";
    std::string   found = ShareFiles::Require(path, ts, tp, ta);
    SdlSurfacePtr surf  = std::make_shared<SDL2pp::Surface>(found);
    return Create(surf);
  }
  /** @returns created texture without any data set.*/
  shared_ptr<SdlGlTexture> SdlGlTexture::Create() {
    return shared_ptr<SdlGlTexture>{ new SdlGlTexture(CreateID()) };
  }
  /** @returns created texture with pixels set from `surf`.*/
  shared_ptr<SdlGlTexture> SdlGlTexture::Create(SdlSurfacePtr surf) {
    auto created{ Create() };
    created->Set(surf);
    return created;
  }
  /** @todo re-write how we handle the parameters to Set. */
  void SdlGlTexture::Set(SdlSurfacePtr surf) {
    Set(surf, GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
  }
  /** @bug THIS NEEDS TO FLIP PIXEL DATA FIRST!!!! */
  void SdlGlTexture::Set(
    SdlSurfacePtr surf, GLint ws, GLint wt, GLint mf, GLint Mf
  ) {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
    SdlSurface converted{ surf->Convert(SDL_PIXELFORMAT_RGBA32) };
    surf->Blit(
      SdlRect{
        surf->GetSize(), -surf->GetSize()
    },
      converted, SdlRect{ { 0, 0 }, -surf->GetSize() }
    );
    Bind();
    glTexImage2D(
      GL_TEXTURE_2D, 0, GL_RGBA, converted.GetWidth(), converted.GetHeight(), 0,
      GL_RGBA, GL_UNSIGNED_BYTE, (converted.Get()->pixels)
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