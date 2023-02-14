#include <holo/Evt.hh>
namespace holo {
/** \brief Every handler registered is given an ID. */
  static CallbackID       EvtCallbackNextId;
  CallbackID NextEvtID(){
    return ++EvtCallbackNextId;
  }
}