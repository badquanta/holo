#include <holo/Pane.hh>
namespace holo {
  using namespace std::placeholders;
  using std::bind;
  Pane::Pane() {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }

  Pane::~Pane() {
    BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
  }


}