#pragma once
#include <holo/sdl/Evt.hh>
namespace holo {
  class SdlEvtTypeSwitch :public EvtAbstractTypeSwitch<SDL_EventType, SDL_Event&>{
    public:
    static SwitchTypeExtractor DefaultExtractor;
    SdlEvtTypeSwitch(SwitchTypeExtractor extractor, const SpecialHandlers_t&sh={});
    SdlEvtTypeSwitch();
    SdlEvtTypeSwitch(const SpecialHandlers_t&sh);
  };
}
