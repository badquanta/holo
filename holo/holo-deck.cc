/** \file
 * \example holo/holo-deck.cc
 *  \copyright
holo
Copyright (C) 2023  Jon David Sawyer

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/
#include <holo/SdlGl.hh>
using namespace holo;

int main(int ac, char** av) {
  try {
    Arch::Configure(ac, av);
    SdlGlContext::sPtr win{ SdlGlContext::Create("Holo-Deck", 300, 200, SDL_WINDOW_RESIZABLE) };
    win->events->Window->Resized->On([&win](SDL_Event& e) {
      SdlPoint drawableSize{ win->GetDrawableSize() };
      glViewport(0, 0, drawableSize.x, drawableSize.y);
    });
    GlSlProgram::sPtr glProgram{ GlSlProgram::Create() };
    {
      GlSlShader::sPtr glVertexShader{ GlSlShader::Load(GL_VERTEX_SHADER, "shaders/v1.vert") };
      if (!glVertexShader->Compile()) {
        throw std::runtime_error(glVertexShader->GetLog());
      }
      glVertexShader->GetLog();
      GlSlShader::sPtr glFragmentShader{ GlSlShader::Load(GL_FRAGMENT_SHADER, "shaders/v1.frag") };
      if (!glFragmentShader->Compile()) {
        throw std::runtime_error(glFragmentShader->GetLog());
      }
      glFragmentShader->GetLog();
      glProgram->Attach(glVertexShader);
      glProgram->Attach(glFragmentShader);
      if (!glProgram->Link()) {
        throw std::runtime_error(glProgram->GetLog());
      }
      glProgram->Validate();
      glProgram->GetLog();
    }
    auto VAO{ GlVertexArray::Create() };
    VAO->Bind();
    GLint vertPos2D   = glProgram->GetAttribLocation("vPos"),
          vertColor3D = glProgram->GetAttribLocation("vColor"),
          vertTex2D   = glProgram->GetAttribLocation("vTexCoord");
    std::vector<GLfloat> vertexData{
      //  x,     y,    z,    r,    g,    b,     u,     v
      -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //
      0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, //
      0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, //
      -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  //
    };
    auto VBO{ GlBuffer<GL_ARRAY_BUFFER, GLfloat, GL_STATIC_DRAW>::Create(vertexData) };
    { // vertex attribute setup
      VBO->Bind();
      glVertexAttribPointer( //
        vertPos2D, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0
      );
      glEnableVertexAttribArray(vertPos2D);
      glVertexAttribPointer( //
        vertColor3D, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(float))
      );
      glEnableVertexAttribArray(vertColor3D);
      glVertexAttribPointer( //
        vertTex2D, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(float))
      );
      glEnableVertexAttribArray(vertTex2D);
    }
    auto firstTex{ SdlGlTexture::Load("textures/Untitled.png") };

    std::vector<GLuint> indexData{ 0, 1, 2, 3 };
    auto IBO{ GlBuffer<GL_ELEMENT_ARRAY_BUFFER, GLuint, GL_STATIC_DRAW>::Create(indexData) };

    bool wireframe = false;

    win->events->Quit->VOID->On(&Arch::RequestQuit);
    win->events->Key->Code(SDLK_ESCAPE)->VOID->On(&Arch::RequestQuit);
    win->events->Key->Code(SDLK_w)->Down->On([&wireframe](SDL_Event& e) {
      if (!e.key.repeat)
        wireframe = !wireframe;
    });
    for (int i = 0; i < glProgram->GetAttributeCount(); i++) {
      std::cout << "Attribute " << i << " is " << glProgram->GetAttributeName(i) << std::endl;
    }
    win->preRender->VOID->On([] {
      glClearColor(0.f, 0.f, 0.f, 1.f);
      glClear(GL_COLOR_BUFFER_BIT);
    });
    win->render->On([VAO, &wireframe, firstTex, vertPos2D, vertColor3D, vertTex2D, glProgram, VBO,
                     IBO]() {
      glProgram->Use();
      VAO->Bind();
      IBO->Bind();
      glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
      glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);
      glProgram->StopUse();
    });
    win->arch->MainLoop();

    glDisableVertexAttribArray(vertPos2D);
    glDisableVertexAttribArray(vertColor3D);
    glDisableVertexAttribArray(vertTex2D);
  } catch (Arch::CliHelp& e) {
    std::cout << e << std::endl;
    return 0;
  } catch (std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}