#pragma once
#include <holo/Arch.hh>

namespace holo {

  class Pane {
    public: /** Shared references */
      using sPtr = shared_ptr<Pane>;
      shared_ptr<Arch> const     arch{ Arch::Get() };
      shared_ptr<EvtVoid> render{ make_shared<EvtVoid>() };
      CallbackID const           OutputID;

    protected: /** inaccessible constructor */
      explicit Pane();

    public: /** accessible destructor */
      virtual ~Pane();
      virtual void Render();
  };
}
