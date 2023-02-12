#pragma once
#include <holo/Arch.hh>

namespace holo {


  class Pane {
    public: /** Shared references */
      using sPtr = shared_ptr<Pane>;
      shared_ptr<Arch> const arch{ Arch::Get() };
      shared_ptr<VoidDispatcher> render{make_shared<VoidDispatcher>()};
    protected: /** inaccessible constructor */
      explicit Pane();

    public: /** accessible destructor */
      virtual ~Pane();
      virtual void Render()=0;
  };
}
