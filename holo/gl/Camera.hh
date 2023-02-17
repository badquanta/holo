#pragma once
#include <holo/gl/math.hh>
#include <holo/sdl/Primitives.hh>
namespace holo {
  const float GlCameraYAW         = -90.0f;
  const float GlCameraPITCH       = 0.0f;
  const float GlCameraSPEED       = 2.5f;
  const float GlCameraSENSITIVITY = 0.1f;
  const float GlCameraZOOM        = 45.0f;
  const vec3  GlCameraORIGIN{ 0.0f, 0.0f, 0.0f };
  const vec3  GlCameraUP{ 0.0f, 1.0f, 0.0f };
  const vec3  GlCameraFRONT{ 0.0f, 0.0f, -1.0f };
  class SdlGlCamera {
    public:
      vec3                             Position{ GlCameraORIGIN };
      vec3                             Momentum{ GlCameraORIGIN };
      vec3                             Front{ GlCameraUP };
      vec3                             Up{ GlCameraFRONT };
      vec3                             Right;
      vec3                             WorldUp{ GlCameraUP };
      float                            Yaw{ GlCameraYAW };
      float                            Pitch{ GlCameraPITCH };
      float                            Speed{ GlCameraSPEED };
      float                            Sensitivity{ GlCameraSENSITIVITY };
      float                            Zoom{ GlCameraZOOM };
      function<void(SDL_Event&)> const SdlMouseMotion{ [this](SDL_Event& e) {
        this->MouseMotionCtrl(e.motion.xrel, e.motion.yrel);
      } };
      function<void(SDL_Event&)> const SdlMouseWheel{ [this](SDL_Event& e) {
        this->MouseScrollZoom(e.wheel.y);
      } };
      function<void()> const ForwardMomentum{ [this]() { this->Momentum += this->Front; } };
      function<void()> const ReverseMomentum{ [this]() { this->Momentum += -(this->Front); } };
      function<void()> const LeftMomentum{ [this]() { this->Momentum -= this->Right; } };
      function<void()> const RightMomentum{ [this]() { this->Momentum += this->Right; } };
      function<void(milliseconds)> const Step{ [this](milliseconds ms) {
        // loose a bit over time.
        this->Position += ((ms / 1000.0f).count() * this->Momentum);
        this->Momentum -= ((ms / 1000.0f).count() * (2.0f * this->Momentum));
        if(glm::length(this->Momentum) < 0.333){
          this->Momentum = vec3{0.0f};
        }
      } };

      SdlGlCamera(
        vec3 position = GlCameraORIGIN, vec3 up = GlCameraUP, float yaw = GlCameraYAW,
        float pitch = GlCameraPITCH
      );
      ~SdlGlCamera();
      mat4 GetView();
      void UpdateVectors();

      void MouseMotionCtrl(float dx, float dy);
      void MouseScrollZoom(float yoffset);
  };
}
