#include <holo/gl/Camera.hh>
namespace holo {
  GlCamera::GlCamera(vec3 position, vec3 up, float yaw, float pitch)
    : Position{ position }
    , Up{ up }
    , WorldUp{ up }
    , Yaw{ yaw }
    , Pitch{ pitch } {
    UpdateVectors();
  }

  GlCamera::~GlCamera(){}

  mat4 GlCamera::GetView() {
    return glm::lookAt(Position, Position + Front, Up);
  }
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

  void GlCamera::MouseScrollZoom(float yoffset) {
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
      Zoom = 1.0f;
    if (Zoom > 45.0f)
      Zoom = 45.0f;
  }

}