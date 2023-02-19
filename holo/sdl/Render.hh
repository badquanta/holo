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
  /** SDL Window & Renderer pair.
   * \todo Unit test holo::SdlRender
   * \ingroup sdl
   */
  class SdlRender : public SdlWindow {
    public:
      /** \todo Remove, stop using sPtr */
      using sPtr = shared_ptr<SdlRender>;
      /** \todo Refactor, use shared_ptr<...> instead. */
      SdlRendererPtr               renderer;
      /** Create a window & renderer pair. **/
      static shared_ptr<SdlRender> Create(
        string t, int x, int y, int w, int h, int f
      );
      /** ... default position */
      static shared_ptr<SdlRender> Create(string t, int w, int h, int f);
      /** ... default position & flags */
      static shared_ptr<SdlRender> Create(string t, int w, int h);
      /** Create a texture for this renderer from this shared surface. */
      shared_ptr<SdlTexture>       CreateTexture(shared_ptr<SdlSurface>);
      /** Create a texture for this render from this surface */
      shared_ptr<SdlTexture>       CreateTexture(SdlSurface);
      /** Load an image file directly as a texture. */
      shared_ptr<SdlTexture>       LoadTexture(string);

    private:
      /** inaccessible constructor, use Create instead.*/
      SdlRender(shared_ptr<SdlWin>);

    public:
      /** accessible destructor */
      virtual ~SdlRender() override;
      /** override `SdlWindow` and `Emitter` implementations.
       *  \todo: review of `Render` is implemented correctly in `SdlWindow`,
       * possibly refactor `Render` into `Emit` or something else.*/
      virtual void Render() override;
  };
}