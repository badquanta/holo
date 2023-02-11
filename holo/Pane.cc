#include "Pane.hh"
#include <boost/log/trivial.hpp>
#include <exception>
#include <functional>
namespace holo {
  using namespace std::placeholders;
  using std::bind;
  Pane::Pane() {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }

  Pane::~Pane() {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }
  /** inaccessible */
  SdlPane::SdlPane(SdlWinPtr w)
    : sdlWin{ w }
    , GetSize{ bind(&SdlWin::GetSize, w) }
    , GetWidth{ bind(&SdlWin::GetWidth, w) }
    , GetHeight{ bind(&SdlWin::GetHeight, w) }
    , GetDrawableSize{ bind(&SdlWin::GetDrawableSize, w) }
    , GetDrawableWidth{ bind(&SdlWin::GetDrawableWidth, w) }
    , GetDrawableHeight{ bind(&SdlWin::GetDrawableHeight, w) }
    , SetTitle{ bind(&SdlWin::SetTitle, w, _1) }
    , GetTitle{ bind(&SdlWin::GetTitle, w) }
    , Maximize{ bind(&SdlWin::Maximize, w) }
    , Minimize{ bind(&SdlWin::Minimize, w) }
    , Hide{ bind(&SdlWin::Hide, w) }
    , Restore{ bind(&SdlWin::Restore, w) }
    , Raise{ bind(&SdlWin::Raise, w) }
    , Show{ bind(&SdlWin::Show, w) }
    , SetFullscreen{ bind(&SdlWin::SetFullscreen, w, _1) }
    , SetSizeWH{ bind(static_cast<SdlWin& (SdlWin::*)(int, int)>(&SdlWin::SetSize), w, _1, _2) }
    , SetSize{ bind(static_cast<SdlWin& (SdlWin::*)(const Point&)>(&SdlWin::SetSize), w, _1) }
    , GetBrightness{ bind(&SdlWin::GetBrightness, w) }
    , SetBrightness{ bind(&SdlWin::SetBrightness, w, _1) }
    , GetPosition{ bind(&SdlWin::GetPosition, w) }
    , SetPosition{ bind(
        static_cast<SdlWin& (SdlWin::*)(const Point&)>(&SdlWin::SetPosition), w, _1
      ) }
    , SetPositionXY{ bind(
        static_cast<SdlWin& (SdlWin::*)(int, int)>(&SdlWin::SetPosition), w, _1, _2
      ) }
    , GetMinimumSize{ bind(&SdlWin::GetMinimumSize, w) }
    , SetMinimumSizeWH{ bind(
        static_cast<SdlWin& (SdlWin::*)(int, int)>(&SdlWin::SetMinimumSize), w, _1, _2
      ) }
    , SetMinimumSize{ bind(
        static_cast<SdlWin& (SdlWin::*)(const Point&)>(&SdlWin::SetMaximumSize), w, _1
      ) }
    , GetMaximumSize{ bind(&SdlWin::GetMaximumSize, w) }
    , SetMaximumSizeWH{ bind(
        static_cast<SdlWin& (SdlWin::*)(int, int)>(&SdlWin::SetMaximumSize), w, _1, _2
      ) }
    , SetMaximumSize{ bind(
        static_cast<SdlWin& (SdlWin::*)(const Point&)>(&SdlWin::SetMaximumSize), w, _1
      ) }
    , GetGrab{ bind(&SdlWin::GetGrab, w) }
    , SetGrab{ bind(&SdlWin::SetGrab, w, _1) }
    , GetDisplayIndex{ bind(&SdlWin::GetDisplayIndex, w) }
    , GetDisplayMode{ bind(&SdlWin::GetDisplayMode, w, _1) }
    , GetFlags{ bind(&SdlWin::GetFlags, w) }
    , SetIcon{ bind(&SdlWin::SetIcon, w, _1) }
    , SetBordered{ bind(&SdlWin::SetBordered, w, _1) }
#if SDL_VERSION_ATLEAST(2, 0, 5)
    , SetOpacity{ bind(&SdlWin::SetOpacity, w, _1) }
    , GetOpacity{ bind(&SdlWin::GetOpacity, w) }
    , SetResizable{ bind(&SdlWin::SetResizable, w, _1) }
#endif
  {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }
  /** virtual */
  SdlPane::~SdlPane() {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }
  /** virtual */
  Uint32 SdlPane::GetID() const {
    return SDL_GetWindowID(sdlWin->Get());
  }

