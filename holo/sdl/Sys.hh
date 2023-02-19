/** \copyright
 * \file
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
#include <holo/Arch.hh>
#include <holo/sdl/EvtRoot.hh>

namespace holo {
  /** SDL Initialization & Shutdown singleton.
   * \todo Refactor: I just don't like `Sys`
   * \ingroup sdl
   */
  class SdlSys {
    public:
      /** Depends on `Arch` instance. */
      shared_ptr<Arch> const                   arch{ Arch::Get() };
      /** Get/Construct singleton instance. */
      static shared_ptr<SdlSys>                Get();
      /** This static map is built to accommodate both `SdlWindow` event
       * dispatching.
       * \note Both creating new SdlWindow instances & processing
       * events referencing window IDs will cause this static map to contain a
       * SdlEvtRoot handler for that specific window id.
       * \note SdlWindow that are created will automatically reference its
       * `SdlEvtRoot` in this list as its `events` member.
       * **/
      static map<Uint32, weak_ptr<SdlEvtRoot>> mapWindowIdEvt;

    protected:
      /** inaccessible, singleton, utilize `Get` */
      SdlSys();
      /** singleton reference */
      static weak_ptr<SdlSys> instance;

    public:
      /** accessible for shared_ptr destruction */
      ~SdlSys();
      /** Process input?
       * \todo Shouldn't this be a static function? Is it being used?
       */
      void Input();

      /** ID of input callback? */
      CallbackID const                  InputID;
      /** SYSTEM EvtRoot.  Windows have their own too.
       * \todo Probably refactor this.. "EvtRoot?"
       */
      std::shared_ptr<SdlEvtRoot> const events{ std::make_shared<SdlEvtRoot>(
      ) };

      /** Reference to SDL2pp::SDL.
       * \todo if it needs to be yet-another shared_ptr
       */
      shared_ptr<SDL2pp::SDL> sdl{
        std::make_shared<SDL2pp::SDL>(SDL_INIT_EVERYTHING)
      };
      /** Reference to SDL2pp::TTF.
       * \todo if it needs to be yet-another shared_ptr
       */
      shared_ptr<SDL2pp::SDLTTF>   ttf{ std::make_shared<SDL2pp::SDLTTF>() };
      /** Reference to SDL2pp::SDLImage.
       * \todo if it needs to be yet-another shared_ptr
       */
      shared_ptr<SDL2pp::SDLImage> image{
        std::make_shared<SDL2pp::SDLImage>(IMG_INIT_PNG | IMG_INIT_JPG)
      };
      /** Reference to SDL2pp::SDLMixer.
       * \todo if it needs to be yet-another shared_ptr
       */
      shared_ptr<SDL2pp::SDLMixer> mixer{
        std::make_shared<SDL2pp::SDLMixer>(MIX_INIT_MP3 | MIX_INIT_OGG)
      };
  };
}