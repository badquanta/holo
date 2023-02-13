#include <holo/sdl/Evt.hh>
namespace holo {
  Uint32 SdlEvt::GetWindowID(SDL_Event& e) {
    Uint32 winId = 0;
    switch (e.type) {
      case SDL_DROPBEGIN:
      case SDL_DROPFILE:
      case SDL_DROPTEXT:
      case SDL_DROPCOMPLETE:
        winId = e.drop.windowID;
        break;
      case SDL_MOUSEWHEEL:
        winId = e.wheel.windowID;
        break;
      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP:
        winId = e.button.windowID;
        break;
      case SDL_MOUSEMOTION:
        winId = e.motion.windowID;
        break;
      case SDL_TEXTINPUT:
        winId = e.text.windowID;
        break;
      case SDL_TEXTEDITING_EXT:
        winId = e.editExt.windowID;
        break;
      case SDL_TEXTEDITING:
        winId = e.edit.windowID;
        break;
      case SDL_KEYDOWN:
      case SDL_KEYUP:
        winId = e.key.windowID;
        break;
      case SDL_WINDOWEVENT:
        winId = e.window.windowID;
        break;
    }
    if ((e.type >= SDL_USEREVENT) && (e.type < SDL_LASTEVENT)) {
      winId = e.user.windowID;
    }
    return winId;
  }
}