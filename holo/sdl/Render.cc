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
#include <holo/ShareFiles.hh>
#include <holo/sdl/Render.hh>
namespace holo {
  /** \todo Replace logging with unit testing */
  SdlRender::SdlRender(shared_ptr<SdlWin> ptr)
    : SdlWindow::SdlWindow(ptr)
    , renderer{ make_shared<SdlRenderer>(*ptr, -1, 0) } {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }
  /** \todo Replace logging with unit testing */
  SdlRender::~SdlRender() {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }
  /** \todo Replace logging with unit testing
   * \todo Review how this uses `open`
   */
  shared_ptr<SdlRender> SdlRender::Create(
    std::string t, int x, int y, int w, int h, int f
  ) {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
    shared_ptr<SdlRender> created{
      new SdlRender(make_shared<SdlWin>(t, x, y, w, h, f))
    };
    open[created->GetID()] = created;
    return created;
  }
  /** ... default x,y & f */
  shared_ptr<SdlRender> SdlRender::Create(std::string t, int w, int h) {
    return Create(t, NEXT.x, NEXT.y, w, h, NEXT.f);
  }
  /** ... default w, h, & f */
  shared_ptr<SdlRender> SdlRender::Create(std::string t, int w, int h, int f) {
    return Create(t, NEXT.x, NEXT.y, w, h, f);
  }

  /** \todo Review how `Render` is implemented, possibly refactor.
   * \note calls `Clear` & `Present`, possibly remove this from here?
   */
  void SdlRender::Render() {
    renderer->Clear();
    // BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
    SdlWindow::Render();

    renderer->Present();
  }
  /** Load a texture for use with this renderer from a surface. */
  shared_ptr<SdlTexture> SdlRender::CreateTexture(SdlSurface surface) {
    return make_shared<SdlTexture>(*renderer, surface);
  }
  /** Load a texture for use with this renderer from a surface. */
  shared_ptr<SdlTexture> SdlRender::CreateTexture(shared_ptr<SdlSurface> surface
  ) {
    return make_shared<SdlTexture>(*renderer, *surface);
  }
  /** Load a texture for use with this renderer from a file. */
  shared_ptr<SdlTexture> SdlRender::LoadTexture(string path) {
    string found = ShareFiles::Require(path);
    return CreateTexture(make_shared<SdlSurface>(found));
  }

}