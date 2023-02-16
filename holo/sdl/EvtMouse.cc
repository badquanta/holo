#include <holo/sdl/EvtMouse.hh>
namespace holo {
  SdlEvtMouseButton::SdlEvtMouseButton() {
    SpecialHandlers = SpecialHandlers_t{
      {SDL_MOUSEBUTTONDOWN,   Up},
      {  SDL_MOUSEBUTTONUP, Down}
    };
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }

  shared_ptr<SdlEvtMouseButton> SdlEvtMouseButtonList::Get(Uint8 buttonID) {
    if (!mapButtonIDs.contains(buttonID)) {
      mapButtonIDs[buttonID] = make_shared<SdlEvtMouseButton>();
    }
    return mapButtonIDs[buttonID];
  }
  void SdlEvtMouseButtonList::Trigger(SDL_Event& e) {
    SdlEvtMouseButton::Trigger(e);
    Get(e.button.button)->Trigger(e);
  }
  void SdlEvtMouseButtonList::Off(CallbackID id) {
    SdlEvtMouseButton::Off(id);
    for (auto pair : mapButtonIDs) {
      pair.second->Off(id);
    }
  }

  SdlEvtMouse::SdlEvtMouse(){
    SpecialHandlers = SpecialHandlers_t{
      {    SDL_MOUSEMOTION, Motion},
      {SDL_MOUSEBUTTONDOWN, Button},
      {  SDL_MOUSEBUTTONUP, Button},
      {     SDL_MOUSEWHEEL,  Wheel}
    };
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }

  /** SdlEvtMouseList*/
  map<Uint32, shared_ptr<SdlEvtMouse>> SdlEvtMouseList::mapMouseIDs{};
  void                                 SdlEvtMouseList::Trigger(SDL_Event& e) {
    SdlEvtMouse::Trigger(e);
    Uint32 mid = SdlEvt::GetMouseID(e);
    if (mid != 0) {
      Get(mid)->Trigger(e);
    }
  }
  void SdlEvtMouseList::Off(CallbackID id) {
    SdlEvtMouseList::Off(id);
    for (auto pair : mapMouseIDs) {
      pair.second->Off(id);
    }
  }
  shared_ptr<SdlEvtMouse> SdlEvtMouseList::Get(Uint32 whichMouseID) {
    if (!mapMouseIDs.contains(whichMouseID)) {
      mapMouseIDs[whichMouseID] = make_shared<SdlEvtMouse>();
    }
    return mapMouseIDs[whichMouseID];
  }

}