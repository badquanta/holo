/**
 * \author BadQuanta
 */
#pragma once
#include "SdlRootEvt.hh"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2pp/Font.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/SDL.hh>
#include <SDL2pp/SDLImage.hh>
#include <SDL2pp/SDLMixer.hh>
#include <SDL2pp/SDLTTF.hh>
#include <SDL2pp/Texture.hh>
#include <boost/log/trivial.hpp>
#include <boost/program_options.hpp>
namespace holo {
  /** Program/Engine wrapper
   * \ingroup general
   */
  class Program {
    public:
      using sRenderer = std::shared_ptr<SDL2pp::Renderer>;
      using sPtr      = std::shared_ptr<Program>;
      static sPtr Init();
      static bool Configure(int, char*[]);
      using CliHelp = boost::program_options::options_description;

    private:
      static sPtr instance;
      Program();

      std::shared_ptr<SDL2pp::SDL>      sdl{ std::make_shared<SDL2pp::SDL>(SDL_INIT_EVERYTHING) };
      std::shared_ptr<SDL2pp::SDLTTF>   ttf{ std::make_shared<SDL2pp::SDLTTF>() };
      std::shared_ptr<SDL2pp::SDLImage> image{
        std::make_shared<SDL2pp::SDLImage>(IMG_INIT_PNG | IMG_INIT_JPG)
      };
      std::shared_ptr<SDL2pp::SDLMixer> mixer{
        std::make_shared<SDL2pp::SDLMixer>(MIX_INIT_MP3 | MIX_INIT_OGG)
      };
      static bool quit;

    public:
      virtual ~Program();
      // SDL      sdl;
      // SDLTTF   ttf;
      // Renderer renderer;
      VoidEvent::sPtr const             prePoll{ std::make_shared<VoidEvent>() };
      VoidEvent::sPtr const             preRender{ std::make_shared<VoidEvent>() };
      std::shared_ptr<SdlRootEvt> const events{ std::make_shared<SdlRootEvt>() };

      void                              MainLoop();
      void                              RequestQuit();
  };
}