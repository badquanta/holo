#include <holo/sdl/PaneRender.hh>
namespace holo {
  SdlPaneRender::SdlPaneRender(SdlWinPtr ptr)
    : SdlPane::SdlPane(ptr)
    , renderer{ make_shared<SdlRenderer>(*ptr, -1, 0) } {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }
  SdlPaneRender::~SdlPaneRender() {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }
  shared_ptr<SdlPaneRender> SdlPaneRender::Create(std::string t, int x, int y, int w, int h, int f) {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
    shared_ptr<SdlPaneRender> created{ new SdlPaneRender(make_shared<SdlWin>(t, x, y, w, h, f)) };
    open[created->GetID()] = created;
    return created;
  }
  shared_ptr<SdlPaneRender> SdlPaneRender::Create(std::string t, int w, int h) {
    return Create(t, NEXT.x, NEXT.y, w, h, NEXT.f);
  }

  void SdlPaneRender::Render(){
    //BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
    SdlPane::Render();
  }
}