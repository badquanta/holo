#include <holo/sdl/PaneGl.hh>
int main(int ac, char** av) {
  try {
    using namespace holo;
    Arch::Configure(ac, av);
    shared_ptr<SdlPaneGl> pane{ SdlPaneGl::Create("Sdl & OpenGL tests..") };
    // Hitting escape in any window means the test
    // failed.
    pane->sdl->events->Key->Code(SDLK_ESCAPE)->Up->VOID->On([]() {
      throw std::runtime_error("Escape key pressed.");
    });
    pane->sdl->events->Quit->VOID->On(&Arch::RequestQuit);
    pane->sdl->events->Key->Code(SDLK_RETURN)->Up->VOID->On(&Arch::RequestQuit);



    pane->render->On([](){

    });

  } catch (holo::Arch::CliHelp& e) {
    std::cerr << "Runtime error: " << e << std::endl;
    return 1;
  } catch (std::exception& e) {
    std::cerr << "EXCEPTION: " << e.what() << std::endl;
    return 2;
  }
  return 0;
}