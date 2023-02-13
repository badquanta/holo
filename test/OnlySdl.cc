#include <holo/sdl/PaneRender.hh>
using namespace holo;
int main(int ac, char**av){

  try {
    Arch::Configure(ac, av);
    shared_ptr<SdlPaneRender> whPane{SdlPaneRender::Create("Sdl rendering tests.", 320, 200, SDL_WINDOW_RESIZABLE)};
    // Background texture:
    shared_ptr<SdlTexture> background = whPane->LoadTexture("share/textures/PlasmaRGB.640x480.png");
    // Hitting escape in any window means the test failed.
    whPane->sdl->events->Key->Code(SDLK_ESCAPE)->Up->VOID->On([](){
        throw std::runtime_error("Escape key pressed.");
    });
    whPane->sdl->events->Quit->VOID->On(&Arch::RequestQuit);
    whPane->sdl->events->Key->Code(SDLK_RETURN)->Up->VOID->On(&Arch::RequestQuit);
    whPane->arch->Timeout(5000,&Arch::RequestQuit);
    whPane->render->On([&whPane, &background](){
      whPane->renderer->Copy(*background);
    });

    whPane->arch->MainLoop();
  } catch (Arch::CliHelp&e){
    std::cout << "Usage: " << e << std::endl;
    return 0;
  } catch (std::exception &e){
    std::cerr << "Exception: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}