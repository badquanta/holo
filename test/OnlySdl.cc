#include <holo/sdl/Render.hh>
#include <holo/ShareFiles.hh>
using namespace holo;
class entity {
  public:
    shared_ptr<SdlTexture> const text;
    SdlRect                      srcRect;
    SdlPoint                     size;
    SdlPoint                     position{ 0, 0 };
    entity(shared_ptr<SdlTexture> t)
      : text{ t }
      , size{ t->GetSize() }, srcRect {{0,0},t->GetSize()} {}
    SdlRect GetDestRect() { return SdlRect{ position, size }; }
};
int main(int ac, char** av) {
  try {
    Arch::Configure(ac, av);
    auto whPane{ SdlRender::Create("Sdl rendering tests.", 320, 200, SDL_WINDOW_RESIZABLE) };
    auto fontHackRegular{ make_shared<SdlFont>(ShareFiles::Require("share/Hack-Regular.ttf"), 24, 0) };
    auto msgEnterSkip{ whPane->CreateTexture(
      fontHackRegular->RenderUTF8_Blended("Press enter to skip.", { 255, 255, 255, 255 })
    ) };

    // Background texture:
    auto   background{ whPane->LoadTexture("share/textures/PlasmaRGB.512x512.png") };
    auto   background2{ whPane->LoadTexture("share/textures/PlasmaRGBA.512x512.png") };
    entity something{ whPane->LoadTexture("share/textures/Untitled.png") };
    whPane->sdl->events->Quit->VOID->On(&Arch::RequestQuit);
    whPane->sdl->events->Key->Code(SDLK_RETURN)->Up->VOID->On(&Arch::RequestQuit);
    SdlPoint bg2Offset{0,0};
    whPane->events->Key->Code(SDLK_LEFT)->Down->VOID->On([&bg2Offset](){
      bg2Offset += {-1,0};
    });
    whPane->events->Key->Code(SDLK_RIGHT)->Down->VOID->On([&bg2Offset](){
      bg2Offset += {1,0};
    });
    whPane->render->On([&]() {
      whPane->renderer->Copy(*background);
      whPane->renderer->FillCopy(
        *background2,
        SdlRect{
          {0, 0},
          background2->GetSize()
      },
        SdlRect{ { 0, 0 }, whPane->GetSize() }, bg2Offset, 0
      );
      // SdlPoint size = msgEnterSkip->GetSize();
      // SdlRect  srcRect{
      //    {0, 0},
      //   size
      // };
      // SdlRect destRect{
      //   SdlPoint{30, 30},
      //   size
      // };
      // whPane->renderer->Copy(*msgEnterSkip, srcRect, destRect);

      // SdlRect srcRect = something.srcRect;
      // SdlRect dstRect = something.GetDestRect();
      whPane->renderer->Copy(*something.text, something.srcRect, something.GetDestRect());
    });
    // Hitting escape in any window means the test failed.
    whPane->sdl->events->Key->Code(SDLK_ESCAPE)->Up->VOID->On([]() {
      throw std::runtime_error("Escape key pressed.");
      // SdlRect rect = msgEnterSkip->GetSize();
    });
    auto QUIT_TIMEOUT_ID = whPane->arch->Timeout(5000, &Arch::RequestQuit);
    whPane->events->Key->Code(SDLK_SPACE)->Up->VOID->Once([QUIT_TIMEOUT_ID]() {
      if (Arch::Get()->CancelTimeout(QUIT_TIMEOUT_ID)) {
        std::cout << "QUIT TIMEOUT CANCELED\n";
      } else {
        std::cout << "QUIT TIMEOUT ALREADY CANCELED\n";
      };
    });
    whPane->arch->MainLoop();

  } catch (Arch::CliHelp& e) {
    std::cout << "Usage: " << e << std::endl;
    return 0;
  } catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}