/**
 * \example test/SdlGl.test.cc
 */
#define BOOST_TEST_MODULE HoloSdlGl_tests
#include <boost/test/included/unit_test.hpp>
#include <holo/SdlGl.hh>

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

  -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f, //
  -0.5f, 0.5f,  -0.5f, -1.0f, 0.0f,  0.0f, //
  -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f, //
  -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f, //
  -0.5f, -0.5f, 0.5f,  -1.0f, 0.0f,  0.0f, //
  -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f, //
  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, //
  0.5f,  0.5f,  -0.5f, 1.0f,  0.0f,  0.0f, //
  0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f, //
  0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f, //
  0.5f,  -0.5f, 0.5f,  1.0f,  0.0f,  0.0f, //
  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, //

  -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f, //
  0.5f,  -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f, //
  0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f, //
  0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f, //
  -0.5f, -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f, //
  -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f, //
  -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f, //
  0.5f,  0.5f,  -0.5f, 0.0f,  1.0f,  0.0f, //
  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, //
  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, //
  -0.5f, 0.5f,  0.5f,  0.0f,  1.0f,  0.0f, //
  -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f  //
};
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
  cubeVBO->Bind();
  cubeVAO->Bind();
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  auto lightCubeVAO{ GlVertexArray::Create() };
  lightCubeVAO->Bind();
  cubeVBO->Bind();
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glc->arch->Step->On(camera.Step);
  camera.ConnectSdlEvtRoot(glc->events);
  vec3 lightPos(1.2f, 1.0f, 2.0f);
  glc->render->On([&]() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
    lightingShader->SetMat4("view", view);
    mat4 model{ 1.0f };
    lightingShader->SetMat4("model", model);
    cubeVAO->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);

    lightCubeShader->Use();
    lightCubeShader->SetMat4("projection", projection);
    lightCubeShader->SetMat4("view", view);
    model = glm::scale(glm::translate(mat4{ 1.0f }, lightPos), vec3(0.2f));
    lightCubeShader->SetMat4("model", model);
    lightCubeVAO->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
  });
  glc->arch->Timeout(1000, &Arch::RequestQuit);
  glc->arch->MainLoop();
}

