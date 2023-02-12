#pragma once
#include <holo/sdl/Pane.hh>
namespace holo {
  /** SDL Window & Renderer pair. */
  class SdlPaneRender : public SdlPane {
    public:
      using sPtr = std::shared_ptr<SdlPaneRender>;
      SdlRendererPtr renderer;
      /** Create a window. **/
      static sPtr    Create(std::string t, int x, int y, int w, int h, int f);

    private:
      SdlPaneRender(SdlWinPtr);

    public:
      virtual ~SdlPaneRender() override;
  };
}