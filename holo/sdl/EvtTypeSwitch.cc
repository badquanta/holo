#include <holo/sdl/EvtTypeSwitch.hh>
namespace holo {
  SdlEvtTypeSwitch::SwitchTypeExtractor SdlEvtTypeSwitch::DefaultExtractor{
    [](SDL_Event& e) -> SDL_EventType { return (SDL_EventType)e.type; }
  };
  SdlEvtTypeSwitch::SdlEvtTypeSwitch(SwitchTypeExtractor extractor, const SpecialHandlers_t& sh)
    : EvtAbstractTypeSwitch<SDL_EventType, SDL_Event&>::EvtAbstractTypeSwitch(extractor, sh) {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }
  SdlEvtTypeSwitch::SdlEvtTypeSwitch()
    : SdlEvtTypeSwitch(DefaultExtractor, {}) {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }
  SdlEvtTypeSwitch::SdlEvtTypeSwitch(const SpecialHandlers_t& sh)
    : SdlEvtTypeSwitch(DefaultExtractor, sh) {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }
}