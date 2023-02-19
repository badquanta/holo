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
#include <holo/sdl/EvtWin.hh>
namespace holo {
  /** \details provides a custom type value extractor.
   * \todo review implementation of window events
   * \note due to problem with initialization order `SpecialHandlers` is set by
   * copy instead of passed initializer list.
   * */
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
}