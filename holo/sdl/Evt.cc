#include <holo/sdl/Evt.hh>
/** \file
 *  \copyright
holo
Copyright (C) 2023  Jon David Sawyer

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/
namespace holo {
  Uint32 SdlEvt::GetMouseID(SDL_Event& e) {
    Uint32 mouseID = 0;
    switch (e.type) {
      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP:
        mouseID = e.button.which;
        break;
      case SDL_MOUSEMOTION:
        mouseID = e.motion.which;
        break;
      case SDL_MOUSEWHEEL:
        mouseID = e.wheel.which;
    }
    return mouseID;
  }
  Uint32 SdlEvt::GetWindowID(SDL_Event& e) {
    Uint32 winId = 0;
    switch (e.type) {
      case SDL_DROPBEGIN:
      case SDL_DROPFILE:
      case SDL_DROPTEXT:
      case SDL_DROPCOMPLETE:
        winId = e.drop.windowID;
        break;
      case SDL_MOUSEWHEEL:
        winId = e.wheel.windowID;
        break;
      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP:
        winId = e.button.windowID;
        break;
      case SDL_MOUSEMOTION:
        winId = e.motion.windowID;
        break;
      case SDL_TEXTINPUT:
        winId = e.text.windowID;
        break;
      case SDL_TEXTEDITING_EXT:
        winId = e.editExt.windowID;
        break;
      case SDL_TEXTEDITING:
        winId = e.edit.windowID;
        break;
      case SDL_KEYDOWN:
      case SDL_KEYUP:
        winId = e.key.windowID;
        break;
      case SDL_WINDOWEVENT:
        winId = e.window.windowID;
        break;
    }
    if ((e.type >= SDL_USEREVENT) && (e.type < SDL_LASTEVENT)) {
      winId = e.user.windowID;
    }
    return winId;
  }

  map<SDL_EventType, string> const mapEvtIdName{
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
    {          SDL_JOYDEVICEADDED,            "joy device added"},
    {        SDL_JOYDEVICEREMOVED,          "joy device removed"},
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
  string SdlEvt::GetEventID_string(SDL_EventType eType) {
    if (mapEvtIdName.contains(eType)) {
      return mapEvtIdName.at(eType);
    } else {
      return "UNKNOWN EVENT";
    }
  }
  stringstream SdlCommonEvtToStream(SDL_Event& e) {
    stringstream  str("SDL_Event");
    SDL_EventType eType{ (SDL_EventType)e.type };
    if (mapEvtIdName.contains(eType)) {
      str << "@" << e.common.timestamp << " " << mapEvtIdName.at(eType);
    } else {
      str << " UNKNOWN EVENT TYPE:" << eType;
    }
    return str;
  }
  string SdlCommonEvtToString(SDL_Event& e) {
    return SdlCommonEvtToStream(e).str();
  }
  string SdlEvtDisplayToString(SDL_Event& e) {
    stringstream strm{ SdlCommonEvtToStream(e) };
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
  map<SDL_WindowEventID, string> SdlWindowEventTypeNames{
    {          SDL_WINDOWEVENT_CLOSE,               "close"},
    {SDL_WINDOWEVENT_DISPLAY_CHANGED,     "display changed"},
    {          SDL_WINDOWEVENT_ENTER,               "enter"},
    {        SDL_WINDOWEVENT_EXPOSED,             "exposed"},
    {   SDL_WINDOWEVENT_FOCUS_GAINED,        "focus gained"},
    {     SDL_WINDOWEVENT_FOCUS_LOST,          "focus lost"},
    {         SDL_WINDOWEVENT_HIDDEN,              "hidden"},
    {       SDL_WINDOWEVENT_HIT_TEST,            "hit test"},
    {SDL_WINDOWEVENT_ICCPROF_CHANGED, "ICC profile changed"},
    {          SDL_WINDOWEVENT_LEAVE,               "leave"},
    {      SDL_WINDOWEVENT_MAXIMIZED,           "maximized"},
    {      SDL_WINDOWEVENT_MINIMIZED,           "minimized"},
    {          SDL_WINDOWEVENT_MOVED,               "moved"},
    {        SDL_WINDOWEVENT_RESIZED,             "resized"},
    {       SDL_WINDOWEVENT_RESTORED,            "restored"},
    {          SDL_WINDOWEVENT_SHOWN,               "shown"},
    {   SDL_WINDOWEVENT_SIZE_CHANGED,        "size changed"},
    {     SDL_WINDOWEVENT_TAKE_FOCUS,          "take focus"}
  };

  stringstream SdlEvtWindowToStream(SDL_Event& e) {
    stringstream strm{ SdlCommonEvtToStream(e) };
    strm << " " << SdlWindowEventTypeNames[(SDL_WindowEventID)e.window.event] << " ID#"
         << e.window.windowID;
    return strm;
  }

  string SdlEvtWindowToString(SDL_Event& e) {
    return SdlEvtWindowToStream(e).str();
  }
  string SdlWinEvtDisplayChangeToString(SDL_Event& e) {
    stringstream strm{ SdlEvtWindowToStream(e) };
    strm << " display#" << e.window.data1;
    return strm.str();
  }
  string SdlWinEvtMovedToString(SDL_Event& e) {
    stringstream strm{ SdlEvtWindowToStream(e) };
    strm << " to " << e.window.data1 << ", " << e.window.data2;
    return strm.str();
  }
  string SdlWinEvtResizedToString(SDL_Event& e) {
    stringstream strm{ SdlEvtWindowToStream(e) };
    strm << " to " << e.window.data1 << "x" << e.window.data2;
    return strm.str();
  }

  map<SDL_WindowEventID, function<string(SDL_Event& e)>> SdlWindowEventTypeToStrings{
    {          SDL_WINDOWEVENT_CLOSE,           &SdlEvtWindowToString},
    {SDL_WINDOWEVENT_DISPLAY_CHANGED, &SdlWinEvtDisplayChangeToString},
    {          SDL_WINDOWEVENT_ENTER,           &SdlEvtWindowToString},
    {        SDL_WINDOWEVENT_EXPOSED,           &SdlEvtWindowToString},
    {   SDL_WINDOWEVENT_FOCUS_GAINED,           &SdlEvtWindowToString},
    {     SDL_WINDOWEVENT_FOCUS_LOST,           &SdlEvtWindowToString},
    {         SDL_WINDOWEVENT_HIDDEN,           &SdlEvtWindowToString},
    {       SDL_WINDOWEVENT_HIT_TEST,           &SdlEvtWindowToString},
    {SDL_WINDOWEVENT_ICCPROF_CHANGED,           &SdlEvtWindowToString},
    {          SDL_WINDOWEVENT_LEAVE,           &SdlEvtWindowToString},
    {      SDL_WINDOWEVENT_MAXIMIZED,           &SdlEvtWindowToString},
    {      SDL_WINDOWEVENT_MINIMIZED,           &SdlEvtWindowToString},
    {          SDL_WINDOWEVENT_MOVED,         &SdlWinEvtMovedToString},
    {        SDL_WINDOWEVENT_RESIZED,       &SdlWinEvtResizedToString},
    {       SDL_WINDOWEVENT_RESTORED,           &SdlEvtWindowToString},
    {          SDL_WINDOWEVENT_SHOWN,           &SdlEvtWindowToString},
    {   SDL_WINDOWEVENT_SIZE_CHANGED,       &SdlWinEvtResizedToString},
    {     SDL_WINDOWEVENT_TAKE_FOCUS,           &SdlEvtWindowToString}
  };
  string SdlWinEvtToString(SDL_Event& e) {
    return SdlWindowEventTypeToStrings[(SDL_WindowEventID)e.window.event](e);
  }
  string SdlKeyEvtToString(SDL_Event& e) {
    stringstream strm{ SdlCommonEvtToStream(e) };
    strm << " windowID#" << e.key.windowID << " repeat#" << e.key.repeat
         << "key:" << e.key.keysym.sym << " state:" << (e.key.state == SDL_PRESSED)
      ? "PRESSED"
      : "RELEASED";
    return strm.str();
  }
  string SdlTextEditingEvtToString(SDL_Event& e) {
    stringstream strm{ SdlCommonEvtToStream(e) };
    strm << " windowID#" << e.edit.windowID << " text:`" << e.edit.text << " start:" << e.edit.start
         << " length:" << e.edit.length;
    return strm.str();
  }
  string SdlTextInputEvtToString(SDL_Event& e) {
    return (SdlCommonEvtToStream(e)
            << " windowID#" << e.text.windowID << " text:'" << e.text.text << "'")
      .str();
  }
  string SdlMouseMotionEvtToString(SDL_Event& e) {
    return (SdlCommonEvtToStream(e)
            << " windowID#" << e.motion.windowID << " mouseID#" << e.motion.which
            << " state:" << e.motion.state << " abs:" << e.motion.x << "," << e.motion.y
            << " rel:" << e.motion.xrel << "," << e.motion.yrel)
      .str();
  }
  string SdlMouseButtonEvtToString(SDL_Event& e) {
    return (SdlCommonEvtToStream(e)
            << " windowID#" << e.button.windowID << " mouseID#" << e.button.which << " buttonID#"
            << e.button.button
            << " state:" << ((e.button.state == SDL_PRESSED) ? "PRESSED" : "RELEASED") << " clicks#"
            << e.button.clicks << " position:" << e.button.x << "," << e.button.y)
      .str();
  }
  string SdlMouseWheelEvtToString(SDL_Event& e) {
    return (SdlCommonEvtToStream(e)
            << " windowID#" << e.wheel.windowID << " mouseID#" << e.wheel.which
            << " direction:" << e.wheel.direction << " pos:" << e.wheel.x << "," << e.wheel.y
            << " precision pos:" << e.wheel.preciseX << "," << e.wheel.preciseY)
      .str();
  }
  string SdlJoyAxisMotionEvtToString(SDL_Event& e) {
    return (SdlCommonEvtToStream(e) << " joystickID#" << e.jaxis.which << " axis#" << e.jaxis.axis
                                    << " value:" << e.jaxis.value)
      .str();
  }
  string SdlJoyBallEvtToString(SDL_Event& e) {
    return (SdlCommonEvtToStream(e) << " joystickID#" << e.jball.which << " ball#" << e.jball.ball
                                    << " rel:" << e.jball.xrel << "," << e.jball.yrel)
      .str();
  }
  string SdlJoyHatEvtToString(SDL_Event& e) {
    return (SdlCommonEvtToStream(e)
            << " joystickID#" << e.jhat.which << " hat#" << e.jhat.hat << " value:" << e.jhat.value)
      .str();
  }
  string SdlJoyButtonEvtToString(SDL_Event& e) {
    return (SdlCommonEvtToStream(e)
            << " joystickID#" << e.jbutton.which << " button#" << e.jbutton.button
            << " state:" << ((e.jbutton.state == SDL_PRESSED) ? "PRESSED" : "RELEASED"))
      .str();
  }
  string SdlJoyDeviceEvtToString(SDL_Event& e) {
    return (SdlCommonEvtToStream(e) << " joystickID#" << e.jdevice.which).str();
  }

  string SdlJoyBatteryEvtToString(SDL_Event& e) {
    return (SdlCommonEvtToStream(e)
            << " joystickID#" << e.jbattery.which << " level:" << e.jbattery.level)
      .str();
  }

  string SdlCDeviceEvtToString(SDL_Event& e) {
    return (SdlCommonEvtToStream(e) << " controllerID#" << e.cdevice.which).str();
  }

  string SdlCAxisEvtToString(SDL_Event& e) {
    return (SdlCommonEvtToStream(e) << " joystickID#" << e.caxis.which << " axis#" << e.caxis.axis
                                    << " value:" << e.caxis.value)
      .str();
  }

  string SdlCButtonEvtToString(SDL_Event& e) {
    return (SdlCommonEvtToStream(e)
            << " joystickID#" << e.cbutton.which << " button#" << e.cbutton.button
            << " state:" << ((e.cbutton.state == SDL_PRESSED) ? "PRESSED" : "RELEASED"))
      .str();
  }

  string SdlEvtCTouchpad_String(SDL_Event& e) {
    return (SdlCommonEvtToStream(e)
            << " joystickID#" << e.ctouchpad.which << " toucpad#" << e.ctouchpad.touchpad
            << " finger#" << e.ctouchpad.finger << " pressure:" << e.ctouchpad.pressure
            << " pos:" << e.ctouchpad.x << "," << e.ctouchpad.y)
      .str();
  }

  string SdlEvtCSensor_string(SDL_Event& e) {
    return (SdlCommonEvtToStream(e)
            << " joystickID#" << e.csensor.which << " sensor#" << e.csensor.sensor << " data: { "
            << e.csensor.data[0] << ", " << e.csensor.data[1] << ", " << e.csensor.data[2] << " }")
      .str();
  }

  string SdlEvtTFinger_string(SDL_Event& e) {
    return (SdlCommonEvtToStream(e)
            << " windowID#" << e.tfinger.windowID << " touchId#" << e.tfinger.touchId
            << " fingerId#" << e.tfinger.fingerId << " pressure:" << e.tfinger.pressure << " pos:"
            << e.tfinger.x << "," << e.tfinger.y << " dis:" << e.tfinger.dx << "," << e.tfinger.dy)
      .str();
  }
  string SdlEvtDGesture_string(SDL_Event& e) {
    return (SdlCommonEvtToStream(e)
            << " touchId#" << e.dgesture.touchId << " gestureId#" << e.dgesture.gestureId
            << " numFingers:" << e.dgesture.numFingers << " pos:" << e.dgesture.x << ","
            << e.dgesture.y)
      .str();
  }
  string SdlEvtMGesture_string(SDL_Event& e) {
    return (SdlCommonEvtToStream(e)
            << " touchId#" << e.mgesture.touchId << " dTheta:" << e.mgesture.dTheta
            << " dDist:" << e.mgesture.dDist << " numFingers:" << e.mgesture.numFingers
            << " pos:" << e.mgesture.x << "," << e.mgesture.y)
      .str();
  }
  string SdlEvtTodo_string(SDL_Event& e) {
    return (SdlCommonEvtToStream(e)
            << " TODO: Implement to string for this type of event:" << e.type)
      .str();
  }
  /***
   * \todo SDL_free must be called. Add to `SdlSys` somehow?
   * \see https://wiki.libsdl.org/SDL2/SDL_DropEvent
   */
  string SdlEvtDrop_string(SDL_Event& e) {
    return (SdlCommonEvtToStream(e)
            << " windowID#" << e.drop.windowID << " file:'" << e.drop.file << "'")
      .str();
  }

  string SdlEvtADevice_string(SDL_Event& e) {
    return (SdlCommonEvtToStream(e)
            << " deviceID#" << e.adevice.which << " iscapture:" << e.adevice.iscapture)
      .str();
  }
  string SdlEvtSensor_string(SDL_Event& e) {
    return (SdlCommonEvtToStream(e)                                    //
            << " sensorID#"                                            //
            << e.sensor.which << " data:{ " << e.sensor.data[0] << "," //
            << e.sensor.data[1] << ","                                 //
            << e.sensor.data[2] << ","                                 //
            << e.sensor.data[3] << ","                                 //
            << e.sensor.data[4] << ","                                 //
            << e.sensor.data[5] << "}")
      .str();
  }

  map<SDL_EventType, function<string(SDL_Event& e)>> mapSdlEvtIdToString{
    {                    SDL_QUIT,        &SdlCommonEvtToString},
    {         SDL_APP_TERMINATING,        &SdlCommonEvtToString},
    {           SDL_APP_LOWMEMORY,        &SdlCommonEvtToString},
    { SDL_APP_WILLENTERBACKGROUND,        &SdlCommonEvtToString},
    {  SDL_APP_DIDENTERBACKGROUND,        &SdlCommonEvtToString},
    { SDL_APP_WILLENTERFOREGROUND,        &SdlCommonEvtToString},
    {  SDL_APP_DIDENTERFOREGROUND,        &SdlCommonEvtToString},
    {           SDL_LOCALECHANGED,        &SdlCommonEvtToString},
    {            SDL_DISPLAYEVENT,       &SdlEvtDisplayToString},
    {             SDL_WINDOWEVENT,           &SdlWinEvtToString},
    {              SDL_SYSWMEVENT,        &SdlCommonEvtToString},
    {                 SDL_KEYDOWN,           &SdlKeyEvtToString},
    {                   SDL_KEYUP,           &SdlKeyEvtToString},
    {             SDL_TEXTEDITING,   &SdlTextEditingEvtToString},
    {               SDL_TEXTINPUT,     &SdlTextInputEvtToString},
    {           SDL_KEYMAPCHANGED,        &SdlCommonEvtToString},
    {             SDL_MOUSEMOTION,   &SdlMouseMotionEvtToString},
    {         SDL_MOUSEBUTTONDOWN,   &SdlMouseButtonEvtToString},
    {           SDL_MOUSEBUTTONUP,   &SdlMouseButtonEvtToString},
    {              SDL_MOUSEWHEEL,    &SdlMouseWheelEvtToString},
    {           SDL_JOYAXISMOTION, &SdlJoyAxisMotionEvtToString},
    {           SDL_JOYBALLMOTION,       &SdlJoyBallEvtToString},
    {            SDL_JOYHATMOTION,        &SdlJoyHatEvtToString},
    {           SDL_JOYBUTTONDOWN,     &SdlJoyButtonEvtToString},
    {             SDL_JOYBUTTONUP,     &SdlJoyButtonEvtToString},
    {       SDL_JOYBATTERYUPDATED,    &SdlJoyBatteryEvtToString},
    {          SDL_JOYDEVICEADDED,     &SdlJoyDeviceEvtToString},
    {        SDL_JOYDEVICEREMOVED,     &SdlJoyDeviceEvtToString},
    {    SDL_CONTROLLERAXISMOTION,         &SdlCAxisEvtToString},
    {    SDL_CONTROLLERBUTTONDOWN,       &SdlCButtonEvtToString},
    {      SDL_CONTROLLERBUTTONUP,       &SdlCButtonEvtToString},
    {   SDL_CONTROLLERDEVICEADDED,       &SdlCDeviceEvtToString},
    {SDL_CONTROLLERDEVICEREMAPPED,       &SdlCDeviceEvtToString},
    { SDL_CONTROLLERDEVICEREMOVED,       &SdlCDeviceEvtToString},
    {  SDL_CONTROLLERTOUCHPADDOWN,      &SdlEvtCTouchpad_String},
    {    SDL_CONTROLLERTOUCHPADUP,      &SdlEvtCTouchpad_String},
    {SDL_CONTROLLERTOUCHPADMOTION,      &SdlEvtCTouchpad_String},
    {  SDL_CONTROLLERSENSORUPDATE,        &SdlEvtCSensor_string},
    {              SDL_FINGERDOWN,        &SdlEvtTFinger_string},
    {                SDL_FINGERUP,        &SdlEvtTFinger_string},
    {            SDL_FINGERMOTION,        &SdlEvtTFinger_string},
    {           SDL_DOLLARGESTURE,       &SdlEvtDGesture_string},
    {            SDL_DOLLARRECORD,       &SdlEvtDGesture_string},
    {            SDL_MULTIGESTURE,       &SdlEvtMGesture_string},
    {         SDL_CLIPBOARDUPDATE,           &SdlEvtTodo_string},
    {                SDL_DROPFILE,           &SdlEvtDrop_string},
    {                SDL_DROPTEXT,           &SdlEvtDrop_string},
    {               SDL_DROPBEGIN,           &SdlEvtDrop_string},
    {            SDL_DROPCOMPLETE,           &SdlEvtDrop_string},
    {        SDL_AUDIODEVICEADDED,        &SdlEvtADevice_string},
    {      SDL_AUDIODEVICEREMOVED,        &SdlEvtADevice_string},
    {            SDL_SENSORUPDATE,         &SdlEvtSensor_string},
    {    SDL_RENDER_TARGETS_RESET,        &SdlCommonEvtToString},
    {     SDL_RENDER_DEVICE_RESET,        &SdlCommonEvtToString}
  };

  function<void(SDL_Event&)> SdlEvt::PrintTo(std::ostream& stream) {
    return [&stream](SDL_Event& e) { stream << GetString(e) << endl; };
  }

  string SdlEvt::GetString(SDL_Event& e) {
    SDL_EventType eType = (SDL_EventType)e.type;
    if (mapSdlEvtIdToString.contains(eType)) {
      return mapSdlEvtIdToString[eType](e);
    } else {
      return "UNKNOWN EVENT TYPE...";
    }
  }

  void SdlEvt::PrintString(SDL_Event& e) {}

}