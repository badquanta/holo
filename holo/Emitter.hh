#pragma once
#include <holo/Arch.hh>

namespace holo {

  class Emitter {
    public: /** Shared references */
      using sPtr = shared_ptr<Emitter>;
      shared_ptr<Arch> const     arch{ Arch::Get() };
      shared_ptr<EvtVoid> render{ make_shared<EvtVoid>() };
      CallbackID const           OutputID;

    protected: /** inaccessible constructor */
      explicit Emitter();

    public: /** accessible destructor */
      virtual ~Emitter();
      virtual void Render();
  };
}
