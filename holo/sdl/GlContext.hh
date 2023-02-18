#pragma once
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

#include <holo/Gl.hh>
#include <holo/sdl/Window.hh>
#include <holo/sdl/GlSys.hh>

namespace holo {
  /** Engine-level Window wrapper.
   * \ingroup windows
   */
  class SdlGlContext : public SdlWindow {
    private:
      /** \note Inaccessible constructor */
      SdlGlContext(shared_ptr<SdlWin>);

    public: /** Typedefs **********************************/
      shared_ptr<SdlGlSys> const sdlGl { SdlGlSys::Get()};
      /** Strong ref. to `Pane` */
      using sPtr             = std::shared_ptr<SdlGlContext>;
      /** Weak ref. to `Pane` */
      using wPtr             = std::weak_ptr<SdlGlContext>;
      /** \todo Maybe make this a virtual function? */
      using RenderDispatcher = EvtAbstractType<SdlGlContext::sPtr>;



    public: /** Class-Methods *****************************/
      /** Create a window. **/
      static sPtr Create(std::string t, int x, int y, int w, int h, int f);
      /** Create window with default positions & flags */
      static sPtr Create(std::string t, int w, int h);
      static sPtr Create(std::string t, int w, int h, int f);
      /** Create window with default title, position, & flags */
      static sPtr Create(int w, int h);
      static sPtr Create(std::string t);
      static sPtr Create(std::string t, int f);
      static sPtr Create(int w, int h, int f);
      static sPtr Create(int f);

    private: /** Class-Methods*/
      static bool  glWasInit;
      static bool  initGl();
      virtual void Render() override;
      CallbackID renderID;
    public: /** Instance Methods *****************************************************/
      /** \brief Ensures `open` map is updated. */
      virtual ~SdlGlContext();

    public: /** Instance Methods ****************************************/
      void GlActivateContext();
      void GlSwap();

    public: /** Instance properties **********************/
      /** Render step callbacks */
      RenderDispatcher::sPtr const  preRender{ std::make_shared<RenderDispatcher>() };

      RenderDispatcher::sPtr const  postRender{ std::make_shared<RenderDispatcher>() };

      /** GLContext associated with window. */
      SDL_GLContext                 glContext;
  };
}
