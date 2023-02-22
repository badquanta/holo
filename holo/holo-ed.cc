/** \file
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
#include <gtkmm.h>
#include <holo/SdlGl.hh>
#include <thread>

void gtkTask() {
  auto app = Gtk::Application::create("org.gtkmm.example");
  // auto app = Gtk::Application::create("badquanta.holo.ed");

  auto builder{ Gtk::Builder::create_from_file(
    holo::ShareFiles::Require("share/holo-ed.glade")
  ) };
  Gtk::Window* win{nullptr};
  builder->get_widget<Gtk::Window>("Holo-Ed",win);

  Glib::RefPtr<Gtk::Action> quit =  Glib::RefPtr<Gtk::Action>::cast_dynamic(builder->get_object("ActionAppQuit"));
  quit->signal_activate().connect([&](){
    std::cout << "Quit activated.\n";
    holo::Arch::RequestQuit();
    delete win;
  });
  win->signal_hide().connect([&win]() { delete win; });
  app->signal_activate().connect([&]() {
    app->add_window(*win);
    win->show();
  });
  app->run(0,{});
}

int main(int ac, char** av) {

  try {
    std::thread gtk(gtkTask);
    auto        glc{ holo::SdlGlContext::Create("Test 1234") };

    holo::SdlSys::Get()->events->Quit->VOID->On(holo::Arch::RequestQuit);
    glc->arch->MainLoop();
    gtk.join();

  } catch (std::exception& e) {
    std::cerr << "ERROR: " << e.what();
    return 1;
  }
  // return app->make_window_and_run<MyWindow>(ac, av);
  return 0;
}