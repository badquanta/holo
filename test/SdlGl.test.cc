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
    vec3                           lightPos{1.2f, 1.0f, 2.0f};
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
  auto        cubeVertBuffer{ GlBufferVertDraw::Create(cubeVertNormTexts) };
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