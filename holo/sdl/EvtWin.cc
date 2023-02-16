#include <holo/sdl/EvtWin.hh>
namespace holo {
  /** \todo review implementation of window events*/
  SdlEvtWin::SdlEvtWin()
    : EvtAbstractTypeSwitch::EvtAbstractTypeSwitch(
        [](SDL_Event& e) -> SDL_WindowEventID {
          if (e.type != SDL_WINDOWEVENT)
            return (SDL_WindowEventID)0;
          return (SDL_WindowEventID)e.window.event;
        }

      ) {
    SpecialHandlers = SpecialHandlers_t{
      {          SDL_WINDOWEVENT_SHOWN,          Shown},
      {         SDL_WINDOWEVENT_HIDDEN,         Hidden},
      {        SDL_WINDOWEVENT_EXPOSED,        Exposed},
      {          SDL_WINDOWEVENT_MOVED,          Moved},
      {        SDL_WINDOWEVENT_RESIZED,        Resized},
      {   SDL_WINDOWEVENT_SIZE_CHANGED,    SizeChanged},
      {      SDL_WINDOWEVENT_MINIMIZED,      Minimized},
      {      SDL_WINDOWEVENT_MAXIMIZED,      Maximized},
      {       SDL_WINDOWEVENT_RESTORED,       Restored},
      {          SDL_WINDOWEVENT_ENTER,          Enter},
      {   SDL_WINDOWEVENT_FOCUS_GAINED,    FocusGained},
      {     SDL_WINDOWEVENT_FOCUS_LOST,      FocusLost},
      {          SDL_WINDOWEVENT_CLOSE,          Close},
      {     SDL_WINDOWEVENT_TAKE_FOCUS,      TakeFocus},
      {       SDL_WINDOWEVENT_HIT_TEST,        HitTest},
      {SDL_WINDOWEVENT_ICCPROF_CHANGED, IccProfChanged}
    };
  }
  /**
  SDL_WindowEventID SdlEvtWin::ExtractSwitch(SDL_Event& e) const {
    assert(e.type == SDL_WINDOWEVENT);
    assert(e.window.event != SDL_WINDOWEVENT_NONE);
    return (SDL_WindowEventID)e.window.event;
  }
  **/
}