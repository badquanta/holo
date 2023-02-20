/** \file
 *  \copyright
holo
Copyright (C) 2023  Jon David Sawyer

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/
#pragma once
#include <assert.h>
#include <chrono>
#include <filesystem>
#include <functional>
#include <map>
#include <memory>
#include <numeric>
#include <sstream>
#include <stack>
#include <stdlib.h>
#include <string>
#include <utility>
#include <vector>
namespace holo {
  using std::bind;
  using std::chrono::duration;
  using std::chrono::high_resolution_clock;
  using std::chrono::hours;
  using namespace std::chrono_literals;
  using std::chrono::microseconds;
  using std::chrono::milliseconds;
  using std::chrono::minutes;
  using std::chrono::nanoseconds;
  using std::chrono::seconds;
  using std::chrono::steady_clock;
  using std::chrono::system_clock;
  using std::endl;
  using std::function;
  using std::make_shared;
  using std::map;
  using std::runtime_error;
  using std::shared_ptr;
  using std::stack;
  using std::string;
  using std::stringstream;
  using std::unreachable;
  using std::vector;
  using std::weak_ptr;
  using std::filesystem::path;
  namespace filesystem = std::filesystem;

  /** \todo include chrono hours, days, etc? */

}