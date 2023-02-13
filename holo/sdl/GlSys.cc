#include <holo/sdl/GlSys.hh>

namespace holo {

  weak_ptr<SdlGlSys> SdlGlSys::instance;
  SdlGlSys::SdlGlSys() {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }

  SdlGlSys::~SdlGlSys() {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }

  shared_ptr<SdlGlSys> SdlGlSys::Get() {
    shared_ptr<SdlGlSys> loaded;
    if (instance.expired()) {
      loaded   = shared_ptr<SdlGlSys>(new SdlGlSys());
      instance = loaded;
      return loaded;
    } else {
      loaded = instance.lock();
    }

    return loaded;
  }
}