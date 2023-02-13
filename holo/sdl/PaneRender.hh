#pragma once
#include <holo/sdl/Pane.hh>
namespace holo {
  /** SDL Window & Renderer pair. */
  class SdlPaneRender : public SdlPane {
    public:
      using sPtr = shared_ptr<SdlPaneRender>;
      SdlRendererPtr                   renderer;
      /** Create a window. **/
      static shared_ptr<SdlPaneRender> Create(string t, int x, int y, int w, int h, int f);
      static shared_ptr<SdlPaneRender> Create(string t, int w, int h, int f);
      static shared_ptr<SdlPaneRender> Create(string t, int w, int h);

      shared_ptr<SdlTexture> CreateTexture(shared_ptr<SdlSurface>);
      shared_ptr<SdlTexture> LoadTexture(string);

    private:
      SdlPaneRender(SdlWinPtr);

    public:
      virtual ~SdlPaneRender() override;
      virtual void Render() override;
  };
}