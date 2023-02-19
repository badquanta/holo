/** \file
 * \copyright
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
#pragma once
#include <SDL2pp/Font.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Surface.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Window.hh>
#include <holo/stdPrimitives.hh>

namespace holo {
  /** \ingroup sdl */
  using SdlPoint       = SDL2pp::Point;
  /** \ingroup sdl */
  using SdlRect        = SDL2pp::Rect;
  /** \ingroup sdl */
  using SdlSurface     = SDL2pp::Surface;
  /** \ingroup sdl */
  using SdlSurfacePtr  = std::shared_ptr<SDL2pp::Surface>;
  /** \ingroup sdl */
  using SdlRenderer    = SDL2pp::Renderer;
  /** \ingroup sdl */
  using SdlRendererPtr = std::shared_ptr<SDL2pp::Renderer>;
  /** \ingroup sdl */
  using SdlTexture     = SDL2pp::Texture;
  /** \ingroup sdl
   * \todo Refactor: possibly distinguish between SDL2pp and Holo SdlWindow
   * better.
   */
  using SdlWin         = SDL2pp::Window;
  /** \ingroup sdl */
  using SdlFont        = SDL2pp::Font;
  /** \ingroup sdl
   * \todo Refactor: Stop usage of Ptr/sPtr
   */
  using SdlWinPtr      = std::shared_ptr<SdlWin>;
}