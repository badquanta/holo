#pragma once
#include <holo/Gl.hh>
#include <holo/sdl/Pane.hh>
#include <holo/sdl/GlSys.hh>
namespace holo {
  /** Engine-level Window wrapper.
   * \ingroup windows
   */
  class SdlPaneGl : public SdlPane {
    private:
      /** \note Inaccessible constructor */
      SdlPaneGl(SdlWinPtr);

    public: /** Typedefs **********************************/
      shared_ptr<SdlGlSys> const sdlGl { SdlGlSys::Get()};
      /** Strong ref. to `Pane` */
      using sPtr             = std::shared_ptr<SdlPaneGl>;
      /** Weak ref. to `Pane` */
      using wPtr             = std::weak_ptr<SdlPaneGl>;
      /** \todo Maybe make this a virtual function? */
      using RenderDispatcher = EvtAbstractType<SdlPaneGl::sPtr>;



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
      virtual ~SdlPaneGl();

    private: /** Instance Methods ****************************************/
      void GlActivateContext();
      void GlSwap();

    public: /** Instance properties **********************/
      /** Reference to the `Program` singleton. */

      /** Render step callbacks */
      RenderDispatcher::sPtr const  preRender{ std::make_shared<RenderDispatcher>() };

      //RenderDispatcher::sPtr const  render{ std::make_shared<RenderDispatcher>() };
      RenderDispatcher::sPtr const  postRender{ std::make_shared<RenderDispatcher>() };
      /** Strong ref. to `SDL2pp::Window` */
      std::shared_ptr<SdlWin> const sdlWin;
      /** GLContext associated with window. */
      SDL_GLContext                 glContext;
  };
}
