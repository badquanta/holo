#include <holo/sdl/Pane.hh>
#include <holo/sdl/Sys.hh>
namespace holo {
  /** Protected */
  weak_ptr<SdlSys>                  SdlSys::instance;
  map<Uint32, weak_ptr<SdlEvtRoot>> SdlSys::mapWindowIdEvt;
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
      Uint32 winId = SdlEvt::GetWindowID(evt);
      if (winId != 0) {
        // Dispatch ONLY to the specified window ID
        if (mapWindowIdEvt.contains(winId)) {
          if (!(mapWindowIdEvt.at(winId).expired())) {
            mapWindowIdEvt[winId].lock()->Trigger(evt);
          }
        }
      } else {
        // Dispatch to ALL windows
        for (auto pair : mapWindowIdEvt) {
          if (!pair.second.expired())
            pair.second.lock()->Trigger(evt);
        }
      }
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