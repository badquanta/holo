#include "Window.hh"
#include "holo-cfg.hh"

using namespace holo;

int main(int ac, char** av) {
  try {
    Program::Configure(ac, av);
    Window::sPtr win{ Window::Create(300, 200) };

    GlProgram::sPtr glProgram{GlProgram::Create()};
    GlShader::sPtr glVertexShader{ GlShader::Create(
      GL_VERTEX_SHADER,
      "#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, "
      "LVertexPos2D.y, 0, 1 ); }"
    ) };
    if (!glVertexShader->Compile()) {
      throw std::runtime_error(glVertexShader->GetLog());
    }
    GlShader::sPtr glFragmentShader{ GlShader::Create(
      GL_FRAGMENT_SHADER,
      "#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }"
    )};
    if (!glFragmentShader->Compile()){
      throw std::runtime_error(glFragmentShader->GetLog());
    }
    glProgram->Attach(glVertexShader);
    glProgram->Attach(glFragmentShader);
    if(!glProgram->Link()){
      throw std::runtime_error(glProgram->GetLog());
    }
    glClearColor(0.f,0.f,0.f,1.f);
    GLint gVertexPos2DLocation = glProgram->GetAttribLocation("LVertexPos2D");

    auto         VBO{ GlBuffer<GL_ARRAY_BUFFER, GLfloat, GL_STATIC_DRAW>::Create() };
    GLfloat      vertexData[] = {
      -0.5f, -0.5f, //
      0.5f,  -0.5f, //
      0.5f,  0.5f,  //
      -0.5f, 0.5f   //
    };
    VBO->Data(2 * 4, vertexData);
    auto IBO{ GlBuffer<GL_ELEMENT_ARRAY_BUFFER, GLuint, GL_STATIC_DRAW>::Create() };
    GLuint indexData[] = { 0, 1, 2, 3 };
    IBO->Data(4, indexData);

    win->SetTitle("Hello World.");
    win->SetPosition({ 100, 200 });
    std::cout << "Title: " << win->GetTitle() << std::endl;
    // Renderer&            renderer = program->GetRenderer();
    // Font                  font(CMAKE_BINARY_DIR "/share/Hack-Regular.ttf", 30);

    SdlEvt::Handler requestQuit{ [win](const SDL_Event& evt) { win->program->RequestQuit(); } };
    win->events->Quit->On(requestQuit);
    win->events->Key->Key(SDLK_ESCAPE)->On(requestQuit);

    win->render->VOID->On([gVertexPos2DLocation, glProgram, VBO, IBO]() {
      glClear(GL_COLOR_BUFFER_BIT);
      glProgram->Use();

      glEnableVertexAttribArray(gVertexPos2DLocation);
      VBO->Bind();
      glVertexAttribPointer(gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), NULL);

      IBO->Bind();
      glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);

      glDisableVertexAttribArray(gVertexPos2DLocation);

      glProgram->StopUse();

    });
    win->program->MainLoop();
    return 0;
  } catch (Program::CliHelp& e) {
    std::cout << e << std::endl;
    return 0;
  } catch (std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
}