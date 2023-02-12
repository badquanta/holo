#include <holo/sdl/Sys.hh>
#include <holo/sdl/Pane.hh>
namespace holo {
 /** Protected */
  weak_ptr<SdlSys> SdlSys::instance;
  /** */
  SdlSys::SdlSys()
    : InputID{ arch->Input->On(bind(&SdlSys::Input, this)) } {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }
  /** */
  SdlSys::~SdlSys() {
    arch->Input->Off(InputID);
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }
  /** */
  void SdlSys::Input() {
    SDL_Event evt;
    while (SDL_PollEvent(&evt)) {
      events->Trigger(evt);
      SdlPane::Dispatch(evt);
    }
  }

  shared_ptr<SdlSys> SdlSys::Get() {
    shared_ptr<SdlSys> loaded;
    if (instance.expired()) {
      loaded   = shared_ptr<SdlSys>(new SdlSys());
      instance = loaded;
      return loaded;
    } else {
      loaded = instance.lock();
    }

    return loaded;
  }
}