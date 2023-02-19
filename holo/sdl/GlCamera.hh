#pragma once
#include <holo/gl/Camera.hh>
#include <holo/sdl/EvtRoot.hh>
namespace holo {
  /**
   * Handle Sdl & Gl camera integration.
   * \note provides helpers to connect events to actions that effect the camera.
   * \todo refactor: make 1st person controls distinct from orthographic or
   * other controls. \todo unit test \ingroup sdl-gl
   */
  class SdlGlCamera : public GlCamera {
    public:
      /** Helper that translates SDL_Event Mouse Motion events into GlCamera
       * mouse YAW/PITCH controller. \todo this is an example of what should be
       * refactored.
       */
      function<void(SDL_Event&)> const SdlMouseMotion{ [this](SDL_Event& e) {
        this->MouseMotionCtrl(e.motion.xrel, e.motion.yrel);
      } };
      /** Helper that translates SDL_Event Mouse Wheel events into GlCamera ZOOM
       * controller. \todo this is an example of what should be refactored.
       */
      function<void(SDL_Event&)> const SdlMouseWheel{ [this](SDL_Event& e) {
        this->MouseScrollZoom(e.wheel.y);
      } };
      /** This helper connects WASD to FORWARD LEFT BACK RIGHT on GlCamera.
       * \todo this is an example of what should be refactored.
       */
      function<void(shared_ptr<SdlEvtRoot>)> ConnectSdlEvtRoot{
        [this](shared_ptr<SdlEvtRoot> root) {
          auto& kbEvt = root->Key;
          kbEvt->Code(SDLK_w)->Down->VOID->On(this->ForwardMomentum);
          kbEvt->Code(SDLK_s)->Down->VOID->On(this->ReverseMomentum);
          kbEvt->Code(SDLK_a)->Down->VOID->On(this->LeftMomentum);
          kbEvt->Code(SDLK_d)->Down->VOID->On(this->RightMomentum);
          root->Mouse->Motion->On(this->SdlMouseMotion);
          root->Mouse->Wheel->On(this->SdlMouseWheel);
        }
      };
  };
}