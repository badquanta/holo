#include "holo/Pane.hh"

int main(int ac, char**av){

  try {
    holo::Arch::Configure(ac, av);
    holo::SdlGlPane::sPtr whPane{holo::SdlGlPane::Create("Simple rendering pane.", 320, 200)};
    // Hitting escape in any window means the test failed.
    holo::VoidDispatcher::CallbackFunction requestQuit = &holo::Arch::RequestQuit;
    whPane->arch->events->Key->Code(SDLK_ESCAPE)->Up->VOID->On([](){
        throw std::runtime_error("Escape key pressed.");
    });
    whPane->arch->events->Quit->VOID->On(&holo::Arch::RequestQuit);
    whPane->arch->events->Key->Code(SDLK_RETURN)->Up->VOID->On(&holo::Arch::RequestQuit);
    whPane->arch->Timeout(10000,&holo::Arch::RequestQuit);
    whPane->render->On([](holo::SdlGlPane::sPtr pane){

    });

    whPane->arch->MainLoop();
  } catch (std::runtime_error &e){
    std::cout << "Failure: " << e.what() << std::endl;
    return 1;
  } catch (std::exception &e){
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return 0;
}