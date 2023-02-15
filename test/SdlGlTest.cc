#include <holo/Gl.hh>
#include <holo/gl/math.hh>
#include <holo/sdl/PaneGl.hh>
int main(int ac, char** av) {
  try {
    using namespace holo;
    Arch::Configure(ac, av);
    shared_ptr<SdlPaneGl> pane{ SdlPaneGl::Create("Sdl & OpenGL tests..") };
    // Hitting escape in any window means the test failed.
    pane->sdl->events->Key->Code(SDLK_ESCAPE)->Up->VOID->On([]() {
      throw std::runtime_error("Escape key pressed.");
    });
    // Closing all windows or otherwise quitting normally means tests passed.
    pane->sdl->events->Quit->VOID->On(&Arch::RequestQuit);
    // Pressing the enter key cancels
    pane->sdl->events->Key->Code(SDLK_RETURN)->Up->VOID->On(&Arch::RequestQuit);
    auto QUIT_TIMEOUT_ID = pane->arch->Timeout(5000, &Arch::RequestQuit);
    pane->events->Key->Code(SDLK_SPACE)->Up->VOID->Once([QUIT_TIMEOUT_ID]() {
      if (Arch::Get()->CancelTimeout(QUIT_TIMEOUT_ID)) {
        std::cout << "QUIT TIMEOUT CANCELED\n";
      } else {
        std::cout << "QUIT TIMEOUT ALREADY CANCELED\n";
      };
    });
    pane->GlActivateContext();
    auto glProgram{ GlSlProgram::Build("share/shaders/test1.vert", "share/shaders/test1.frag") };
    auto VAO{ GlVertexArray::Create() };
    VAO->Bind();
    vector<float> vertices{
      // positions          // texture coords
      0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // top right
      0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
      -0.5f, 0.5f,  0.0f, 0.0f, 1.0f  // top left
    };

    auto             VBO{ GlBuffer<GL_ARRAY_BUFFER, GLfloat, GL_STATIC_DRAW>::Create(vertices) };
    vector<uint32_t> indices{
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
    };
    auto EBO{ GlBuffer<GL_ELEMENT_ARRAY_BUFFER, uint32_t, GL_STATIC_DRAW>::Create(indices) };

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    auto texture1{ GlTexture::Load("share/textures/PlasmaRGB.512x512.png") };
    auto texture2{ GlTexture::Load("textures/Untitled.png") };

    glProgram->Use();
    glProgram->Set("texture1", 0);
    glProgram->Set("texture2", 1);

    pane->render->On([&]() {
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
      glActiveTexture(GL_TEXTURE0);
      texture1->Bind();
      glActiveTexture(GL_TEXTURE1);
      texture2->Bind();

      glm::mat4 transform{ 1.0f };
      transform = glm::translate(transform, glm::vec3(0.5f,-0.5f,0.5f));
      transform = glm::rotate(transform, 0.0f ,glm::vec3(0.0f,0.0f,1.0f));
      glProgram->Use();
      auto transformLoc = glProgram->GetUniformLocation("transform");
      glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

      VAO->Bind();
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    });
    pane->arch->MainLoop();
  } catch (holo::Arch::CliHelp& e) {
    std::cerr << "Runtime error: " << e << std::endl;
    return 1;
  } catch (std::exception& e) {
    std::cerr << "EXCEPTION: " << e.what() << std::endl;
    return 2;
  }
  return 0;
}