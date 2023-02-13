configure_file(holo-cfg.hh.in holo-cfg.hh)
configure_file(.input.holo.hh holo.hh)

set(HOLO_SDL_SOURCES
  "sdl/Sys.cc"
  "sdl/GlSys.cc"
  "sdl/Evt.cc"
  "sdl/EvtKeyCode.cc"
  "sdl/EvtKeyPress.cc"
  "sdl/EvtWin.cc"
  "sdl/EvtRoot.cc"
  "sdl/Pane.cc"
  "sdl/PaneGl.cc"
  "sdl/PaneRender.cc"
)

set(HOLO_GL_SOURCES
  "gl/SlProgram.cc"
  "gl/SlShader.cc"
  "gl/Texture.cc"
  "gl/VertexArray.cc"
)

set(HOLO_SOURCES
  "Arch.cc"
  "Pane.cc"
)

add_library(holo ${HOLO_SOURCES} ${HOLO_SDL_SOURCES} ${HOLO_GL_SOURCES})
target_include_directories(holo PUBLIC "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}")

target_link_libraries(holo glm SDL2pp::SDL2pp Boost::log Boost::program_options Boost::filesystem GLEW OpenGL)

add_executable(holo-deck holo-deck.cc)

target_link_libraries(holo-deck holo )
