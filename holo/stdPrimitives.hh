#pragma once
#include <chrono>
#include <functional>
#include <map>
#include <memory>
#include <assert.h>
#include <utility>
#include <filesystem>
#include <vector>
#include <string>
namespace holo {
  using std::string;
  using std::function;
  using std::map;
  using std::vector;
  using std::filesystem::path;
  using std::shared_ptr;
  using std::weak_ptr;
  using std::make_shared;
  using std::bind;
  using std::unreachable;
  using std::chrono::nanoseconds;
  using std::chrono::microseconds;
  using std::chrono::milliseconds;
  using std::chrono::seconds;
  using std::chrono::minutes;
  using std::chrono::hours;
  /** \todo include chrono hours, days, etc? */
  using std::chrono::system_clock;
  using std::chrono::steady_clock;
  using std::chrono::high_resolution_clock;
  using std::chrono::duration;


}