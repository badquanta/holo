#include <holo/Emitter.hh>
namespace holo {
  using namespace std::placeholders;
  using std::bind;
  Emitter::Emitter()
    : OutputID{ arch->Output->On([this]() { this->Render(); }) } {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }

  Emitter::~Emitter() {
    arch->Output->Off(OutputID);
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }

  void Emitter::Render() {
    render->Trigger();
    //BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }

}