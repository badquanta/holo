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
#include <holo/sdl/EvtRoot.hh>
namespace holo {
  SdlEvtRoot::SdlEvtRoot()
    : SdlEvtTypeSwitch() {
    SpecialHandlers = SpecialHandlers_t{
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
      {          SDL_JOYDEVICEADDED,           Joy},
      {        SDL_JOYDEVICEREMOVED,           Joy},
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

}