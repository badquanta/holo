#pragma once
#include <holo/gl/math.hh>
#include <holo/stdPrimitives.hh>
namespace holo {
  /** Used for GlCamera defaults. \ingroup gl  */
  const float GlCameraYAW         = -90.0f;
  /** Used for GlCamera defaults. \ingroup gl  */
  const float GlCameraPITCH       = 0.0f;
  /** Used for GlCamera defaults. \ingroup gl  */
  const float GlCameraSPEED       = 2.5f;
  /** Used for GlCamera defaults. \ingroup gl  */
  const float GlCameraSENSITIVITY = 0.1f;
  /** Used for GlCamera defaults. \ingroup gl  */
  const float GlCameraZOOM        = 45.0f;
  /** Used for GlCamera defaults. \ingroup gl  */
  const vec3  GlCameraORIGIN{ 0.0f, 0.0f, 0.0f };
  /** Used for GlCamera defaults. \ingroup gl  */
  const vec3  GlCameraUP{ 0.0f, 1.0f, 0.0f };
  /** Used for GlCamera defaults. \ingroup gl */
  const vec3  GlCameraFRONT{ 0.0f, 0.0f, -1.0f };
  /**
   * \todo GlCamera requires some major refactoring to support various camera modes and control paradigms.
   * \ingroup gl
   */
  class GlCamera {
    public:
      /** position is updated with momentum on each step. */
      vec3  Position{ GlCameraORIGIN };
      /** momentum is vector and velocity per second. */
      vec3  Momentum{ GlCameraORIGIN };
      /** define 1/2 of camera orientation.*/
      vec3  Front{ GlCameraUP };
      /** define 2/2 of camera orientation.*/
      vec3  Up{ GlCameraFRONT };
      /** cache 3/2 of camera orientation (defined by `Front` & `Up`) */
      vec3  Right;
      /** keep track of global UP */
      vec3  WorldUp{ GlCameraUP };
      /** used to define Front & Up */
      float Yaw{ GlCameraYAW };
      /** used to define Front & Up */
      float Pitch{ GlCameraPITCH };
      /** used to factor Momentum */
      float Speed{ GlCameraSPEED };
      /** used to factor Mouse Input */
      float Sensitivity{ GlCameraSENSITIVITY };
      /** used to vary field of view */
      float Zoom{ GlCameraZOOM };

      /** Adds momentum in the Front direction. */
      function<void()> const ForwardMomentum{ [this]() {
        this->Momentum += this->Front;
      } };
      /** Adds momentum in the -Front direction */
      function<void()> const ReverseMomentum{ [this]() {
        this->Momentum += -(this->Front);
      } };
      /** Adds momentum in the Left direction */
      function<void()> const LeftMomentum{ [this]() {
        this->Momentum -= this->Right;
      } };
      /** Adds momentum in the -Left direction */
      function<void()> const RightMomentum{ [this]() {
        this->Momentum += this->Right;
      } };

      /** This function performs camera motion. */
      function<void(milliseconds)> const Step{ [this](milliseconds ms) {
        // loose a bit over time.
        this->Position += ((ms / 1000.0f).count() * this->Momentum * Speed);
        this->Momentum -= ((ms / 1000.0f).count() * (2.0f * this->Momentum));
        if (glm::length(this->Momentum) < 0.333) {
          this->Momentum = vec3{ 0.0f };
        }
      } };

      /** Construct a camera. */
      GlCamera(
        vec3 position = GlCameraORIGIN, vec3 up = GlCameraUP,
        float yaw = GlCameraYAW, float pitch = GlCameraPITCH
      );
      /** Get rid of the camera. */
      ~GlCamera();
      /** Get the VIEW MATRIX */
      mat4 GetView();
      /** Update calculated vectors. */
      void UpdateVectors();
      /** Control Pitch & YAW with 2D motion. */
      void MouseMotionCtrl(float dx, float dy);
      /** Control FOV with 1D motion. */
      void MouseScrollZoom(float yoffset);
  };
}
