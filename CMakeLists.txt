cmake_minimum_required(VERSION 3.8)
project(holo
  VERSION 0.1.0
  DESCRIPTION "SDL2/OpenGL Game Engine"
  HOMEPAGE_URL "https://github.com/BadQuanta/holo"
)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(GLU REQUIRED)
find_package(GLEW REQUIRED)
# GLM
add_subdirectory("ext/glm")

# Dependency SDL2pp
set(SDL2PP_WITH_IMAGE ON)
set(SDL2PP_WITH_MIXER ON)
set(SDL2PP_WITH_TTF ON)
add_subdirectory("ext/libSDL2pp")
# Boost
set(BOOST_INCLUDE_LIBRARIES test json log filesystem program_options)
add_subdirectory("ext/boost")

# Project assets
add_subdirectory("share")
# Main library & main demo.
add_subdirectory("holo")
# CTest

add_subdirectory("test")
# Documentation source & doxygen generator.
add_subdirectory("docs")
