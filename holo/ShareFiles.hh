#pragma once
/** \file
 * \copyright
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
#include <holo/stdPrimitives.hh>
namespace holo {
  class ShareFiles {
    public:
      /** If not otherwise specified, these absolute paths will be tried for any non-absolute path
       * searched.*/
      static map<string, string> Found;
      static vector<string>      SearchAbsolutes;
      /** Search for a given path:
       * Check `Found` for previously discovered paths.
       */
      static string Find(
        const string& path, const vector<string>& trySuffixes = {},
        const vector<string>& tryPrefixes = {}, const vector<string>& tryAbsolutes = SearchAbsolutes
      );
      static string Require(
        const string& path, const vector<string>& trySuffixes = {},
        const vector<string>& tryPrefixes = {}, const vector<string>& tryAbsolutes = SearchAbsolutes
      );
  };
}