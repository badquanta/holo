# Holo

Holo holo, holo holo holo... holo.

## Build setup

I wanted to make use of Boost::json.  Boost::json wouldn't work unless I pulled in _A LOT_ of Boost in general.
So I decided just to pull in all of Boost via their git repository.
Maybe this was a bad idea; since checking out all the sub-repositories takes _a long_ time.

But hopefully this is just something you need to do once:

    git submodule update --init --recursive
    mkdir build
    cd build
    cmake ../

## Compiling

Just enter into your build directory and run `cmake --build`

    ninja


