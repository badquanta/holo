#define BOOST_TEST_MODULE EvtSdlTests
#include <boost/test/included/unit_test.hpp>
#include <holo/sdl/Evt.hh>
#include <holo/sdl/EvtRoot.hh>
#include <holo/sdl/EvtMouse.hh>
using namespace holo;
BOOST_AUTO_TEST_CASE(free_test_function) {
  BOOST_TEST(true);
}
BOOST_AUTO_TEST_CASE(SdlEvtTest) {
  SdlEvt    basic;
  SDL_Event e{ 0 };
  basic.On([](SDL_Event&) { std::cout << "Called every time." << std::endl; });
  basic.Once([](SDL_Event&) { std::cout << "Called only once." << std::endl; });
  basic.Trigger(e);
  e.type = SDL_MOUSEBUTTONDOWN;
  basic.Trigger(e);
  e.type = SDL_MOUSEBUTTONUP;
  basic.Trigger(e);
}
BOOST_AUTO_TEST_CASE(SdlEvtTypeSwitchTest) {
  SdlEvtTypeSwitch etSwitch;
  SDL_Event        e{ 0 };
  etSwitch.On([](SDL_Event&) { std::cout << "Called every time." << std::endl; });
  etSwitch.Once([](SDL_Event&) { std::cout << "Called only once." << std::endl; });
  etSwitch.Trigger(e);
  e.type = SDL_MOUSEBUTTONDOWN;
  etSwitch.Trigger(e);
  e.type = SDL_MOUSEBUTTONUP;
  etSwitch.Trigger(e);
}
BOOST_AUTO_TEST_CASE(SdlKeyCodeEvtTest) {
  SdlKeyCodeEvt key;
  key.On([](SDL_Event&) { std::cout << "Called every time." << std::endl; });
  key.Once([](SDL_Event&) { std::cout << "Called only once." << std::endl; });
  SDL_Event e{ type : 0 };
  key.Trigger(e);
  e.type = SDL_KEYDOWN;
  key.Trigger(e);
  e.type = SDL_KEYUP;
  key.Trigger(e);
}

BOOST_AUTO_TEST_CASE(SdlMouseEvtTest) {
  SdlEvtMouseList ml;
  ml.On([](SDL_Event&) { std::cout << "Called every time." << std::endl; });
  ml.Once([](SDL_Event&) { std::cout << "Called only once." << std::endl; });
  SDL_Event e{ type : 0 };
  ml.Trigger(e);
  e.type = SDL_KEYDOWN;
  ml.Trigger(e);
  e.type = SDL_KEYUP;
  ml.Trigger(e);
}



BOOST_AUTO_TEST_CASE(SdlEvtWinTest) {
  SdlEvtWin win;
  win.On([](SDL_Event&) { std::cout << "Called every time." << std::endl; });
  win.Once([](SDL_Event&) { std::cout << "Called only once." << std::endl; });
  SDL_Event e{ type : 0 };
  win.Trigger(e);
  e.type = SDL_KEYDOWN;
  win.Trigger(e);
  e.type = SDL_KEYUP;
  win.Trigger(e);
}

BOOST_AUTO_TEST_CASE(SdlEvtRootTest) {
  SdlEvtRoot root;
  SDL_Event  e{ 0 };
  root.On([](SDL_Event&) { std::cout << "Called every time." << std::endl; });
  root.Once([](SDL_Event&) { std::cout << "Called only once." << std::endl; });
  root.Trigger(e);
  e.type = SDL_MOUSEBUTTONDOWN;
  root.Trigger(e);
  e.type = SDL_MOUSEBUTTONUP;
  root.Trigger(e);
}