#pragma once
#include <holo/sdl/Sys.hh>
namespace holo {


  class SdlGlSys {
    public:
      shared_ptr<SdlSys> const    sdlSys{ SdlSys::Get() };
      static shared_ptr<SdlGlSys> Get();

    protected:
      SdlGlSys();
      static weak_ptr<SdlGlSys> instance;

    public:
      ~SdlGlSys();
  };
}