BOOST_AUTO_TEST_CASE(SdlGlMaterialLighting3_1) {
  auto        glc{ SdlGlContext::Create("learnopengl.com 3.1 materials") };
  SdlGlCamera camera{ vec3(0.0f, 0.0f, 3.0f) };
  vec3        lightPos(1.2f, 1.0f, 2.0f);
  glc->GlActivateContext();
  glEnable(GL_DEPTH_TEST);
  auto lightingShader{ GlSlProgram::Build("3.1.materials") };
  auto lightCubeShader{ GlSlProgram::Build("3.1.light_cube") };
  auto cubeVAO{ GlVertexArray::Create() };
  auto VBO{ GlBuffer<GL_ARRAY_BUFFER, float, GL_STATIC_DRAW>::Create(cubeVertices) };
  cubeVAO->Bind();
  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // normal attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  auto lightingVAO{ GlVertexArray::Create() };
  lightingVAO->Bind();
  VBO->Bind();

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glc->arch->Step->On(camera.Step);
  camera.ConnectSdlEvtRoot(glc->events);

  // light properties
  vec3 lightColor{ 1.0f, 1.0f, 1.0f };
  vec3 diffuseColor;
  vec3 ambientColor;
  glc->arch->Step->On([&](milliseconds deltaMS) {
    lightColor.x = static_cast<float>(sin((deltaMS.count() / 100.0f)));
    lightColor.y = static_cast<float>(sin((deltaMS.count() / 100.0f)));
    lightColor.z = static_cast<float>(sin((deltaMS.count() / 100.0f)));
    diffuseColor = lightColor * glm::vec3(0.5f);   // decrease the influence
    ambientColor = diffuseColor * glm::vec3(0.2f); // low influence
  });

  glc->render->On([&]() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    lightingShader->Use();
    lightingShader->SetVec3("light.position", lightPos);
    lightingShader->SetVec3("viewPos", camera.Position);
    lightingShader->SetVec3("light.specular", 1.0f, 1.0f, 1.0f);
    lightingShader->SetVec3("light.ambient", ambientColor);
    lightingShader->SetVec3("light.diffuse", diffuseColor);

    // material properties
    lightingShader->SetVec3("material.ambient", 1.0f, 0.5f, 0.31f);
    lightingShader->SetVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
    lightingShader->SetVec3("material.specular", 0.5f, 0.5f, 0.5f);
    // specular lighting doesn't have full effect on this object's material
    lightingShader->SetFloat("material.shininess", 32.0f);

    mat4 projection = glm::perspective(
      glm::radians(camera.Zoom), (float)glc->GetWidth() / (float)glc->GetHeight(), 0.1f, 100.0f
    );
    mat4 view = camera.GetView();
    lightingShader->SetMat4("projection", projection);
    lightingShader->SetMat4("view", view);

    mat4 model{ 1.0f };
    lightingShader->SetMat4("model", model);

    cubeVAO->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    lightCubeShader->Use();
    lightCubeShader->SetMat4("projection", projection);
    lightCubeShader->SetMat4("view", view);
    lightCubeShader->SetMat4("model", scale(translate(mat4(1.0f), lightPos), vec3(0.2f)));
    lightingVAO->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
  });

  glc->arch->Timeout(1000, &Arch::RequestQuit);
  glc->arch->MainLoop();
}
class TestProgram {
  public:
    const shared_ptr<SdlGlContext> glc;
    SdlGlCamera                    camera{ vec3(0.0f, 0.0f, 3.0f) };
    vec3                           lightPos{ 1.2f, 1.0f, 2.0f };
    TestProgram(string title)
      : glc{ SdlGlContext::Create(title, SDL_WINDOW_RESIZABLE) } {
      glc->GlActivateContext();
      glEnable(GL_DEPTH_TEST);
      auto QUIT_TIMEOUT_ID = glc->arch->Timeout(1000, &Arch::RequestQuit);
      auto CancelQuitTimeoutOnce{ [QUIT_TIMEOUT_ID]() {
        if (Arch::Get()->CancelTimeout(QUIT_TIMEOUT_ID)) {
          std::cout << "QUIT TIMEOUT CANCELED\n";
        } else {
          std::cout << "QUIT TIMEOUT ALREADY CANCELED\n";
        };
      } };
      glc->events->Window->Close->VOID->On(&Arch::RequestQuit);
      glc->events->Key->Code(SDLK_SPACE)->Up->VOID->Once(CancelQuitTimeoutOnce);
      glc->events->Mouse->Button->Down->VOID->Once(CancelQuitTimeoutOnce);
      glc->arch->Step->On(camera.Step);
      camera.ConnectSdlEvtRoot(glc->events);
      glc->events->Window->Resized->VOID->On([&]() {
        SdlPoint drawableSize{ glc->GetDrawableSize() };
        glc->GlActivateContext();
        glViewport(0, 0, drawableSize.x, drawableSize.y);
      });
      glc->events->Key->Code(SDLK_m)->FirstDown->VOID->On([&]() {
        // pane->SetGrab(!pane->GetGrab());
        SDL_SetRelativeMouseMode((SDL_GetRelativeMouseMode() == SDL_TRUE) ? SDL_FALSE : SDL_TRUE);
      });
    }
};
// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
vector<float> cubeVertNormTexts{
  // positions          // normals           // texture coords
  -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f,  0.0f,  0.5f,  -0.5f, -0.5f, 0.0f,
  0.0f,  -1.0f, 1.0f,  0.0f,  0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f,  1.0f,
  0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f,  1.0f,  -0.5f, 0.5f,  -0.5f, 0.0f,
  0.0f,  -1.0f, 0.0f,  1.0f,  -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f,  0.0f,

  -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.5f,  -0.5f, 0.5f,  0.0f,
  0.0f,  1.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,  -0.5f, 0.5f,  0.5f,  0.0f,
  0.0f,  1.0f,  0.0f,  1.0f,  -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

  -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  1.0f,  0.0f,  -0.5f, 0.5f,  -0.5f, -1.0f,
  0.0f,  0.0f,  1.0f,  1.0f,  -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f,  1.0f,
  -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f,  1.0f,  -0.5f, -0.5f, 0.5f,  -1.0f,
  0.0f,  0.0f,  0.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  1.0f,  0.0f,

  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  -0.5f, 1.0f,
  0.0f,  0.0f,  1.0f,  1.0f,  0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
  0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f,  1.0f,  0.5f,  -0.5f, 0.5f,  1.0f,
  0.0f,  0.0f,  0.0f,  0.0f,  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

  -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f,  1.0f,  0.5f,  -0.5f, -0.5f, 0.0f,
  -1.0f, 0.0f,  1.0f,  1.0f,  0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  1.0f,  0.0f,
  0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  1.0f,  0.0f,  -0.5f, -0.5f, 0.5f,  0.0f,
  -1.0f, 0.0f,  0.0f,  0.0f,  -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f,  1.0f,

  -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.5f,  0.5f,  -0.5f, 0.0f,
  1.0f,  0.0f,  1.0f,  1.0f,  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  0.0f,
  1.0f,  0.0f,  0.0f,  0.0f,  -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};
