# Holo v0.1.0

C++23 framework & examples project. Sdl & OpenGL support. Planned integration of Gtk3 or 4.

## Goals

### v0.1.1

* demo 3d game
* demo 2d game
* demo editor application (suite?)
  * integrate gtk inter-operations.
* implement more automated testing for
inadvertent behavior modifications of various use cases.

### v0.2.0

* better/fine grained unit testing
* fully packaging for installation with CPack.
* support running Gl with Gtk without SDL & Vice-versa.
* support running Gtk without Gl or SDL.
* support running a mix of all three.

## this repository

[HOLO_GITHUB]:(https://github.com/BadQuanta/holo)

  Available on [github][HOLO_GITHUB].

* `docs` is where doxygen is configured via cmake.
* `holo` C++ source code.
  * `Arch`
  * `Emitter`
* `share`
* `test`
* `CMakeLists.txt`

## API Overview

### namespace holo

#### &lt;holo/Arch.hpp&gt;

  `holo::Arch` Used to configure framework options and manages abstract "main loop" all systems use to orchestrate with others.

#### &lt;holo/Evt.hpp&gt;

  Provides callback function collection and dispatching.

* `holo::EvtAbstract<Types...>` can represent the collection and dispatching of callbacks with any `Types...` of signature lists.
* `holo::EvtVoid` provides an concrete type of a function<void(void)> `Evt...`.
* `holo::EvtAbstractType` for `holo::EvtAbstract<Types...>` with one or more `Types...` this
specialization provides a `holo::EvtVoid` proxy named `VOID` which will always be triggered when this is triggered.
* `holo::EvtAbstractTypeSwitch` provides a mechanism for relaying to various sub-events, see `holo::SdlEvtRoot` for a good example usage.

#### &lt;holo/Emitter.hh&gt;

`holo::Emitter` provides a base class with which to link into Arch's main loop. See `holo::SdlWindow` for an example implementation.

__TODO__ need to finish documenting major components of the architecture, but beyond here it
is in flux being prototyped.

### holo::Sdl*

#### &lt;holo/sdl/Evt.hh&gt;

`holo::SdlEvt`

## various useful external links


The source code depends on [libSDL2pp][libSDL2pp] & [boost][boost] along with

Various external references used in building.

[boost]:(https://github.com/boostorg/boost)
[boost_log_trivial]:(https://www.boost.org/doc/libs/1_75_0/libs/log/doc/html/log/tutorial.html)
[glm]:(https://github.com/g-truc/glm)
[libSDL2pp]:(https://github.com/libSDL2pp/libSDL2pp)
[libSDL2pp_API]:(https://sdl2pp.amdmi3.ru/)
[libSDL2_API]:(https://wiki.libsdl.org/SDL2/CategoryAPI)

* [glm][glm]
* SDL2
  * SDL2pp
    * [github repository][libSDL2pp]
    * [API][libSDL2pp_API]
  * [libSDL 2.0 API][libSDL2_API]
* OpenGL
  * [opengl api](https://registry.khronos.org/OpenGL-Refpages/gl4/html/index.php)
* [boost/][boost]

  * [log/trivial][boost_log_trivial]
* c++ & std libs
  * [cppreference.com](https://en.cppreference.com/w/cpp)
  * [cplusplus.com](https://cplusplus.com/)
  * [std::chrono](https://cplusplus.com/reference/chrono/)
* glsl
  * __TODO__ link to some glsl guidance.

* [cmake](https://cmake.org/cmake/help/v3.24/manual/cmake-commands.7.html)

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
