configure_file(holo-cfg.hh.in holo-cfg.hh)
configure_file(.input.holo.hh holo.hh)
file(GLOB_RECURSE HOLO_GLSL_FS_SOURCES RELATIVE "${PROJECT_SOURCE_DIR}/holo/gl/sl" "*.fs")
file(GLOB_RECURSE HOLO_GLSL_VS_SOURCES RELATIVE "${PROJECT_SOURCE_DIR}/holo/gl/sl" "*.vs")
foreach(GLSL_SOURCE IN LISTS HOLO_GLSL_FS_SOURCES HOLO_GLSL_VS_SOURCES)
  message("HOLO GLSL ${GLSL_SOURCE}")
  configure_file("gl/sl/${GLSL_SOURCE}" "gl/sl/${GLSL_SOURCE}")
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
  "sdl/Window.cc"
  "sdl/GlContext.cc"
  "sdl/GlTexture.cc"
  "sdl/Render.cc"
)

set(HOLO_GL_SOURCES
  "gl/Errors.cc"
  "gl/SlProgram.cc"
  "gl/SlShader.cc"
  "gl/Texture.cc"
  "gl/VertexArray.cc"
  "gl/Camera.cc"
  "gl/Model.cc"
  "gl/Mesh.cc"
)

set(HOLO_SOURCES
  "Evt.cc"
  "Arch.cc"
  "Emitter.cc"
  "ShareFiles.cc"
)

add_library(holo ${HOLO_SOURCES} ${HOLO_SDL_SOURCES} ${HOLO_GL_SOURCES})
# see: https://blog.feabhas.com/2021/07/cmake-part-2-release-and-debug-builds/
target_compile_options(holo
  PRIVATE -Wall -Wextra -Wpedantic
# -Wconversion -Wsign-conversion
    $<$<CONFIG:DEBUG>:-g3>
    $<$<CONFIG:DEBUG>:-Og>
    $<$<CONFIG:RELEASE>:-O3>
    $<$<CONFIG:RELEASE>:-Werror>
)

target_include_directories(holo PUBLIC "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}")

target_link_libraries(holo glm assimp SDL2pp::SDL2pp Boost::log Boost::program_options Boost::filesystem GLEW OpenGL)

function(HoloDemo arg)
  add_executable(${arg} "${arg}.cc")
  target_link_libraries(${arg} holo)
  message("HOLO DEMO ${arg}")
endfunction()
HoloDemo(holo-deck)
HoloDemo(holo-ed)
HoloDemo(holo-view)
target_include_directories(holo-ed PUBLIC ${GTKMM_INCLUDE_DIRS})
target_link_libraries(holo-ed ${GTKMM_LIBRARIES})

