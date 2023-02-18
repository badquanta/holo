#define BOOST_TEST_MODULE HoloSdlGl_tests
#include <boost/test/included/unit_test.hpp>
#include <holo/sdl/GlCamera.hh>
#include <holo/sdl/GlContext.hh>

using namespace holo;
// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
vector<float> cubeVertices{
  -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, //
  0.5f,  -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, //
  0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, //
  0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, //
  -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, //
  -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, //
  -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  //
  0.5f,  -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  //
  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  //
  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  //
  -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  //
  -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  //
  -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  //
  -0.5f, 0.5f,  -0.5f, -1.0f, 0.0f,  0.0f,  //
  -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  //
  -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  //
  -0.5f, -0.5f, 0.5f,  -1.0f, 0.0f,  0.0f,  //
  -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  //
  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  //
  0.5f,  0.5f,  -0.5f, 1.0f,  0.0f,  0.0f,  //
  0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  //
  0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  //
  0.5f,  -0.5f, 0.5f,  1.0f,  0.0f,  0.0f,  //
  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  //
  -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  //
  0.5f,  -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  //
  0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  //
  0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  //
  -0.5f, -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  //
  -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  //
  -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  //
  0.5f,  0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  //
  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  //
  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  //
  -0.5f, 0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  //
  -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f   //
};
BOOST_AUTO_TEST_CASE(firstRun) {
  auto glc{ SdlGlContext::Create("firstRun") };
  // so something worth-while and like clear the screen.
  glc->render->On([]() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
  });
  glc->arch->Timeout(250, &Arch::RequestQuit);
  glc->arch->MainLoop();
}

BOOST_AUTO_TEST_CASE(secondRun) {
  auto glc{ SdlGlContext::Create("firstRun") };
  // so something worth-while and like clear the screen.
  glc->render->On([]() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
  });
  glc->arch->Timeout(250, &Arch::RequestQuit);
  glc->arch->MainLoop();
}

BOOST_AUTO_TEST_CASE(SdlGlBasicLighting2_2) {
  auto        glc{ SdlGlContext::Create("basic lighting", 800, 600) };
  SdlGlCamera camera{
    vec3{0.0f, 0.0f, 3.0f}
  };
  glEnable(GL_DEPTH_TEST);
  auto lightingShader{ GlSlProgram::Build("2.2.basic_lighting") };
  auto lightCubeShader{ GlSlProgram::Build("2.2.light_cube") };
  auto cubeVAO{ GlVertexArray::Create() };
  auto cubeVBO{ GlBuffer<GL_ARRAY_BUFFER, GLfloat, GL_STATIC_DRAW>::Create(cubeVertices) };
  cubeVAO->Bind();
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  auto lightCubeVAO{ GlVertexArray::Create() };
  lightCubeVAO->Bind();
  cubeVBO->Bind();
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  vec3 lightPos(1.2f,1.0f,2.0f);
  glc->render->On([&]() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    lightingShader->Use();
    lightingShader->SetVec3("objectColor", 1.0f, 0.5f, 0.31f);
    lightingShader->SetVec3("lightColor", 1.0f, 1.0f, 1.0f);
    lightingShader->SetVec3("lightPos", lightPos);
    lightingShader->SetVec3("viewPos", camera.Position);
    mat4 projection{ glm::perspective(
      glm::radians(camera.Zoom), (float)glc->GetWidth() / (float)glc->GetHeight(), 0.1f, 100.0f
    ) };
    lightingShader->SetMat4("projection", projection);
    mat4 view{ camera.GetView() };
    mat4 model{1.0f};
    lightingShader->SetMat4("view", view);
    lightingShader->SetMat4("model", model);
    cubeVAO->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);

    lightCubeShader->Use();
    lightCubeShader->SetMat4("projection",projection);
    lightCubeShader->SetMat4("view",view);

    model = glm::scale(glm::translate(mat4{1.0f},lightPos),vec3(0.2f));
    lightCubeShader->SetMat4("model",model);
    lightCubeVAO->Bind();
    glDrawArrays(GL_TRIANGLES,0,36);

  });
  glc->arch->Timeout(5000, &Arch::RequestQuit);
  glc->arch->MainLoop();
}
