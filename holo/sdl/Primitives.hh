#pragma once
#include <holo/stdPrimitives.hh>
#include <SDL2pp/Surface.hh>
#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>

namespace holo {
  using Surface = SDL2pp::Surface;
  using SurfacePtr = std::shared_ptr<SDL2pp::Surface>;
  using SdlRendererPtr = std::shared_ptr<SDL2pp::Renderer>;
  using SdlWin    = SDL2pp::Window;
  using SdlWinPtr = std::shared_ptr<SdlWin>;
}