BOOST_AUTO_TEST_CASE(SdlGlLightingMaps) {
  TestProgram test("learnopengl.com 4.2 lighting map specular");
  auto        lightingShader{ GlSlProgram::Build("4.2.lighting_maps") };
  auto        lightCubeShader{ GlSlProgram::Build("4.2.light_cube") };
  auto        cubeVAO{ GlVertexArray::Create() };
  auto        cubeVertBuffer{ GlBufferFloatDraw::Create(cubeVertNormTexts) };
  cubeVertBuffer->Bind();
  cubeVAO->Bind();
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  auto lightCubeVAO{ GlVertexArray::Create() };
  lightCubeVAO->Bind();
  cubeVertBuffer->Bind();
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  auto diffuseMap{ SdlGlTexture::Load("share/textures/container2.png") };
  auto specularMap{ SdlGlTexture::Load("share/textures/container2_specular.png") };
  lightingShader->Use();
  lightingShader->SetInt("material.diffuse", 0);
  lightingShader->SetInt("material.specular", 1);

  test.glc->arch->Step->On([&](milliseconds msDelta) {

  });
  test.glc->render->On([&]() {
    // ------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // be sure to activate shader when setting uniforms/drawing objects
    lightingShader->Use();
    lightingShader->SetVec3("light.position", test.lightPos);
    lightingShader->SetVec3("viewPos", test.camera.Position);

    // light properties
    lightingShader->SetVec3("light.ambient", 0.2f, 0.2f, 0.2f);
    lightingShader->SetVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
    lightingShader->SetVec3("light.specular", 1.0f, 1.0f, 1.0f);

    // material properties
    lightingShader->SetFloat("material.shininess", 64.0f);

    // view/projection transformations
    mat4 projection = glm::perspective(
      glm::radians(test.camera.Zoom), (float)test.glc->GetWidth() / (float)test.glc->GetHeight(),
      0.1f, 100.0f
    );
    mat4 view = test.camera.GetView();
    lightingShader->SetMat4("projection", projection);
    lightingShader->SetMat4("view", view);

    // world transformation
    glm::mat4 model = glm::mat4(1.0f);
    lightingShader->SetMat4("model", model);

    // bind diffuse map
    glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, diffuseMap);
    diffuseMap->Bind();
    // bind specular map
    glActiveTexture(GL_TEXTURE1);
    // glBindTexture(GL_TEXTURE_2D, specularMap);
    specularMap->Bind();

    // render the cube
    // glBindVertexArray(cubeVAO);
    cubeVAO->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // also draw the lamp object
    lightCubeShader->Use();
    lightCubeShader->SetMat4("projection", projection);
    lightCubeShader->SetMat4("view", view);
    model = glm::mat4(1.0f);
    model = glm::translate(model, test.lightPos);
    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
    lightCubeShader->SetMat4("model", model);

    lightCubeVAO->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
  });

  test.glc->arch->MainLoop();
}

