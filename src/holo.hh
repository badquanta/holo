/**
 * @todo Add GNU GPL stuff
 */
#pragma once

#include <boost/json.hpp>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2pp/Font.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/SDL.hh>
#include <SDL2pp/SDLImage.hh>
#include <SDL2pp/SDLMixer.hh>
#include <SDL2pp/SDLTTF.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Window.hh>
#include <holo-cfg.hh>
#include <iostream>
#include <memory>
#include <vector>

namespace holo {
  using namespace SDL2pp;
  class Deck {
    public:
      std::shared_ptr<SDL>      sdl;
      std::shared_ptr<SDLTTF>   ttf;
      std::shared_ptr<SDLImage> image;
      std::shared_ptr<SDLMixer> mixer;
      std::shared_ptr<Window>   mainWindow;
      std::shared_ptr<Renderer> mainRenderer;

    public:
      // SDL      sdl;
      // SDLTTF   ttf;
      // Renderer renderer;

      Deck();
      virtual ~Deck();

      Window& GetWindow();
      Renderer& GetRenderer();
  };
} // namespace holo