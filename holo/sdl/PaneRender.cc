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
}