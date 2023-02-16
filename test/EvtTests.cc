#define BOOST_TEST_MODULE EvtTests
#include <boost/test/included/unit_test.hpp>
#include <holo/Evt.hh>
using namespace holo;
BOOST_AUTO_TEST_CASE(free_test_function) {
  BOOST_TEST(true);
}

BOOST_AUTO_TEST_CASE(EvtAbstract_Int32) {
  EvtAbstract<int32_t> mine;
  mine.On([](int32_t n){
    std::cout << "Mine called with #"<<n<<std::endl;
  });
  mine.Trigger(1);
  mine.Trigger(-120);
  mine.Trigger(120);
}
