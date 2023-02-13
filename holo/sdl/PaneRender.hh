#pragma once
#include <holo/sdl/Pane.hh>
namespace holo {
  /** SDL Window & Renderer pair. */
  class SdlPaneRender : public SdlPane {
    public:
      using sPtr = std::shared_ptr<SdlPaneRender>;
      SdlRendererPtr                   renderer;
      /** Create a window. **/
      static shared_ptr<SdlPaneRender> Create(std::string t, int x, int y, int w, int h, int f);
      static shared_ptr<SdlPaneRender> Create(std::string t, int w, int h);

    private:
      SdlPaneRender(SdlWinPtr);

    public:
      virtual ~SdlPaneRender() override;
      virtual void Render() override;
  };
}