#include <holo/sdl/Pane.hh>

namespace holo {
  using namespace std::placeholders;
  map<Uint32, weak_ptr<SdlPane>> SdlPane::open;
  SdlPane::Defaults              SdlPane::NEXT;
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
    , SetSize{ bind(static_cast<SdlWin& (SdlWin::*)(const SdlPoint&)>(&SdlWin::SetSize), w, _1) }
    , GetBrightness{ bind(&SdlWin::GetBrightness, w) }
    , SetBrightness{ bind(&SdlWin::SetBrightness, w, _1) }
    , GetPosition{ bind(&SdlWin::GetPosition, w) }
    , SetPosition{ bind(
        static_cast<SdlWin& (SdlWin::*)(const SdlPoint&)>(&SdlWin::SetPosition), w, _1
      ) }
    , SetPositionXY{ bind(
        static_cast<SdlWin& (SdlWin::*)(int, int)>(&SdlWin::SetPosition), w, _1, _2
      ) }
    , GetMinimumSize{ bind(&SdlWin::GetMinimumSize, w) }
    , SetMinimumSizeWH{ bind(
        static_cast<SdlWin& (SdlWin::*)(int, int)>(&SdlWin::SetMinimumSize), w, _1, _2
      ) }
    , SetMinimumSize{ bind(
        static_cast<SdlWin& (SdlWin::*)(const SdlPoint&)>(&SdlWin::SetMaximumSize), w, _1
      ) }
    , GetMaximumSize{ bind(&SdlWin::GetMaximumSize, w) }
    , SetMaximumSizeWH{ bind(
        static_cast<SdlWin& (SdlWin::*)(int, int)>(&SdlWin::SetMaximumSize), w, _1, _2
      ) }
    , SetMaximumSize{ bind(
        static_cast<SdlWin& (SdlWin::*)(const SdlPoint&)>(&SdlWin::SetMaximumSize), w, _1
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
    sdl->windows[GetID()]=events;
    BOOST_LOG_TRIVIAL(trace) <<  __PRETTY_FUNCTION__ << " ID=" << GetID();
  }
  /** virtual */
  SdlPane::~SdlPane() {
    sdl->windows.erase(GetID());
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }
  /** virtual */
  Uint32 SdlPane::GetID() const {
    return SDL_GetWindowID(sdlWin->Get());
  }

}
