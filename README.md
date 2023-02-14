# Holo

## Immediate Goals

* loading OpenGL textures from SDL Surfaces.
* separate external code into provider modules.

## External dependencies

The source code depends on [libSDL2pp](https://github.com/libSDL2pp/libSDL2pp) & [boost](https://github.com/boostorg/boost).

### References:

Various external references used in building.

* [SDL2pp API](https://sdl2pp.amdmi3.ru/)
* [Sdl2 API](https://wiki.libsdl.org/SDL2/CategoryAPI)
* boost/
  * [log/trivial](https://www.boost.org/doc/libs/1_75_0/libs/log/doc/html/log/tutorial.html)
* [c++ & standard library](https://en.cppreference.com/w/cpp)


## Build setup

Ensure all submodules are initialized with something like:

    git clone --recursive https://github.com/BadQuanta/holo.git

or

    cd holo
    git submodule update --init --recursive
    mkdir build
    cd build
    cmake ../

## Compiling

Just enter into your build directory and run `cmake --build`

    ninja

or `make` or whatever build system cmake defaults to creating for your platform.
