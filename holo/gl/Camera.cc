#include <holo/gl/Camera.hh>
namespace holo {
  /** Setup camera & update vectors. */
  GlCamera::GlCamera(vec3 position, vec3 up, float yaw, float pitch)
    : Position{ position }
    , Up{ up }
    , WorldUp{ up }
    , Yaw{ yaw }
    , Pitch{ pitch } {
    UpdateVectors();
  }
  /** Get rid of a camera. */
  GlCamera::~GlCamera(){}
  /** Use `glm::lookAt` to calculate a view matrix. */
  mat4 GlCamera::GetView() {
    return glm::lookAt(Position, Position + Front, Up);
  }
  /** Recalculate `Front`, `Right`, and `Up` vectors. */
  void GlCamera::UpdateVectors() {
    vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front   = glm::normalize(front);
    // also re-calculate the Right and Up vector
    Right   = glm::normalize(glm::cross(Front, WorldUp)
      ); // normalize the vectors, because their length gets closer to 0 the more you look up or down
         // which results in slower movement.
    Up      = glm::normalize(glm::cross(Right, Front));
  }
  /** 2D motion to YAW & PITCH camera controls */
  void GlCamera::MouseMotionCtrl(float dx, float dy) {
    float x = dx * Sensitivity;
    float y = dy * Sensitivity;
    Yaw     += x;
    Pitch   += y;
    if (Pitch > 89.0f)
      Pitch = 89.0f;
    if (Pitch < -89.0f)
      Pitch = -89.0f;
    UpdateVectors();
  }
  /** 1D motion to F.O.V. zoom control.*/
  void GlCamera::MouseScrollZoom(float yoffset) {
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
      Zoom = 1.0f;
    if (Zoom > 45.0f)
      Zoom = 45.0f;
  }

}