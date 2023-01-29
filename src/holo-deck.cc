#include "holo.hh"

using namespace SDL2pp;

int
main()
{
  try {
    holo::Deck           hd;
    Window&              window = hd.GetWindow();
    Renderer&             renderer = hd.GetRenderer();
    Font                 font(CMAKE_BINARY_DIR "/share/Hack-Regular.ttf", 30);
    std::vector<Texture> textures;
    textures.emplace_back(
      renderer,
      font.RenderText_Solid(
        "Hello, world! (solid)",
        SDL_Color{ 255, 255, 255, 255 }
      )
    );
    textures.emplace_back(
      renderer,
      font.RenderText_Shaded(
        "Hello, world! (shaded)",
        SDL_Color{ 255, 255, 255, 255 },
        SDL_Color{ 0, 0, 255, 255 }
      )
    );
    textures.emplace_back(
      renderer,
      font.RenderText_Blended(
        "Hello, world! (blended)",
        SDL_Color{ 255, 255, 255, 255 }
      )
    );
    while (1) {
      SDL_Event event;
      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN &&
                                       (event.key.keysym.sym == SDLK_ESCAPE ||
                                        event.key.keysym.sym == SDLK_q))) {
          return 0;
        }
        renderer.SetDrawColor(0, 63, 63);
        renderer.Clear();

        int h = 0;
        for (auto& texture : textures) {
          renderer.Copy(
            texture,
            NullOpt,
            Rect(0, h, texture.GetWidth(), texture.GetHeight())
          );
          h += texture.GetHeight();
        }
        renderer.Present();
        SDL_Delay(1);
      }
    }
    return 0;
  } catch (std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
}