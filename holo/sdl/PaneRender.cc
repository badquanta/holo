#include <holo/sdl/PaneRender.hh>
namespace holo {
  SdlPaneRender::SdlPaneRender(shared_ptr<SdlWin> ptr)
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

  shared_ptr<SdlPaneRender> SdlPaneRender::Create(std::string t, int w, int h, int f) {
    return Create(t, NEXT.x, NEXT.y, w, h, f);
  }

  void SdlPaneRender::Render(){
    renderer->Clear();
    //BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
    SdlPane::Render();

    renderer->Present();
  }
  shared_ptr<SdlTexture> SdlPaneRender::CreateTexture(SdlSurface surface){
    return make_shared<SdlTexture>(*renderer, surface);
  }
  shared_ptr<SdlTexture> SdlPaneRender::CreateTexture(shared_ptr<SdlSurface> surface){
    return make_shared<SdlTexture>(*renderer, *surface);
  }

  shared_ptr<SdlTexture> SdlPaneRender::LoadTexture(string path){
    string found = Arch::FindPath(path);
    return CreateTexture(make_shared<SdlSurface>(found));
  }

}