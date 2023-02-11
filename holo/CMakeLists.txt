configure_file(holo-cfg.hh.in holo-cfg.hh)
configure_file(.input.holo.hh holo.hh)
add_library(holo holo.cc Arch.cc sdl/RootEvt.cc Pane.cc GlVertexArray.cc GlTexture.cc GlShader.cc GlProgram.cc)
target_include_directories(holo PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_BINARY_DIR}";"${PROJECT_SOURCE_DIR}")

target_link_libraries(holo SDL2pp::SDL2pp Boost::json Boost::log Boost::program_options Boost::filesystem GLEW OpenGL)

add_executable(holo-deck holo-deck.cc)

target_link_libraries(holo-deck holo )