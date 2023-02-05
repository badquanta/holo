configure_file(holo-cfg.hh.in holo-cfg.hh)
add_library(holo holo.cc SdlEvt.cc SdlRootEvt.cc GlProgram.cc Program.cc Window.cc)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(holo SDL2pp::SDL2pp Boost::json Boost::log Boost::program_options Boost::filesystem GLEW OpenGL)

add_executable(holo-deck holo-deck.cc)

target_link_libraries(holo-deck holo )