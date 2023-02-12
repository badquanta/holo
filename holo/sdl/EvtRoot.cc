#include <holo/sdl/EvtRoot.hh>
namespace holo {
  SdlEvtRoot::SdlEvtRoot() {
    /** \todo Examine why passing the following to the parent via a constructor failed. */
    SpecialHandlers = {
      {                    SDL_QUIT,          Quit},
      {         SDL_APP_TERMINATING,           App},
      {           SDL_APP_LOWMEMORY,           App},
      { SDL_APP_WILLENTERBACKGROUND,           App},
      {  SDL_APP_DIDENTERBACKGROUND,           App},
      { SDL_APP_WILLENTERFOREGROUND,           App},
      {  SDL_APP_DIDENTERFOREGROUND,           App},

      {           SDL_LOCALECHANGED, LocaleChanged},

      {            SDL_DISPLAYEVENT,       Display},

      {             SDL_WINDOWEVENT,        Window},

      {              SDL_SYSWMEVENT,         SysWm},

      {                 SDL_KEYDOWN,           Key},
      {                   SDL_KEYUP,           Key},

      {             SDL_TEXTEDITING,          Text},
      {               SDL_TEXTINPUT,          Text},

      {           SDL_KEYMAPCHANGED, KeymapChanged},

      {             SDL_MOUSEMOTION,         Mouse},
      {         SDL_MOUSEBUTTONDOWN,         Mouse},
      {           SDL_MOUSEBUTTONUP,         Mouse},
      {              SDL_MOUSEWHEEL,         Mouse},

      {           SDL_JOYAXISMOTION,           Joy},
      {           SDL_JOYBALLMOTION,           Joy},
      {            SDL_JOYHATMOTION,           Joy},
      {           SDL_JOYBUTTONDOWN,           Joy},
      {             SDL_JOYBUTTONUP,           Joy},
      {       SDL_JOYBATTERYUPDATED,           Joy},

      {    SDL_CONTROLLERAXISMOTION,    Controller},
      {    SDL_CONTROLLERBUTTONDOWN,    Controller},
      {      SDL_CONTROLLERBUTTONUP,    Controller},
      {   SDL_CONTROLLERDEVICEADDED,    Controller},
      {SDL_CONTROLLERDEVICEREMAPPED,    Controller},
      { SDL_CONTROLLERDEVICEREMOVED,    Controller},
      {  SDL_CONTROLLERTOUCHPADDOWN,    Controller},
      {    SDL_CONTROLLERTOUCHPADUP,    Controller},
      {SDL_CONTROLLERTOUCHPADMOTION,    Controller},
      {  SDL_CONTROLLERSENSORUPDATE,    Controller},

      {              SDL_FINGERDOWN,        Finger},
      {                SDL_FINGERUP,        Finger},
      {            SDL_FINGERMOTION,        Finger},

      {           SDL_DOLLARGESTURE,       Gesture},
      {            SDL_DOLLARRECORD,       Gesture},
      {            SDL_MULTIGESTURE,       Gesture},

      {         SDL_CLIPBOARDUPDATE,     Clipboard},

      {                SDL_DROPFILE,          Drop},
      {                SDL_DROPTEXT,          Drop},
      {               SDL_DROPBEGIN,          Drop},
      {            SDL_DROPCOMPLETE,          Drop},

      {        SDL_AUDIODEVICEADDED,         Audio},
      {      SDL_AUDIODEVICEREMOVED,         Audio},

      {            SDL_SENSORUPDATE,        Sensor},

      {    SDL_RENDER_TARGETS_RESET,        Render},
      {     SDL_RENDER_DEVICE_RESET,        Render}
    };
  }

  SDL_EventType SdlEvtRoot::ExtractSwitch(SDL_Event& e) const {
    return (SDL_EventType)e.type;
  }
}