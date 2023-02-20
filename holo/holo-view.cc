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

class View {
  public:
    static map<uint32_t, shared_ptr<View>> open;
    static shared_ptr<View>                Open(string filename) {
      auto created                = make_shared<View>(filename);
      open[created->glc->GetID()] = created;
      return created;
    };
    shared_ptr<GlSlProgram>        ourShader;
    shared_ptr<GlModel>            ourModel;
    const shared_ptr<SdlGlContext> glc;
    SdlGlCamera                    camera{
      vec3{0.0f, 0.0f, 3.0f}
    };
    vec3 lightPos{ 1.2f, 1.0f, 2.0f };

    View(string filename)
      : glc{ SdlGlContext::Create(filename) } {
      glc->events->Window->Close->VOID->On([this]() {
        this->open.erase(this->glc->GetID());
      });
      glc->GlActivateContext();
      glEnable(GL_DEPTH_TEST);

      glc->arch->Step->On(camera.Step);
      camera.ConnectSdlEvtRoot(glc->events);
      glc->events->Window->Resized->VOID->On([&]() {
        SdlPoint drawableSize{ glc->GetDrawableSize() };
        glc->GlActivateContext();
        glViewport(0, 0, drawableSize.x, drawableSize.y);
      });
      glc->events->Key->Code(SDLK_m)->FirstDown->VOID->On([&]() {
        // pane->SetGrab(!pane->GetGrab());
        SDL_SetRelativeMouseMode(
          (SDL_GetRelativeMouseMode() == SDL_TRUE) ? SDL_FALSE : SDL_TRUE
        );
      });
      ourShader = GlSlProgram::Build("1.model_loading");
      ourModel  = make_shared<GlModel>(
        ShareFiles::Find("share/models/backpack/backpack.obj")
      );
      glc->render->On([&]() {
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ourShader->Use();
        mat4 projection = glm::perspective(
          glm::radians(camera.Zoom), glc->GetWidth() / glc->GetHeight(), 0.1f,
          100.0f
        );
        mat4 view = camera.GetView();
        ourShader->SetMat4("projection", projection);
        ourShader->SetMat4("view", view);

        mat4 model{ 1.0f };
        model = glm::translate(model, vec3(0.0f));
        model = glm::scale(model, vec3(1.0f));
        ourShader->SetMat4("model", model);
        ourModel->Draw(ourShader);
      });
    };
};

map<uint32_t, shared_ptr<View>> View::open;

int main(int ac, char** av) {
  Arch::CFG.hidden.add_options()(
    "view-file", boost::program_options::value<vector<string>>(), "file to view"
  );
  Arch::CFG.positional.add("view-file", -1);
  Arch::Configure(".holo-view", { ".cfg" }, { "." }, { std::getenv("HOME") });
  Arch::Configure(ac, av);
  try {
    if (Arch::CFG.values.count("view-file")) {
      vector<string> filePaths{
        Arch::CFG.values["view-file"].as<vector<string>>()
      };
      for (const string& filePath : filePaths) {
        View::Open(filePath);
      }
      SdlSys::Get()->events->Quit->VOID->On([]() { Arch::RequestQuitAt(0ms); });
      Arch::Get()->MainLoop();
    } else {
      // throw runtime_error("No files specified.");
      View::Open(ShareFiles::Find("share/models/backpack/backpack.obj"));
      Arch::Get()->MainLoop();
    }
  } catch (Arch::CliHelp& e) {
    std::cerr << e << endl;
  } catch (std::exception& e) {
    std::cerr << "ERROR: " << e.what() << endl;
    return 1;
  }
  return 0;
}