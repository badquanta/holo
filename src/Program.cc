#include "Program.hh"
#include "Window.hh"
#include <boost/format.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>

#include <stdlib.h>

namespace holo {
  Program::sPtr Program::instance;
  bool          Program::quit = false;
  bool          Program::Configure(int ac, char* av[]) {
    namespace logging = boost::log;
    namespace po      = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()                 //
      ("help", "produce help message") //
      ("log", po::value<int>()->default_value(2), "set log level");
    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);
    if (vm.count("help")) {
      quit = true;
      throw desc;
    }
    int logLvl = vm["log"].as<int>();
    switch (logLvl) {
      case 5:
        logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::trace);
        break;
      case 4:
        logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::debug);
        break;
      case 3:
        logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::info);
        break;
      case 2:
        logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::warning);
        break;
      case 1:
        logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::error);
        break;
      case 0:
        logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::fatal);
        break;
      default:
        char buffer[50];
        snprintf(buffer, 50, "Invalid log level: %d", logLvl);
        throw std::runtime_error(std::string(buffer));
    }
    return true;
  }
  Program::sPtr Program::Init() {
    if (!instance) {
      instance = std::shared_ptr<Program>(new Program());
    }
    return instance;
  }

  Program::Program() {
    BOOST_LOG_TRIVIAL(trace) << "Startup";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // mainRenderer = std::make_shared<SDL2pp::Renderer>(*mainWindow, -1, SDL_RENDERER_ACCELERATED);
  }

  Program::~Program() {
    BOOST_LOG_TRIVIAL(trace) << "Shutdown";
  }

  void Program::MainLoop() {
    while (!quit) {
      SDL_Event evt;
      prePoll->Trigger();
      while (SDL_PollEvent(&evt)) {
        events->Trigger(evt);
        Window::Dispatch(evt);
      }
      preRender->Trigger();
      Window::RenderAll();
    }
  }
  void Program::RequestQuit() {
    quit = true;
  }

}