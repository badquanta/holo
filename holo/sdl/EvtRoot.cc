#include <holo/sdl/EvtRoot.hh>
namespace holo {
  SdlEvtRoot::SdlEvtRoot()
    : SdlEvtTypeSwitch(SpecialHandlers_t{
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
  }) {}

  map<SDL_EventType, string> SdlEventTypeNames{
    {                    SDL_QUIT,                        "quit"},
    {         SDL_APP_TERMINATING,             "app Terminating"},
    {           SDL_APP_LOWMEMORY,              "app low memory"},
    { SDL_APP_WILLENTERBACKGROUND,  "app will enter background."},
    {  SDL_APP_DIDENTERBACKGROUND,    "app did enter background"},
    { SDL_APP_WILLENTERFOREGROUND,   "app will enter foreground"},
    {  SDL_APP_DIDENTERFOREGROUND,    "app did enter foreground"},
    {           SDL_LOCALECHANGED,              "locale changed"},
    {            SDL_DISPLAYEVENT,               "display event"},
    {             SDL_WINDOWEVENT,                      "window"},
    {              SDL_SYSWMEVENT,                      "sys wm"},
    {                 SDL_KEYDOWN,                    "key down"},
    {                   SDL_KEYUP,                      "key up"},
    {             SDL_TEXTEDITING,                "Text editing"},
    {               SDL_TEXTINPUT,                  "Text input"},
    {           SDL_KEYMAPCHANGED,              "keymap changed"},
    {             SDL_MOUSEMOTION,                "mouse motion"},
    {         SDL_MOUSEBUTTONDOWN,           "mouse button down"},
    {           SDL_MOUSEBUTTONUP,             "mouse button up"},
    {              SDL_MOUSEWHEEL,                 "mouse wheel"},
    {           SDL_JOYAXISMOTION,             "Joy axis motion"},
    {           SDL_JOYBALLMOTION,        "Joy axis ball motion"},
    {            SDL_JOYHATMOTION,              "joy hat motion"},
    {           SDL_JOYBUTTONDOWN,             "joy button down"},
    {             SDL_JOYBUTTONUP,               "joy button up"},
    {       SDL_JOYBATTERYUPDATED,         "joy battery updated"},
    {    SDL_CONTROLLERAXISMOTION,      "controller axis motion"},
    {    SDL_CONTROLLERBUTTONDOWN,      "controller button down"},
    {      SDL_CONTROLLERBUTTONUP,        "controller button up"},
    {   SDL_CONTROLLERDEVICEADDED,     "controller device added"},
    {SDL_CONTROLLERDEVICEREMAPPED,  "controller device remapped"},
    { SDL_CONTROLLERDEVICEREMOVED,   "controller device removed"},
    {  SDL_CONTROLLERTOUCHPADDOWN,   "controller touch pad down"},
    {    SDL_CONTROLLERTOUCHPADUP,     "controller touch pad up"},
    {SDL_CONTROLLERTOUCHPADMOTION, "controller touch pad motion"},
    {  SDL_CONTROLLERSENSORUPDATE,    "controller sensor update"},
    {              SDL_FINGERDOWN,                 "finger down"},
    {                SDL_FINGERUP,                   "finger up"},
    {            SDL_FINGERMOTION,               "finger motion"},
    {           SDL_DOLLARGESTURE,              "dollar gesture"},
    {            SDL_DOLLARRECORD,               "dollar record"},
    {            SDL_MULTIGESTURE,                "multigesture"},
    {         SDL_CLIPBOARDUPDATE,                   "Clipboard"},
    {                SDL_DROPFILE,                   "Drop file"},
    {                SDL_DROPTEXT,                   "Drop text"},
    {               SDL_DROPBEGIN,                  "Drop begin"},
    {            SDL_DROPCOMPLETE,               "Drop complete"},
    {        SDL_AUDIODEVICEADDED,          "Audio device added"},
    {      SDL_AUDIODEVICEREMOVED,        "Audio device removed"},
    {            SDL_SENSORUPDATE,               "Sensor update"},
    {    SDL_RENDER_TARGETS_RESET,        "Render targets reset"},
    {     SDL_RENDER_DEVICE_RESET,         "Render device reset"}
  };
  stringstream SdlEvtCommonToString(SDL_Event& e) {
    stringstream str("sdl event ");
    str << SdlEventTypeNames[(SDL_EventType)e.type];
    str << " Timestamp: " << e.timestamp;
    return str;
  }
  string SdlEvtBasicToString(SDL_Event& e) {
    return SdlEvtCommonToString(e).str();
  }
  string SdlEvtDisplayToString(SDL_Event& e) {
    stringstream strm{ SdlEvtCommonToString(e) };
    strm << "id#" << e.display.display;
    switch (e.display.event) {
      case SDL_DISPLAYEVENT_CONNECTED:
        strm << " connected";
        break;
      case SDL_DISPLAYEVENT_DISCONNECTED:
        strm << " disconnected";
        break;
      case SDL_DISPLAYEVENT_ORIENTATION:
        strm << " orientation changed";
        break;
      default:
        strm << " unknown display event#" << e.display.event;
    }
    return strm.str();
  }
  string SdlEvtWindowToString(SDL_Event&e){
    stringstream strm{SdlEvtBasicToString(e)};

  }
  map<SDL_EventType, function<string(SDL_Event& e)>> SdlEventTypeToStrings{
    {                    SDL_QUIT,   &SdlEvtBasicToString},
    {         SDL_APP_TERMINATING,   &SdlEvtBasicToString},
    {           SDL_APP_LOWMEMORY,   &SdlEvtBasicToString},
    { SDL_APP_WILLENTERBACKGROUND,   &SdlEvtBasicToString},
    {  SDL_APP_DIDENTERBACKGROUND,   &SdlEvtBasicToString},
    { SDL_APP_WILLENTERFOREGROUND,   &SdlEvtBasicToString},
    {  SDL_APP_DIDENTERFOREGROUND,   &SdlEvtBasicToString},
    {           SDL_LOCALECHANGED,   &SdlEvtBasicToString},
    {            SDL_DISPLAYEVENT, &SdlEvtDisplayToString},
    {             SDL_WINDOWEVENT,                 Window},
    {              SDL_SYSWMEVENT,                  SysWm},
    {                 SDL_KEYDOWN,                    Key},
    {                   SDL_KEYUP,                    Key},
    {             SDL_TEXTEDITING,                   Text},
    {               SDL_TEXTINPUT,                   Text},
    {           SDL_KEYMAPCHANGED,          KeymapChanged},
    {             SDL_MOUSEMOTION,                  Mouse},
    {         SDL_MOUSEBUTTONDOWN,                  Mouse},
    {           SDL_MOUSEBUTTONUP,                  Mouse},
    {              SDL_MOUSEWHEEL,                  Mouse},
    {           SDL_JOYAXISMOTION,                    Joy},
    {           SDL_JOYBALLMOTION,                    Joy},
    {            SDL_JOYHATMOTION,                    Joy},
    {           SDL_JOYBUTTONDOWN,                    Joy},
    {             SDL_JOYBUTTONUP,                    Joy},
    {       SDL_JOYBATTERYUPDATED,                    Joy},
    {    SDL_CONTROLLERAXISMOTION,             Controller},
    {    SDL_CONTROLLERBUTTONDOWN,             Controller},
    {      SDL_CONTROLLERBUTTONUP,             Controller},
    {   SDL_CONTROLLERDEVICEADDED,             Controller},
    {SDL_CONTROLLERDEVICEREMAPPED,             Controller},
    { SDL_CONTROLLERDEVICEREMOVED,             Controller},
    {  SDL_CONTROLLERTOUCHPADDOWN,             Controller},
    {    SDL_CONTROLLERTOUCHPADUP,             Controller},
    {SDL_CONTROLLERTOUCHPADMOTION,             Controller},
    {  SDL_CONTROLLERSENSORUPDATE,             Controller},
    {              SDL_FINGERDOWN,                 Finger},
    {                SDL_FINGERUP,                 Finger},
    {            SDL_FINGERMOTION,                 Finger},
    {           SDL_DOLLARGESTURE,                Gesture},
    {            SDL_DOLLARRECORD,                Gesture},
    {            SDL_MULTIGESTURE,                Gesture},
    {         SDL_CLIPBOARDUPDATE,              Clipboard},
    {                SDL_DROPFILE,                   Drop},
    {                SDL_DROPTEXT,                   Drop},
    {               SDL_DROPBEGIN,                   Drop},
    {            SDL_DROPCOMPLETE,                   Drop},
    {        SDL_AUDIODEVICEADDED,                  Audio},
    {      SDL_AUDIODEVICEREMOVED,                  Audio},
    {            SDL_SENSORUPDATE,                 Sensor},
    {    SDL_RENDER_TARGETS_RESET,                 Render},
    {     SDL_RENDER_DEVICE_RESET,                 Render}
  };
}