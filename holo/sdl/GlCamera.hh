#pragma once
#include <holo/gl/Camera.hh>
#include <holo/sdl/EvtRoot.hh>
namespace holo {
  class SdlGlCamera : public GlCamera {
    public:
      function<void(SDL_Event&)> const SdlMouseMotion{ [this](SDL_Event& e) {
        this->MouseMotionCtrl(e.motion.xrel, e.motion.yrel);
      } };
      function<void(SDL_Event&)> const SdlMouseWheel{ [this](SDL_Event& e) {
        this->MouseScrollZoom(e.wheel.y);
      } };
      function<void(shared_ptr<SdlEvtRoot>)> ConnectSdlEvtRoot{ [this](shared_ptr<SdlEvtRoot> root
                                                                ) {
        auto&                                kbEvt = root->Key;
        kbEvt->Code(SDLK_w)->Down->VOID->On(this->ForwardMomentum);
        kbEvt->Code(SDLK_s)->Down->VOID->On(this->ReverseMomentum);
        kbEvt->Code(SDLK_a)->Down->VOID->On(this->LeftMomentum);
        kbEvt->Code(SDLK_d)->Down->VOID->On(this->RightMomentum);
        root->Mouse->Motion->On(this->SdlMouseMotion);
        root->Mouse->Wheel->On(this->SdlMouseWheel);
      } };
  };
}