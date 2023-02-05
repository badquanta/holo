#pragma once
#include "Program.hh"
#include "GlProgram.hh"
#include <SDL2pp/Window.hh>
namespace holo {
  using SdlWin    = SDL2pp::Window;
  using SdlWinPtr = std::shared_ptr<SdlWin>;
  using Surface   = SDL2pp::Surface;
  using Point     = SDL2pp::Point;
  using std::function;

  /** Engine-level Window wrapper.
   * \ingroup windows
   */
  class Window {
    private:
      /** \note Inaccessible constructor */
      Window(std::shared_ptr<SdlWin>);

    public: /** Typedefs **********************************/
      /** Strong ref. to `Window` */
      using sPtr             = std::shared_ptr<Window>;
      /** Weak ref. to `Window` */
      using wPtr             = std::weak_ptr<Window>;
      /** \todo Maybe make this a virtual function? */
      using RenderDispatcher = BaseDispatcher<Window::sPtr>;

    public: /** Class-Methods *****************************/
      /** Create a window. **/
      static sPtr Create(std::string t, int x, int y, int w, int h, int f);
      /** Create window with default positions & flags */
      static sPtr Create(std::string t, int w, int h);
      /** Create window with default title, position, & flags */
      static sPtr Create(int w, int h);
      /** Dispatches an SDL_Event to the appropriate window(s)
       * \details
       *  If the event specifies a WindowID then it will be dispatched only to that specific window.
       *  Otherwise all `open` instances of a Window will receive the event.
       */
      static void Dispatch(SDL_Event& e);
      /** Calls the render void event of all `open` windows */
      static void RenderAll();

    private: /** Class-Methods*/
      static bool glWasInit;
      static bool initGl();

    public: /** Instance Methods *****************************************************/
      /** \brief Ensures `open` map is updated. */
      virtual ~Window();
      /** Retrieve the Window ID */
      Uint32 GetID();

    private: /** Instance Methods ****************************************/
      void GlActivateContext();
      void GlSwap();

    private: /** Static properties ************************************/
      static std::map<Uint32, wPtr> open;

    public: /** Instance properties **********************/
      /** Event tree associated with this window instance. */
      std::shared_ptr<SdlRootEvt> const events{ std::make_shared<SdlRootEvt>() };
      /** Reference to the `Program` singleton. */
      Program::sPtr const               program{ Program::Get() };
      /** Rendering callbacks */
      RenderDispatcher::sPtr const      render{ std::make_shared<RenderDispatcher>() };
      /** Strong ref. to `SDL2pp::Window` */
      std::shared_ptr<SdlWin> const     sdlWin;
      /** GLContext associated with window. */
      SDL_GLContext                     glContext;

    public: /** CONVIENCE FORWARDERS to SDL2pp::Window instance */
      /** \brief Convience accessors to methods on `SDL2pp::Window` instance
       * \return[Point]
       * \fn Point GetSize() **/
      function<Point()> const                     GetSize;
      /** \brief Get the width of the window
       * \returns int
       * \fn int GetWidth
       */
      function<int()> const                       GetWidth;
      /** Get the height of the window.
       * \returns int
       * \fn int GetHeight
       */
      function<int()> const                       GetHeight;
      /** Get the drawable size * \fn Point GetDrawableSize()
       * \see https://wiki.libsdl.org/SDL2/SDL_GL_GetDrawableSize
       * \see https://sdl2pp.amdmi3.ru/classSDL2pp_1_1Window.html#a5b75c003e803029db8a54230dcf2ba7e
       */
      function<Point()> const                     GetDrawableSize;
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
      /** */
      function<SdlWin&()> const                   Hide;
      function<SdlWin&()> const                   Restore;
      function<SdlWin&()> const                   Raise;
      function<SdlWin&()> const                   Show;
      function<SdlWin&(Uint32)> const             SetFullscreen;
      function<SdlWin&(const Point&)> const       SetSize;
      function<SdlWin&(int, int)> const           SetSizeWH;
      function<float()> const                     GetBrightness;
      function<SdlWin&(float)> const              SetBrightness;
      function<Point()> const                     GetPosition;
      function<SdlWin&(int, int)> const           SetPositionXY;
      function<SdlWin&(const Point&)> const       SetPosition;
      function<Point()> const                     GetMinimumSize;
      function<SdlWin&(int, int)> const           SetMinimumSizeWH;
      function<SdlWin&(const Point&)> const       SetMinimumSize;
      function<Point()> const                     GetMaximumSize;
      function<SdlWin&(int, int)> const           SetMaximumSizeWH;
      function<SdlWin&(const Point&)> const       SetMaximumSize;
      function<bool()> const                      GetGrab;
      function<SdlWin&(bool)> const               SetGrab;
      function<int()> const                       GetDisplayIndex;
      function<void(SDL_DisplayMode&)> const      GetDisplayMode;
      function<Uint32()> const                    GetFlags;
      function<SdlWin&(const Surface&)> const     SetIcon;
      function<SdlWin&(bool)> const               SetBordered;
#if SDL_VERSION_ATLEAST(2, 0, 5)
      function<SdlWin&(float)> const SetOpacity;
      function<float()> const        GetOpacity;
      function<SdlWin&(bool)> const  SetResizable;
#endif
  };

}