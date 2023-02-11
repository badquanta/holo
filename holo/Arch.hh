/**
 * \author BadQuanta
 */
#pragma once
#include "holo/holo-cfg.hh"
#include "holo/sdl/Primitives.hh"
#include "holo/sdl/RootEvt.hh"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2pp/Font.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/SDL.hh>
#include <SDL2pp/SDLImage.hh>
#include <SDL2pp/SDLMixer.hh>
#include <SDL2pp/SDLTTF.hh>
#include <SDL2pp/Texture.hh>
#include <boost/filesystem.hpp>
#include <boost/log/trivial.hpp>
#include <boost/program_options.hpp>
#include <filesystem>
namespace holo {

  /** Program/Engine wrapper.
   * \ingroup general
   */
  class Arch {
    public:
      using sPtr      = std::shared_ptr<Arch>;
      using CliHelp   = boost::program_options::options_description;
      typedef Uint32                  TimeoutID;
      static std::vector<std::string> FileSearchPaths;

      static sPtr        Get();
      static bool        Configure(int, char*[]);
      static std::string FindPath(const std::string&);
      static std::string FindPath(
        const std::string& aPath, const std::vector<std::string>& searchPaths
      );
      SurfacePtr LoadImage(std::string image);
      CallbackID Timeout(unsigned int, VoidDispatcher::CallbackFunction);
      void       CallTimeouts();

    private:
      static sPtr instance;
      Arch();

      std::shared_ptr<SDL2pp::SDL>      sdl{ std::make_shared<SDL2pp::SDL>(SDL_INIT_EVERYTHING) };
      std::shared_ptr<SDL2pp::SDLTTF>   ttf{ std::make_shared<SDL2pp::SDLTTF>() };
      std::shared_ptr<SDL2pp::SDLImage> image{
        std::make_shared<SDL2pp::SDLImage>(IMG_INIT_PNG | IMG_INIT_JPG)
      };
      std::shared_ptr<SDL2pp::SDLMixer> mixer{
        std::make_shared<SDL2pp::SDLMixer>(MIX_INIT_MP3 | MIX_INIT_OGG)
      };
      static Uint32 exitRequestedAt;

      typedef std::map<Uint32, VoidDispatcher::CallbackFunction> TimeoutMap;
      TimeoutMap                                                 timedDispatches;
      Uint64                                                     cycles{ 0 };
      Uint64 const                                               reportEvery{ 100 };
      std::vector<Uint64>                                        lastCycleTicks{ reportEvery, 0 };

    public:
      virtual ~Arch();
      // SDL      sdl;
      // SDLTTF   ttf;
      // Renderer renderer;
      VoidDispatcher::sPtr const        prePoll{ std::make_shared<VoidDispatcher>() };
      VoidDispatcher::sPtr const        preRender{ std::make_shared<VoidDispatcher>() };
      std::shared_ptr<SdlRootEvt> const events{ std::make_shared<SdlRootEvt>() };
      VoidDispatcher::sPtr const        NEXT{ std::make_shared<VoidDispatcher>() };
      Uint64                            GetCycle();
      void                              MainLoop();
      static void                       RequestQuit();
      static void                       RequestQuitAt(Uint32);
      void                              CancelQuit();
  };
}