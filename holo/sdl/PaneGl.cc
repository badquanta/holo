#include <holo/sdl/PaneGl.hh>
namespace holo {
  void SdlPaneGl::Render(){
    this->GlActivateContext();
    this->render->Trigger();
    this->GlSwap();
  }
  SdlPaneGl::Defaults SdlPaneGl::NEXT;
  /** CONSTRUCT a window.
   * \details
   *  Creates an OpenGL context.
   */
  SdlPaneGl::SdlPaneGl(std::shared_ptr<SdlWin> w)
    : SdlPane::SdlPane(w) {
    BOOST_LOG_TRIVIAL(trace) << "Window created.";
    glContext = SDL_GL_CreateContext(sdlWin->Get());
    if (glContext == NULL) {
      throw new std::runtime_error(SDL_GetError());
    }
    GlActivateContext();
    if (!initGl())
      throw std::runtime_error("Failed to initialize OpenGL");
  }
  bool SdlPaneGl::glWasInit{ false };
  bool SdlPaneGl::initGl() {
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

  void SdlPaneGl::GlActivateContext() {

    if (SDL_GL_MakeCurrent(sdlWin->Get(), glContext) != 0) {
      throw std::runtime_error(SDL_GetError());
    }
  }
  void SdlPaneGl::GlSwap() {
    SDL_GL_SwapWindow(sdlWin->Get());
  }


  SdlPaneGl::~SdlPaneGl() {
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
  SdlPaneGl::sPtr SdlPaneGl::Create(std::string t, int x, int y, int w, int h, int f) {
    BOOST_LOG_TRIVIAL(trace) << "Window::Create(t='" << t << "', x=" << x << ", y=" << y
                             << ", w=" << w << ", h=" << h << ", f=" << f << ")";
    sPtr tmp(new SdlPaneGl(std::make_shared<SdlWin>(t, x, y, w, h, f | SDL_WINDOW_OPENGL)));
    open[tmp->GetID()] = tmp;
    return tmp;
  }
  SdlPaneGl::sPtr SdlPaneGl::Create(std::string t, int w, int h, int f) {
    return Create(t, NEXT.x, NEXT.y, w, h, f);
  }
  SdlPaneGl::sPtr SdlPaneGl::Create(std::string t, int w, int h) {
    return Create(t, NEXT.x, NEXT.y, w, h, NEXT.f);
  }

  SdlPaneGl::sPtr SdlPaneGl::Create(int w, int h) {
    return Create("Untitled", w, h);
  }
}
