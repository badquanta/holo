/** \copyright
holo
Copyright (C) 2023  Jon David Sawyer

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/
#include <holo/sdl/Window.hh>

namespace holo {
  using namespace std::placeholders;
  map<Uint32, weak_ptr<SdlWindow>> SdlWindow::open;
  SdlWindow::Defaults              SdlWindow::NEXT;
  /** inaccessible */
  SdlWindow::SdlWindow(shared_ptr<SdlWin> w)
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
    sdl->mapWindowIdEvt[GetID()]=events;
    BOOST_LOG_TRIVIAL(trace) <<  __PRETTY_FUNCTION__ << " ID=" << GetID();
  }
  /** virtual */
  SdlWindow::~SdlWindow() {
    sdl->mapWindowIdEvt.erase(GetID());
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }
  /** virtual */
  Uint32 SdlWindow::GetID() const {
    return SDL_GetWindowID(sdlWin->Get());
  }

}
