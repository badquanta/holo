/** \copyright
holo
Copyright (C) 2023  Jon David Sawyer

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/
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