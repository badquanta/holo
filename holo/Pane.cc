#include <holo/Pane.hh>
namespace holo {
  using namespace std::placeholders;
  using std::bind;
  Pane::Pane()
    : OutputID{ arch->Output->On([this]() { this->Render(); }) } {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }

  Pane::~Pane() {
    arch->Output->Off(OutputID);
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }

  void Pane::Render() {
    render->Trigger();
    //BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }

}