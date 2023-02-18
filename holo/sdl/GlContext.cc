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
#include <holo/sdl/GlContext.hh>
namespace holo {
  void SdlGlContext::Render(){
    this->GlActivateContext();
    this->render->Trigger();
    this->GlSwap();
  }

  /** CONSTRUCT a window.
   * \details
   *  Creates an OpenGL context.
   */
  SdlGlContext::SdlGlContext(std::shared_ptr<SdlWin> w)
    : SdlWindow::SdlWindow(w) {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
    glContext = SDL_GL_CreateContext(w->Get());
    if (glContext == NULL) {
      throw new std::runtime_error(SDL_GetError());
    }
    GlActivateContext();
    if (!initGl())
      throw std::runtime_error("Failed to initialize OpenGL");
  }
  bool SdlGlContext::glWasInit{ false };
  bool SdlGlContext::initGl() {
    if (!glWasInit) {
      BOOST_LOG_TRIVIAL(trace) << "Initializing OpenGL";
      glewExperimental = GL_TRUE;
      GLenum glewError = glewInit();
      if (glewError != GLEW_OK) {
        throw std::runtime_error((char*)glewGetErrorString(glewError));
      }
      if (SDL_GL_SetSwapInterval(1) < 0) {
        BOOST_LOG_TRIVIAL(warning) << "Unable to set VSync: " << SDL_GetError();
      }
      glWasInit = true;
    } else {
      BOOST_LOG_TRIVIAL(info) << "OpenGL already initialized.";
    }
    return glWasInit;
  }

  void SdlGlContext::GlActivateContext() {
    if (SDL_GL_MakeCurrent(sdlWin->Get(), glContext) != 0) {
      string errStr{SDL_GetError()};
      throw std::runtime_error(SDL_GetError());
    }
  }
  void SdlGlContext::GlSwap() {
    SDL_GL_SwapWindow(sdlWin->Get());
  }


  SdlGlContext::~SdlGlContext() {
    BOOST_LOG_TRIVIAL(trace) << "Window destroyed";
    SDL_GL_DeleteContext(glContext);
    open.erase(GetID());
  }
  /**
   * \return Strong ref.
   * \param t Title for created window.
   * \param x Left
   * \param y Top
   * \param w Width
   * \param h Height
   * \param f Flags
   * \note Flags will always have `SDL_WINDOW_OPENGL` set.
   */
  SdlGlContext::sPtr SdlGlContext::Create(std::string t, int x, int y, int w, int h, int f) {
    BOOST_LOG_TRIVIAL(trace) << "Window::Create(t='" << t << "', x=" << x << ", y=" << y
                             << ", w=" << w << ", h=" << h << ", f=" << (f | SDL_WINDOW_OPENGL) << ")";
    sPtr tmp(new SdlGlContext(make_shared<SdlWin>(t, x, y, w, h, f | SDL_WINDOW_OPENGL)));
    open[tmp->GetID()] = tmp;
    return tmp;
  }
  SdlGlContext::sPtr SdlGlContext::Create(std::string t, int w, int h, int f) {
    return Create(t, NEXT.x, NEXT.y, w, h, f);
  }
  SdlGlContext::sPtr SdlGlContext::Create(std::string t, int w, int h) {
    return Create(t, NEXT.x, NEXT.y, w, h, NEXT.f);
  }
  shared_ptr<SdlGlContext> SdlGlContext::Create(std::string t){
    return Create(t, NEXT.x, NEXT.y, NEXT.w, NEXT.h, NEXT.f);
  }
  shared_ptr<SdlGlContext> SdlGlContext::Create(std::string t, int f){
    return Create(t, NEXT.x, NEXT.y, NEXT.w, NEXT.h, f);
  }

  SdlGlContext::sPtr SdlGlContext::Create(int w, int h) {
    return Create("Untitled", w, h);
  }
}
