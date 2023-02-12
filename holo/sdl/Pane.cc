#include <holo/sdl/Pane.hh>

namespace holo {
  using namespace std::placeholders;
  map<Uint32, weak_ptr<SdlPane>> SdlPane::open;
  /** inaccessible */
  SdlPane::SdlPane(SdlWinPtr w)
    : sdlWin{ w }
    , GetSize{ bind(&SdlWin::GetSize, w) }
    , GetWidth{ bind(&SdlWin::GetWidth, w) }
    , GetHeight{ bind(&SdlWin::GetHeight, w) }
    , GetDrawableSize{ bind(&SdlWin::GetDrawableSize, w) }
    , GetDrawableWidth{ bind(&SdlWin::GetDrawableWidth, w) }
    , GetDrawableHeight{ bind(&SdlWin::GetDrawableHeight, w) }
    , SetTitle{ bind(&SdlWin::SetTitle, w, _1) }
    , GetTitle{ bind(&SdlWin::GetTitle, w) }
    , Maximize{ bind(&SdlWin::Maximize, w) }
    , Minimize{ bind(&SdlWin::Minimize, w) }
    , Hide{ bind(&SdlWin::Hide, w) }
    , Restore{ bind(&SdlWin::Restore, w) }
    , Raise{ bind(&SdlWin::Raise, w) }
    , Show{ bind(&SdlWin::Show, w) }
    , SetFullscreen{ bind(&SdlWin::SetFullscreen, w, _1) }
    , SetSizeWH{ bind(static_cast<SdlWin& (SdlWin::*)(int, int)>(&SdlWin::SetSize), w, _1, _2) }
    , SetSize{ bind(static_cast<SdlWin& (SdlWin::*)(const Point&)>(&SdlWin::SetSize), w, _1) }
    , GetBrightness{ bind(&SdlWin::GetBrightness, w) }
    , SetBrightness{ bind(&SdlWin::SetBrightness, w, _1) }
    , GetPosition{ bind(&SdlWin::GetPosition, w) }
    , SetPosition{ bind(
        static_cast<SdlWin& (SdlWin::*)(const Point&)>(&SdlWin::SetPosition), w, _1
      ) }
    , SetPositionXY{ bind(
        static_cast<SdlWin& (SdlWin::*)(int, int)>(&SdlWin::SetPosition), w, _1, _2
      ) }
    , GetMinimumSize{ bind(&SdlWin::GetMinimumSize, w) }
    , SetMinimumSizeWH{ bind(
        static_cast<SdlWin& (SdlWin::*)(int, int)>(&SdlWin::SetMinimumSize), w, _1, _2
      ) }
    , SetMinimumSize{ bind(
        static_cast<SdlWin& (SdlWin::*)(const Point&)>(&SdlWin::SetMaximumSize), w, _1
      ) }
    , GetMaximumSize{ bind(&SdlWin::GetMaximumSize, w) }
    , SetMaximumSizeWH{ bind(
        static_cast<SdlWin& (SdlWin::*)(int, int)>(&SdlWin::SetMaximumSize), w, _1, _2
      ) }
    , SetMaximumSize{ bind(
        static_cast<SdlWin& (SdlWin::*)(const Point&)>(&SdlWin::SetMaximumSize), w, _1
      ) }
    , GetGrab{ bind(&SdlWin::GetGrab, w) }
    , SetGrab{ bind(&SdlWin::SetGrab, w, _1) }
    , GetDisplayIndex{ bind(&SdlWin::GetDisplayIndex, w) }
    , GetDisplayMode{ bind(&SdlWin::GetDisplayMode, w, _1) }
    , GetFlags{ bind(&SdlWin::GetFlags, w) }
    , SetIcon{ bind(&SdlWin::SetIcon, w, _1) }
    , SetBordered{ bind(&SdlWin::SetBordered, w, _1) }
#if SDL_VERSION_ATLEAST(2, 0, 5)
    , SetOpacity{ bind(&SdlWin::SetOpacity, w, _1) }
    , GetOpacity{ bind(&SdlWin::GetOpacity, w) }
    , SetResizable{ bind(&SdlWin::SetResizable, w, _1) }
#endif
  {

    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }
  /** virtual */
  SdlPane::~SdlPane() {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }
  /** virtual */
  Uint32 SdlPane::GetID() const {
    return SDL_GetWindowID(sdlWin->Get());
  }

  void SdlPane::RenderAll() {
    for (auto pair : open) {
      if (!pair.second.expired()) {
        auto win = pair.second.lock();
        win->Render();
      }
    }
  }

  /**
   *
   */
  void SdlPane::Dispatch(SDL_Event& e) {
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
    if (winId != 0) {
      // Dispatch ONLY to the specified window ID
      if (open.contains(winId)) {
        if (!open.at(winId).expired()) {
          open[winId].lock()->events->Trigger(e);
        }
      }
    } else {
      // Dispatch to ALL windows
      for (auto pair : open) {
        if (!pair.second.expired())
          pair.second.lock()->events->Trigger(e);
      }
    }
}
}