  std::map<Uint32, SdlPane::wPtr> SdlPane::open;
  SdlGlPane::Defaults             SdlGlPane::NEXT;
  /** CONSTRUCT a window.
   * \details
   *  Creates an OpenGL context.
   */
  SdlGlPane::SdlGlPane(std::shared_ptr<SdlWin> w)
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
  bool SdlGlPane::glWasInit{ false };
  bool SdlGlPane::initGl() {
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
  /**
   *
   */
  void SdlGlPane::Dispatch(SDL_Event& e) {
    Uint32 winId = 0;
    switch (e.type) {
      case SDL_DROPBEGIN:
      case SDL_DROPFILE:
      case SDL_DROPTEXT:
      case SDL_DROPCOMPLETE:
        winId = e.drop.windowID;
        break;
      case SDL_MOUSEWHEEL:
        winId = e.wheel.windowID;
        break;
      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP:
        winId = e.button.windowID;
        break;
      case SDL_MOUSEMOTION:
        winId = e.motion.windowID;
        break;
      case SDL_TEXTINPUT:
        winId = e.text.windowID;
        break;
      case SDL_TEXTEDITING_EXT:
        winId = e.editExt.windowID;
        break;
      case SDL_TEXTEDITING:
        winId = e.edit.windowID;
        break;
      case SDL_KEYDOWN:
      case SDL_KEYUP:
        winId = e.key.windowID;
        break;
      case SDL_WINDOWEVENT:
        winId = e.window.windowID;
        break;
    }
    if ((e.type >= SDL_USEREVENT) && (e.type < SDL_LASTEVENT)) {
      winId = e.user.windowID;
    }
    if (winId != 0) {
      // Dispatch ONLY to the specified window ID
      if (open.contains(winId)) {
        if (!open.at(winId).expired()) {
          open[winId].lock()->events->Trigger(e);
        }
      }
    } else {
      // Dispatch to ALL windows
      for (auto pair : open) {
        if (!pair.second.expired())
          pair.second.lock()->events->Trigger(e);
      }
    }
  }

  void SdlGlPane::GlActivateContext() {

    if (SDL_GL_MakeCurrent(sdlWin->Get(), glContext) != 0) {
      throw std::runtime_error(SDL_GetError());
    }
  }
  void SdlGlPane::GlSwap() {
    SDL_GL_SwapWindow(sdlWin->Get());
  }

  void SdlGlPane::RenderAll() {
    for (auto pair : open) {
      if (!pair.second.expired()) {
        SdlGlPane::sPtr win = pair.second.lock();
        win->GlActivateContext();
        win->preRender->Trigger(win);
        win->render->Trigger(win);
        win->postRender->Trigger(win);
        win->GlSwap();
      }
    }
  }

  SdlGlPane::~SdlGlPane() {
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
  SdlGlPane::sPtr SdlGlPane::Create(std::string t, int x, int y, int w, int h, int f) {
    BOOST_LOG_TRIVIAL(trace) << "Window::Create(t='" << t << "', x=" << x << ", y=" << y
                             << ", w=" << w << ", h=" << h << ", f=" << f << ")";
    sPtr tmp(new SdlGlPane(std::make_shared<SdlWin>(t, x, y, w, h, f | SDL_WINDOW_OPENGL)));
    open[tmp->GetID()] = tmp;
    return tmp;
  }
  SdlGlPane::sPtr SdlGlPane::Create(std::string t, int w, int h, int f) {
    return Create(t, NEXT.x, NEXT.y, w, h, f);
  }
  SdlGlPane::sPtr SdlGlPane::Create(std::string t, int w, int h) {
    return Create(t, NEXT.x, NEXT.y, w, h, NEXT.f);
  }

  SdlGlPane::sPtr SdlGlPane::Create(int w, int h) {
    return Create("Untitled", w, h);
  }

}