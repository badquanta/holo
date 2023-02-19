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
#include <holo/sdl/GlSys.hh>
#include <holo/sdl/Window.hh>

namespace holo {
  /** Sdl window with OpenGL context.
   * \todo unit test
   * \ingroup sdl-gl
   */
  class SdlGlContext : public SdlWindow {
    private:
      /** \note Inaccessible constructor */
      SdlGlContext(shared_ptr<SdlWin>);

    public: /** Typedefs **********************************/
      shared_ptr<SdlGlSys> const sdlGl{ SdlGlSys::Get() };
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
      /** default position. */
      static sPtr Create(std::string t, int w, int h, int f);
      /** Create window with default title, position, & flags */
      static sPtr Create(int w, int h);
      /** default title and position.*/
      static sPtr Create(std::string t);
      /** default position, size, and flags. */
      static sPtr Create(std::string t, int f);
      /** default title and position. */
      static sPtr Create(int w, int h, int f);
      /** default title, position, and size*/
      static sPtr Create(int f);

    private: /** Class-Methods*/
      /** \todo refactor how we track if we already initialized GLEW?*/
      static bool  glWasInit;
      /** initialize GLEW */
      static bool  initGl();
      /** \todo review overridden Render, consider if we should override in
       * SdlWindow */
      virtual void Render() override;
      /** \todo I think this should be removed*/
      CallbackID   renderID;

    public: /** Instance Methods
               *****************************************************/
      /** \brief Ensures `open` map is updated. */
      virtual ~SdlGlContext();

    public: /** Instance Methods ****************************************/
      /** \todo Better name: `Activate()`, `Use()`, or `Bind()`? */
      void GlActivateContext();
      /** Update opengl buffers.*/
      void GlSwap();

    public: /** Instance properties **********************/
      /** \todo refactor & move these to `Emitter` */
      RenderDispatcher::sPtr const preRender{
        std::make_shared<RenderDispatcher>()
      };
      /** \todo refactor & move these to `Emitter` */
      RenderDispatcher::sPtr const postRender{
        std::make_shared<RenderDispatcher>()
      };
      /** GLContext associated with window. */
      SDL_GLContext glContext;
  };
}
