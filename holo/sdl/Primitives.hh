#pragma once
#include <holo/stdPrimitives.hh>
#include <SDL2pp/Surface.hh>
#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>

namespace holo {
  using SdlSurface = SDL2pp::Surface;
  using SdlSurfacePtr = std::shared_ptr<SDL2pp::Surface>;
  using SdlRenderer = SDL2pp::Renderer;
  using SdlRendererPtr = std::shared_ptr<SDL2pp::Renderer>;
  using SdlTexture = SDL2pp::Texture;
  using SdlWin    = SDL2pp::Window;
  using SdlWinPtr = std::shared_ptr<SdlWin>;
}