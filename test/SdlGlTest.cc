/** \file
 * \copyright
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
int main(int ac, char** av) {
  try {
    using namespace holo;
    Arch::Configure(ac, av);
    shared_ptr<SdlGlContext> pane{ SdlGlContext::Create("Sdl & OpenGL tests..", SDL_WINDOW_RESIZABLE) };
    pane->events->Window->Resized->On([&](SDL_Event& e) {
      SdlPoint drawableSize{ pane->GetDrawableSize() };
      pane->GlActivateContext();
      glViewport(0, 0, drawableSize.x, drawableSize.y);
    });
    // Hitting escape in any window means the test failed.
    pane->sdl->events->Key->Code(SDLK_ESCAPE)->Up->VOID->On([]() {
      throw std::runtime_error("Escape key pressed.");
    });
    // Closing all windows or otherwise quitting normally means tests passed.
    pane->sdl->events->Quit->VOID->On(&Arch::RequestQuit);
    // Pressing the enter key cancels
    pane->sdl->events->Key->Code(SDLK_RETURN)->Up->VOID->On(&Arch::RequestQuit);
    auto QUIT_TIMEOUT_ID = pane->arch->Timeout(5000, &Arch::RequestQuit);
    auto CancelQuitTimeoutOnce{ [QUIT_TIMEOUT_ID]() {
      if (Arch::Get()->CancelTimeout(QUIT_TIMEOUT_ID)) {
        std::cout << "QUIT TIMEOUT CANCELED\n";
      } else {
        std::cout << "QUIT TIMEOUT ALREADY CANCELED\n";
      };
    } };
    pane->events->Key->Code(SDLK_SPACE)->Up->VOID->Once(CancelQuitTimeoutOnce);
    pane->events->Mouse->Button->Down->VOID->Once(CancelQuitTimeoutOnce);
    // pane->sdl->events->On(SdlEvt::PrintTo(std::cout));
    pane->GlActivateContext();

    glEnable(GL_DEPTH_TEST);
    auto glProgram{ GlSlProgram::Build("share/shaders/test1.vert", "share/shaders/test1.frag") };
    auto VAO{ GlVertexArray::Create() };
    VAO->Bind();
    vector<float> vertices{
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, //
      0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  //
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   //
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   //
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,  //
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, //
                                       //
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  //
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,   //
      0.5f, 0.5f, 0.5f, 1.0f, 1.0f,    //
      0.5f, 0.5f, 0.5f, 1.0f, 1.0f,    //
      -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,   //
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  //
                                       //
      -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   //
      -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,  //
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  //
      -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   //
                                       //
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,    //
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   //
      0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  //
      0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  //
      0.5f, -0.5f, 0.5f, 0.0f, 0.0f,   //
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,    //

      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
      0.5f, -0.5f, -0.5f, 1.0f, 1.0f,  //
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,   //
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,   //
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  //
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //

      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, //
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,  //
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   //
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   //
      -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,  //
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f  //
    };
    vector<vec3> cubePositions{                             //
                                vec3(0.0f, 0.0f, 0.0f),     //
                                vec3(2.0f, 5.0f, -15.0f),   //
                                vec3(-1.5f, -2.2f, -2.5f),  //
                                vec3(-3.8f, -2.0f, -12.3f), //
                                vec3(2.4f, -0.4f, -3.5f),   //
                                vec3(-1.7f, 3.0f, -7.5f),   //
                                vec3(1.3f, -2.0f, -2.5f),   //
                                vec3(1.5f, 2.0f, -2.5f),    //
                                vec3(1.5f, 0.2f, -1.5f),    //
                                vec3(-1.3f, 1.0f, -1.5f)
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

    auto texture1{ SdlGlTexture::Load("share/models/Crate/clear_01.png") };
    auto texture2{ SdlGlTexture::Load("share/textures/Untitled.png") };

    glProgram->Use();
    glProgram->SetInt("texture1", 0);
    glProgram->SetInt("texture2", 1);

    mat4        model{ rotate(mat4{ 1.0f }, radians(-55.0f), vec3(1.0f, 0.0f, 0.0f)) };
    SdlGlCamera camera;
    mat4        projection{ glm::perspective(
      radians(45.0f), (float)pane->GetWidth() / (float)pane->GetHeight(), 0.1f, 100.0f
    ) };

    pane->arch->Step->On(camera.Step);
    auto& kbEvt = pane->events->Key;
    kbEvt->Code(SDLK_w)->Down->VOID->On(camera.ForwardMomentum);
    kbEvt->Code(SDLK_s)->Down->VOID->On(camera.ReverseMomentum);
    kbEvt->Code(SDLK_a)->Down->VOID->On(camera.LeftMomentum);
    kbEvt->Code(SDLK_d)->Down->VOID->On(camera.RightMomentum);
    pane->events->Mouse->Motion->On(camera.SdlMouseMotion);
    pane->events->Mouse->Wheel->On(camera.SdlMouseWheel);

    kbEvt->Code(SDLK_m)->FirstDown->VOID->On([&]() {
      // pane->SetGrab(!pane->GetGrab());
      SDL_SetRelativeMouseMode((SDL_GetRelativeMouseMode() == SDL_TRUE) ? SDL_FALSE : SDL_TRUE);
    });

    pane->render->On([&]() {
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glActiveTexture(GL_TEXTURE0);
      texture1->Bind();
      glActiveTexture(GL_TEXTURE1);
      texture2->Bind();

      glProgram->Use();
      // auto viewLoc = glProgram->GetUniformLocation("view");
      // glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
      mat4 view{ camera.GetView() };
      glProgram->SetMat4("view", view);
      glProgram->SetMat4("projection", projection);
      VAO->Bind();
      for (auto cubePosition : cubePositions) {
        model = translate(mat4{ 1.0f }, cubePosition);
        glProgram->SetMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
      }
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