#pragma once
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2pp/SDL.hh>
#include <SDL2pp/SDLImage.hh>
#include <SDL2pp/SDLMixer.hh>
#include <SDL2pp/SDLTTF.hh>
#include <holo/sdl/EvtRoot.hh>
#include <holo/Arch.hh>

namespace holo {
  class SdlSys {
    public:
      shared_ptr<Arch> const    arch{ Arch::Get() };
      static shared_ptr<SdlSys> Get();
      static map<Uint32, weak_ptr<SdlEvtRoot>> mapWindowIdEvt;
    protected:
      SdlSys();
      static weak_ptr<SdlSys> instance;

    public:
      ~SdlSys();
      void                              Input();

      CallbackID const                  InputID;
      std::shared_ptr<SdlEvtRoot> const events{ std::make_shared<SdlEvtRoot>() };
      shared_ptr<SDL2pp::SDL>           sdl{ std::make_shared<SDL2pp::SDL>(SDL_INIT_EVERYTHING) };
      shared_ptr<SDL2pp::SDLTTF>        ttf{ std::make_shared<SDL2pp::SDLTTF>() };
      shared_ptr<SDL2pp::SDLImage>      image{
        std::make_shared<SDL2pp::SDLImage>(IMG_INIT_PNG | IMG_INIT_JPG)
      };
      shared_ptr<SDL2pp::SDLMixer> mixer{
        std::make_shared<SDL2pp::SDLMixer>(MIX_INIT_MP3 | MIX_INIT_OGG)
      };
  };
}