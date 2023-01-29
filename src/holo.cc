#include "holo.hh"

namespace holo {
  Deck::Deck() {
    sdl        = std::make_shared<SDL>(SDL_INIT_EVERYTHING);
    ttf        = std::make_shared<SDLTTF>();
    image      = std::make_shared<SDLImage>(IMG_INIT_PNG | IMG_INIT_JPG);
    mixer      = std::make_shared<SDLMixer>(MIX_INIT_MP3 | MIX_INIT_OGG);
    mainWindow = std::make_shared<Window>(
      "holo-deck",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      640,
      480,
      SDL_WINDOW_RESIZABLE
    );
    mainRenderer =
      std::make_shared<Renderer>(*mainWindow, -1, SDL_RENDERER_ACCELERATED);
  }

  Deck::~Deck() {}

  Window& Deck::GetWindow(){
    return *mainWindow;
  }
  Renderer& Deck::GetRenderer(){
    return *mainRenderer;
  }

};
