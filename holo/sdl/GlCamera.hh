#pragma once
#include <holo/gl/Camera.hh>
#include <holo/sdl/Evt.hh>
namespace holo {
  class SdlGlCamera : public GlCamera {
    public:
      function<void(SDL_Event&)> const SdlMouseMotion{ [this](SDL_Event& e) {
        this->MouseMotionCtrl(e.motion.xrel, e.motion.yrel);
      } };
      function<void(SDL_Event&)> const SdlMouseWheel{ [this](SDL_Event& e) {
        this->MouseScrollZoom(e.wheel.y);
      } };
  };
}