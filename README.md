# NOT YET RELEASED Holo v0.1.0

[learnOpenGl]:https://learnopengl.com/

* _DO NOT RECURSIVE CLONE_
  * __WARNING__ : This repository currently includes many external repositories linked, including the root [boostorg library][boost] which is H.U.G.E. (~2GB) ; I am considering removing this, obviously. But for now it's fine for me.

* __DO NOT USE__ this repository, not fit for use.

`libHolo` will be a C++23 framework with example games and applications.


## Credits

### OpenGL related

Many thanks, and credit, go to [learnopengl.com](https://learnopengl.com/), much early framework design and code comes from these tutorials, including verbatim shaders.

#### Font files

* Hack-Regular by [Source-Foundery](https://github.com/source-foundry/Hack)

#### Textures files & sources

* [learnopengl.com lighting maps](https://learnopengl.com/Lighting/Lighting-maps)
  * container2.png
  * container2_specular.png
* [JWC on OpenGameArt](https://opengameart.org/content/wood-texture-tiles)
  * `wood1.jpg`
  * `wood2.jpg`

#### Models

* [crate-5 by Kutejnikof on opengameart.org](https://opengameart.org/content/crate-5)

## Sub Projects

This repository is prototyping what is essentially seven individual projects at once.
These will likely be separated in the future:

* `holo-deck`: Demo 3D Game, intended to rely on SDL & OpenGL only.
* `holo-ed`: Demo files game editor, intended to rely on SDL, OpenGL, & Gtk.
* `Holo`, possibly `HoloCore` in the future: Core, external library agnostic framework.  Intended to carry zero dependencies on Gtk, Sdl, or OpenGL directly but provides a framework for those external components work cooperatively.
* `HoloSdl`: Core SDL integration. No dependencies on OpenGL.
* `HoloGl`: Core OpenGL integration. No dependencies on SDL.
* `HoloSdlGl`: SDL & OpenGL integration.
* `HoloGtk`: GTK integration.

## Goals

### v0.1.1

* sdl & opengl
* demo 3d game
* demo 2d game
* demo editor application (suite?)
  * integrate gtk inter-operations.
* implement more automated testing for
inadvertent behavior modifications of various use cases.

### v0.2.0

* sdl, opengl, & gtk
* better/fine grained unit testing
* fully packaging for installation with CPack.
* support running Gl with Gtk without SDL & Vice-versa.
* support running Gtk without Gl or SDL.
* support running a mix of all three.

### v0.3.0

* other windowing toolkits?
* other multimedia, device i/o, frameworks?

## this repository

[HOLO_GITHUB]:https://github.com/BadQuanta/holo

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

#### &lt;holo/Sdl.hh&gt;

__TODO__ need to finish documenting major components of the architecture, but beyond here it
is in flux being prototyped.

### holo::Sdl*

#### &lt;holo/sdl/Evt.hh&gt;

`holo::SdlEvt`

## various useful external links

The source code depends on [libSDL2pp][libSDL2pp] & [boost][boost] along with

Various external references used in building.

[boost]:https://github.com/boostorg/boost
[boost_log_trivial]:https://www.boost.org/doc/libs/1_75_0/libs/log/doc/html/log/tutorial.html
[glm]:https://github.com/g-truc/glm
[libSDL2pp]:https://github.com/libSDL2pp/libSDL2pp
[libSDL2pp_API]:https://sdl2pp.amdmi3.ru/
[libSDL2_API]:https://wiki.libsdl.org/SDL2/CategoryAPI

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
