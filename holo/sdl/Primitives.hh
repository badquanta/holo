#pragma once
#include <SDL2pp/Font.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Surface.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Window.hh>
#include <holo/stdPrimitives.hh>

namespace holo {
  using SdlPoint       = SDL2pp::Point;
  using SdlRect        = SDL2pp::Rect;
  using SdlSurface     = SDL2pp::Surface;
  using SdlSurfacePtr  = std::shared_ptr<SDL2pp::Surface>;
  using SdlRenderer    = SDL2pp::Renderer;
  using SdlRendererPtr = std::shared_ptr<SDL2pp::Renderer>;
  using SdlTexture     = SDL2pp::Texture;
  using SdlWin         = SDL2pp::Window;
  using SdlFont        = SDL2pp::Font;
  using SdlWinPtr      = std::shared_ptr<SdlWin>;
}