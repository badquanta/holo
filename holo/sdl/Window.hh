#pragma once
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

#include <holo/Emitter.hh>
#include <holo/sdl/Sys.hh>
namespace holo {
  /** Common SDL.
   * \ingroup sdl
   * \todo probably refactor: SdlWindow vs SdlEmitter? Distinguish between Holo
   * wrapper and SDL2pp class.
   */
  class SdlWindow : public Emitter {
    public:
      /** SDL2pp interface
       * \todo probably refactoring to `window` in the future. */
      shared_ptr<SdlWin> const     sdlWin;
      /** Depends on `SdlSys` singleton .*/
      shared_ptr<SdlSys> const     sdl{ SdlSys::Get() };
      /** Event tree associated w+ith this window instance. */
      shared_ptr<SdlEvtRoot> const events{ make_shared<SdlEvtRoot>() };
      /** Dispatches an SDL_Event to the appropriate window(s)
       * \details
       *  If the event specifies a WindowID then it will be dispatched only to
       * that specific window. Otherwise all `open` instances of a Window will
       * receive the event.
       */
      static void                  Dispatch(SDL_Event& e);

    public: /** Class-Properties: Defaults for new window, if otherwise
               unspecified. */
      static struct Defaults {
          std::string title{ "Untitled" };
          int         x{ SDL_WINDOWPOS_CENTERED }, y{ SDL_WINDOWPOS_CENTERED },
            w{ 320 }, h{ 230 }, f{ 0 };
      } NEXT;

    protected:
      /** Inaccessible, use `Create`?*/
      SdlWindow(shared_ptr<SdlWin>);
      /** Instances of SDL Windows that are open.
       * \todo review this vs using the map on SdlSys? **/
      static map<Uint32, weak_ptr<SdlWindow>> open;

    public:
      /** Destructor */
      virtual ~SdlWindow() override;
      /** Retrieve the Window ID */
      Uint32 GetID() const;

