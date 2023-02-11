# Holo

## Immediate Goals

* loading OpenGL textures from SDL Surfaces.
* separate external code into provider modules.

## External dependencies

The source code depends on [libSDL2pp](https://github.com/libSDL2pp/libSDL2pp) & [boost](https://github.com/boostorg/boost).



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
