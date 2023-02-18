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

#include <holo/sdl/Window.hh>
namespace holo {
  /** SDL Window & Renderer pair. */
  class SdlRender : public SdlWindow {
    public:
      using sPtr = shared_ptr<SdlRender>;
      SdlRendererPtr                   renderer;
      /** Create a window. **/
      static shared_ptr<SdlRender> Create(string t, int x, int y, int w, int h, int f);
      static shared_ptr<SdlRender> Create(string t, int w, int h, int f);
      static shared_ptr<SdlRender> Create(string t, int w, int h);

      shared_ptr<SdlTexture> CreateTexture(shared_ptr<SdlSurface>);
      shared_ptr<SdlTexture> CreateTexture(SdlSurface);
      shared_ptr<SdlTexture> LoadTexture(string);

    private:
      SdlRender(shared_ptr<SdlWin>);

    public:
      virtual ~SdlRender() override;
      virtual void Render() override;
  };
}