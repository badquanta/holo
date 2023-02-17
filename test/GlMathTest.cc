#define BOOST_TEST_MODULE GlMathTest
#include <boost/test/included/unit_test.hpp>
#include <holo/gl/math.hh>

using namespace holo;

BOOST_AUTO_TEST_CASE(GlMathPractice01) {
  vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
  mat4 trans = mat4(1.0f);
  trans      = translate(trans, vec3(1.0f, 1.0f, 0.0f));

  vec = trans * vec;
  std::cout << vec.x << "," << vec.y << "," << vec.z << std::endl;
}

BOOST_AUTO_TEST_CASE(GlMathPractice02) {
  vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
  mat4 trans = mat4(1.0f);
  trans      = rotate(trans, radians(90.0f), vec3(0.0, 0.0, 1.0));
  trans      = scale(trans, vec3(0.5, 0.5, 0.5));

  vec = trans * vec;
  std::cout << vec.x << "," << vec.y << "," << vec.z << std::endl;
}

BOOST_AUTO_TEST_CASE(GlMathCameraPractice) {
  vec3 cameraPos       = vec3(0.0f, 0.0f, 3.0f);
  vec3 cameraTarget    = vec3(0.0f, 0.0f, 0.0f);
  vec3 cameraDirection = normalize(cameraPos - cameraTarget);
  vec3 up = vec3(0.0f,1.0f,0.0f);
  vec3 cameraRight = normalize(cross(up,cameraDirection));
  vec3 cameraUp = cross(cameraDirection, cameraRight);
}