    public: /** CONVIENCE FORWARDERS to SDL2pp::Window instance */
      /** \brief Convience accessors to methods on `SDL2pp::Window` instance
       * \return[SdlPoint]
       * \fn SdlPoint GetSize() **/
      function<SdlPoint()> const                  GetSize;
      /** \brief Get the width of the window
       * \returns int
       * \fn int GetWidth
       */
      // function<int()> const                       GetWidth;
      virtual float                               GetWidth() override;
      /** Get the height of the window.
       * \returns int
       * \fn int GetHeight
       */
      // function<int()> const                       GetHeight;
      virtual float                               GetHeight() override;
      /** Get the drawable size * \fn SdlPoint GetDrawableSize()
       * \see https://wiki.libsdl.org/SDL2/SDL_GL_GetDrawableSize
       * \see
       * https://sdl2pp.amdmi3.ru/classSDL2pp_1_1Window.html#a5b75c003e803029db8a54230dcf2ba7e
       */
      function<SdlPoint()> const                  GetDrawableSize;
      /** Get drawable width \fn int GetDrawableWidth */
      function<int()> const                       GetDrawableWidth;
      /** Get drawable height \fn int GetDrawableHeight */
      function<int()> const                       GetDrawableHeight;
      /** Set window title \fn SDL2pp::Window& SetTitle
       * \param[const] std::string& title */
      function<SdlWin&(const std::string&)> const SetTitle;
      /** Get window title \fn std::string GetTitle */
      function<std::string()> const               GetTitle;
      /** Maximize \fn SDL2pp::Window& Maximize */
      function<SdlWin&()> const                   Maximize;
      /** Minimize \fn SDL2pp::Window& Minimize */
      function<SdlWin&()> const                   Minimize;
      /** \see https://sdl2pp.amdmi3.ru/classSDL2pp_1_1Window.html */
      function<SdlWin&()> const                   Hide;
      /** \see https://sdl2pp.amdmi3.ru/classSDL2pp_1_1Window.html */
      function<SdlWin&()> const                   Restore;
      /** \see https://sdl2pp.amdmi3.ru/classSDL2pp_1_1Window.html */
      function<SdlWin&()> const                   Raise;
      /** \see https://sdl2pp.amdmi3.ru/classSDL2pp_1_1Window.html */
      function<SdlWin&()> const                   Show;
      /** \see https://sdl2pp.amdmi3.ru/classSDL2pp_1_1Window.html */
      function<SdlWin&(Uint32)> const             SetFullscreen;
      /** \see https://sdl2pp.amdmi3.ru/classSDL2pp_1_1Window.html */
      function<SdlWin&(const SdlPoint&)> const    SetSize;
      /** \see https://sdl2pp.amdmi3.ru/classSDL2pp_1_1Window.html */
      function<SdlWin&(int, int)> const           SetSizeWH;
      /** \see https://sdl2pp.amdmi3.ru/classSDL2pp_1_1Window.html */
      function<float()> const                     GetBrightness;
      /** \see https://sdl2pp.amdmi3.ru/classSDL2pp_1_1Window.html */
      function<SdlWin&(float)> const              SetBrightness;
      /** \see https://sdl2pp.amdmi3.ru/classSDL2pp_1_1Window.html */
      function<SdlPoint()> const                  GetPosition;
      /** \see https://sdl2pp.amdmi3.ru/classSDL2pp_1_1Window.html */
      function<SdlWin&(int, int)> const           SetPositionXY;
      /** \see https://sdl2pp.amdmi3.ru/classSDL2pp_1_1Window.html */
      function<SdlWin&(const SdlPoint&)> const    SetPosition;
      /** \see https://sdl2pp.amdmi3.ru/classSDL2pp_1_1Window.html */
      function<SdlPoint()> const                  GetMinimumSize;
      /** \see https://sdl2pp.amdmi3.ru/classSDL2pp_1_1Window.html */
      function<SdlWin&(int, int)> const           SetMinimumSizeWH;
      /** \see https://sdl2pp.amdmi3.ru/classSDL2pp_1_1Window.html */
      function<SdlWin&(const SdlPoint&)> const    SetMinimumSize;
      /** \see https://sdl2pp.amdmi3.ru/classSDL2pp_1_1Window.html */
      function<SdlPoint()> const                  GetMaximumSize;
      /** \see https://sdl2pp.amdmi3.ru/classSDL2pp_1_1Window.html */
      function<SdlWin&(int, int)> const           SetMaximumSizeWH;
      /** \see https://sdl2pp.amdmi3.ru/classSDL2pp_1_1Window.html */
      function<SdlWin&(const SdlPoint&)> const    SetMaximumSize;
      /** \see https://sdl2pp.amdmi3.ru/classSDL2pp_1_1Window.html */
      function<bool()> const                      GetGrab;
      /** \see https://sdl2pp.amdmi3.ru/classSDL2pp_1_1Window.html */
      function<SdlWin&(bool)> const               SetGrab;
      /** \see https://sdl2pp.amdmi3.ru/classSDL2pp_1_1Window.html */
      function<int()> const                       GetDisplayIndex;
      /** \see https://sdl2pp.amdmi3.ru/classSDL2pp_1_1Window.html */
      function<void(SDL_DisplayMode&)> const      GetDisplayMode;
      /** \see https://sdl2pp.amdmi3.ru/classSDL2pp_1_1Window.html */
      function<Uint32()> const                    GetFlags;
      /** \see https://sdl2pp.amdmi3.ru/classSDL2pp_1_1Window.html */
      function<SdlWin&(const SdlSurface&)> const  SetIcon;
      /** \see https://sdl2pp.amdmi3.ru/classSDL2pp_1_1Window.html */
      function<SdlWin&(bool)> const               SetBordered;

#if SDL_VERSION_ATLEAST(2, 0, 5)
      /** \see https://sdl2pp.amdmi3.ru/classSDL2pp_1_1Window.html */
      function<SdlWin&(float)> const SetOpacity;
      /** \see https://sdl2pp.amdmi3.ru/classSDL2pp_1_1Window.html */
      function<float()> const        GetOpacity;
      /** \see https://sdl2pp.amdmi3.ru/classSDL2pp_1_1Window.html */
      function<SdlWin&(bool)> const  SetResizable;

#endif
  };
}
