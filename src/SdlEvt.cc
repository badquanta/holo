#include "SdlEvt.hh"
#include <utility>
#include <assert.h>
namespace holo {

  /**
   * \brief Dispatch specific WindowEvents to handlers.
   **/
  void SdlWindowEvt::Trigger(SDL_Event& e) const {
    assert(e.type == SDL_WINDOWEVENT);
    assert(e.window.event != SDL_WINDOWEVENT_NONE);
    switch (e.window.event) {
      case SDL_WINDOWEVENT_SHOWN:
        Shown->Trigger(e);
        break;
      case SDL_WINDOWEVENT_HIDDEN:
        Hidden->Trigger(e);
        break;
      case SDL_WINDOWEVENT_EXPOSED: /**< Window has been exposed and should be redrawn */
        Exposed->Trigger(e);
        break;
      case SDL_WINDOWEVENT_MOVED: /**< Window has been moved to data1, data2*/
        Moved->Trigger(e);
        break;
      case SDL_WINDOWEVENT_RESIZED: /**< Window has been resized to data1xdata2 */
        Resized->Trigger(e);
        break;
      case SDL_WINDOWEVENT_SIZE_CHANGED: /**< The window size has changed, either as
                                           a result of an API call or through the
                                           system or user changing the window size. */
        SizeChanged->Trigger(e);
        break;
      case SDL_WINDOWEVENT_MINIMIZED: /**< Window has been minimized */
        Minimized->Trigger(e);
        break;
      case SDL_WINDOWEVENT_MAXIMIZED: /**< Window has been maximized */
        Maximized->Trigger(e);
        break;
      case SDL_WINDOWEVENT_RESTORED: /**< Window has been restored to normal size
                                     and position */
        Restored->Trigger(e);
        break;
      case SDL_WINDOWEVENT_ENTER: /**< Window has gained mouse focus */
        Enter->Trigger(e);
        break;
      case SDL_WINDOWEVENT_FOCUS_GAINED:
      case SDL_WINDOWEVENT_FOCUS_LOST: /**< Window has lost keyboard focus */
        FocusLost->Trigger(e);
        break;
      case SDL_WINDOWEVENT_CLOSE: /**< The window manager requests that the window be closed */
        Close->Trigger(e);
        break;
      case SDL_WINDOWEVENT_TAKE_FOCUS: /**< Window is being offered a focus (should
                                     SetWindowInputFocus() on itself or a subwindow, or ignore) */
        TakeFocus->Trigger(e);
        break;
      case SDL_WINDOWEVENT_HIT_TEST: /**< Window had a hit test that wasn't SDL_HITTEST_NORMAL. */
        HitTest->Trigger(e);
        break;
      case SDL_WINDOWEVENT_ICCPROF_CHANGED: /**< The ICC profile of the window's display has
                                             * changed.*/
        IccChanged->Trigger(e);
        break;
      case SDL_WINDOWEVENT_DISPLAY_CHANGED: /**< Window has been moved to display data1. */
        DisplayChanged->Trigger(e);
        break;
      default:
        std::unreachable();
    }
    SdlEvt::Trigger(e);
  }

  void SdlKeyPressEvt::Trigger(SDL_Event& e) const {
    assert((e.type == SDL_KEYDOWN) || (e.type == SDL_KEYUP));
    switch (e.type) {
      case SDL_KEYDOWN:
        Down->Trigger(e);
        break;
      case SDL_KEYUP:
        Up->Trigger(e);
        break;
      default:
        std::unreachable();
    }
    SdlEvt::Trigger(e);
  }

  void SdlKeyEvt::Trigger(SDL_Event& e) const {
    assert((e.type == SDL_KEYDOWN) || (e.type == SDL_KEYUP));
    SDL_Keycode sym = e.key.keysym.sym;
    if (Sym.contains(sym)) {
      Sym.at(sym)->Trigger(e);
    }
    SdlKeyPressEvt::Trigger(e);
  }

  SdlKeyPressEvt::sPtr SdlKeyEvt::Key(SDL_Keycode code) {
    if (!Sym.contains(code)) {
      Sym[code] = std::make_shared<SdlKeyPressEvt>();
    }
    return Sym[code];
  }
}