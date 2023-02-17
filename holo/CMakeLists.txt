configure_file(holo-cfg.hh.in holo-cfg.hh)
configure_file(.input.holo.hh holo.hh)
file(GLOB_RECURSE HOLO_GLSL_FS_SOURCES RELATIVE "${CURRENT_SOURCE_DIR}" "gl/sl/*.fs")
file(GLOB_RECURSE HOLO_GLSL_VS_SOURCES RELATIVE "${CURRENT_SOURCE_DIR}" "gl/sl/*.vs")
foreach(GLSL_SOURCE IN LISTS HOLO_GLSL_FS_SOURCES HOLO_GLSL_VS_SOURCES)
  message("GLSL Source: ${GLSL_SOURCE}")
endforeach()

set(HOLO_SDL_SOURCES
  "sdl/Sys.cc"
  "sdl/GlSys.cc"
  "sdl/Evt.cc"
  "sdl/EvtTypeSwitch.cc"
  "sdl/EvtKeyCode.cc"
  "sdl/EvtKeyPress.cc"
  "sdl/EvtMouse.cc"
  "sdl/EvtWin.cc"
  "sdl/EvtRoot.cc"
  "sdl/Pane.cc"
  "sdl/PaneGl.cc"
  "sdl/PaneRender.cc"
)

set(HOLO_GL_SOURCES
  "gl/Errors.cc"
  "gl/SlProgram.cc"
  "gl/SlShader.cc"
  "gl/Texture.cc"
  "gl/VertexArray.cc"
  "gl/Camera.cc"
)

set(HOLO_SOURCES
  "Evt.cc"
  "Arch.cc"
  "Emitter.cc"
)

add_library(holo ${HOLO_SOURCES} ${HOLO_SDL_SOURCES} ${HOLO_GL_SOURCES})
target_include_directories(holo PUBLIC "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}")

target_link_libraries(holo glm SDL2pp::SDL2pp Boost::log Boost::program_options Boost::filesystem GLEW OpenGL)

add_executable(holo-deck holo-deck.cc)

target_link_libraries(holo-deck holo )
