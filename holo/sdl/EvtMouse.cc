#include <holo/sdl/EvtMouse.hh>
namespace holo {
  SdlEvtMouseButton::SdlEvtMouseButton()
    : SdlEvtTypeSwitch(SpecialHandlers_t{
        {SDL_MOUSEBUTTONDOWN,   Up},
        {  SDL_MOUSEBUTTONUP, Down}
  }) {}

  shared_ptr<SdlEvtMouseButton> SdlEvtMouseButtonList::Get(Uint8 buttonID) {
    if (!mapButtonIDs.contains(buttonID)) {
      mapButtonIDs[buttonID] = make_shared<SdlEvtMouseButton>();
    }
    return mapButtonIDs[buttonID];
  }
  void SdlEvtMouseButtonList::Trigger(SDL_Event& e) {
    SdlEvtMouseButton::Trigger(e);
    Get(GetMouseButtonID(e))->Trigger(e);
  }
  void SdlEvtMouseButtonList::Off(CallbackID id) {
    SdlEvtMouseButton::Off(id);
    for (auto pair : mapButtonIDs) {
      pair.second->Off(id);
    }
  }

  SdlEvtMouse::SdlEvtMouse()
    : SdlEvtTypeSwitch(SpecialHandlers_t{
        {    SDL_MOUSEMOTION, Motion},
        {SDL_MOUSEBUTTONDOWN, Button},
        {  SDL_MOUSEBUTTONUP, Button},
        {     SDL_MOUSEWHEEL,  Wheel}
  }) {}

  SDL_EventType SdlEvtMouse::ExtractSwitch(SDL_Event& e) const {
    assert(
      (e.type == SDL_MOUSEMOTION) || (e.type == SDL_MOUSEBUTTONDOWN) ||
      (e.type == SDL_MOUSEBUTTONUP) || (e.type == SDL_MOUSEWHEEL)
    );
    return (SDL_EventType)e.type;
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