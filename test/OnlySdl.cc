#include <holo/sdl/PaneRender.hh>
using namespace holo;
int main(int ac, char**av){

  try {
    Arch::Configure(ac, av);
    SdlPaneRender::sPtr whPane{SdlPaneRender::Create("Sdl rendering tests.", 320, 200)};
    // Hitting escape in any window means the test failed.
    whPane->sdl->events->Key->Code(SDLK_ESCAPE)->Up->VOID->On([](){
        throw std::runtime_error("Escape key pressed.");
    });
    whPane->sdl->events->Quit->VOID->On(&Arch::RequestQuit);
    whPane->sdl->events->Key->Code(SDLK_RETURN)->Up->VOID->On(&Arch::RequestQuit);
    whPane->arch->Timeout(500,&Arch::RequestQuit);
    whPane->render->On([](){

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