BOOST_AUTO_TEST_CASE(SdlGlDirectionalLight) {
  TestProgram test("LearnOpenGL.com Multiple Lights");
  auto        lightingShader{ GlSlProgram::Build("6.multiple_lights") };
  auto        lightCubeShader{ GlSlProgram::Build("6.light_cube") };

  vector<vec3> cubePositions{ glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
                              glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
                              glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
                              glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
                              glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f) };

  vector<vec3> pointLightPositions{ glm::vec3(0.7f, 0.2f, 2.0f), glm::vec3(2.3f, -3.3f, -4.0f),
                                    glm::vec3(-4.0f, 2.0f, -12.0f), glm::vec3(0.0f, 0.0f, -3.0f) };

  auto cubeVAO{ GlVertexArray::Create() };
  auto VBO{ GlBufferFloatDraw::Create(cubeVertNormTexts) };
  cubeVAO->Bind();
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);
  auto lightCubeVAO{ GlVertexArray::Create() };
  lightCubeVAO->Bind();
  VBO->Bind();
  // note that we update the lamp's position attribute's stride to reflect the updated buffer data
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  auto diffuseMap{ SdlGlTexture::Load("share/textures/container2.png") };
  auto specularMap{ SdlGlTexture::Load("share/textures/container2_specular.png") };
  lightingShader->Use();
  lightingShader->SetInt("material.diffuse", 0);
  lightingShader->SetInt("material.specular", 1);

  test.glc->render->On([&]() {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    lightingShader->Use();
    lightingShader->SetVec3("viewPos", test.camera.Position);
    lightingShader->SetFloat("material.shininess", 32.0f);
    /*
           Here we set all the uniforms for the 5/6 types of lights we have. We have to set them
       manually and index the proper PointLight struct in the array to set each uniform variable.
       This can be done more code-friendly by defining light types as classes and set their values
       in there, or by using a more efficient uniform approach by using 'Uniform buffer objects',
       but that is something we'll discuss in the 'Advanced GLSL' tutorial.
        */
    // directional light
    lightingShader->SetVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
    lightingShader->SetVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
    lightingShader->SetVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
    lightingShader->SetVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
    // point light 1
    lightingShader->SetVec3("pointLights[0].position", pointLightPositions[0]);
    lightingShader->SetVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
    lightingShader->SetVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
    lightingShader->SetVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
    lightingShader->SetFloat("pointLights[0].constant", 1.0f);
    lightingShader->SetFloat("pointLights[0].linear", 0.09f);
    lightingShader->SetFloat("pointLights[0].quadratic", 0.032f);
    // point light 2
    lightingShader->SetVec3("pointLights[1].position", pointLightPositions[1]);
    lightingShader->SetVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
    lightingShader->SetVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
    lightingShader->SetVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
    lightingShader->SetFloat("pointLights[1].constant", 1.0f);
    lightingShader->SetFloat("pointLights[1].linear", 0.09f);
    lightingShader->SetFloat("pointLights[1].quadratic", 0.032f);
    // point light 3
    lightingShader->SetVec3("pointLights[2].position", pointLightPositions[2]);
    lightingShader->SetVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
    lightingShader->SetVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
    lightingShader->SetVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
    lightingShader->SetFloat("pointLights[2].constant", 1.0f);
    lightingShader->SetFloat("pointLights[2].linear", 0.09f);
    lightingShader->SetFloat("pointLights[2].quadratic", 0.032f);
    // point light 4
    lightingShader->SetVec3("pointLights[3].position", pointLightPositions[3]);
    lightingShader->SetVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
    lightingShader->SetVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
    lightingShader->SetVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
    lightingShader->SetFloat("pointLights[3].constant", 1.0f);
    lightingShader->SetFloat("pointLights[3].linear", 0.09f);
    lightingShader->SetFloat("pointLights[3].quadratic", 0.032f);
    // spotLight
    lightingShader->SetVec3("spotLight.position", test.camera.Position);
    lightingShader->SetVec3("spotLight.direction", test.camera.Front);
    lightingShader->SetVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
    lightingShader->SetVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
    lightingShader->SetVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
    lightingShader->SetFloat("spotLight.constant", 1.0f);
    lightingShader->SetFloat("spotLight.linear", 0.09f);
    lightingShader->SetFloat("spotLight.quadratic", 0.032f);
    lightingShader->SetFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    lightingShader->SetFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

    mat4 projection{ glm::perspective(
      glm::radians(test.camera.Zoom), test.glc->GetWidth() / test.glc->GetHeight(), 0.1f, 100.0f
    ) };
    mat4 view{ test.camera.GetView() };
    lightingShader->SetMat4("projection", projection);
    lightingShader->SetMat4("view", view);
    mat4 model{ 1.0f };
    lightingShader->SetMat4("model", model);

    diffuseMap->Bind(GL_TEXTURE0);
    specularMap->Bind(GL_TEXTURE1);

    cubeVAO->Bind();
    // render containers
    for (uint32_t i = 0; i < 10; i++) {
      lightingShader->SetMat4(
        "model", glm::rotate(
                   glm::translate(mat4{ 1.0f }, cubePositions[i]), glm::radians(20.0f * i),
                   vec3{ 1.0f, 0.3f, 0.5f }
                 )
      );
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    lightCubeShader->Use();
    lightCubeShader->SetMat4("projection", projection);
    lightCubeShader->SetMat4("view", view);
    lightCubeVAO->Bind();
    for (uint32_t i = 0; i < 4; i++) {
      lightCubeShader->SetMat4(
        "model", glm::scale(glm::translate(mat4{ 1.0f }, pointLightPositions[i]), vec3{ 0.2f })
      );
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }
  });
  test.glc->arch->MainLoop();
}

#include <holo/ShareFiles.hh>
#include <holo/gl/Model.hh>

BOOST_AUTO_TEST_CASE(SdlGlModelLoading) {
  TestProgram test("LearnOpenGL.com Model Loading");
  auto        ourShader{ GlSlProgram::Build("1.model_loading") };
  GlModel     ourModel(ShareFiles::Find("share/models/backpack/backpack.obj"));
  test.glc->render->On([&]() {
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ourShader->Use();
    mat4 projection = glm::perspective(
      glm::radians(test.camera.Zoom), test.glc->GetWidth()/ test.glc->GetHeight(), 0.1f, 100.0f
    );
    mat4 view = test.camera.GetView();
    ourShader->SetMat4("projection", projection);
    ourShader->SetMat4("view", view);

    mat4 model{ 1.0f };
    model = glm::translate(model, vec3(0.0f));
    model = glm::scale(model, vec3(1.0f));
    ourShader->SetMat4("model", model);
    ourModel.Draw(ourShader);
  });
  test.glc->arch->MainLoop();
}