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
#include <boost/dll/runtime_symbol_info.hpp>
#include <holo/ShareFiles.hh>
#include <holo/boostPrimitives.hh>
namespace holo {
  boost::filesystem::path __program_location_path{ boost::dll::program_location() };

  vector<string> ShareFiles::SearchAbsolutes{
    __program_location_path.parent_path().parent_path().string(),
    __program_location_path.parent_path().string()  };
  map<string, string> ShareFiles::Found{};

  string ShareFiles::Find(
    const string& path, const vector<string>& trySuffixes, const vector<string>& tryPrefixes,
    const vector<string>& tryAbsolutes
  ) {
    if (!(Found.contains(path))) {
      BOOST_LOG_TRIVIAL(info) << "holo::ShareFiles::Find('" << path << "')";
      /**
      if (trySuffixes.size() > 0) {
        for (auto s : trySuffixes) {
          BOOST_LOG_TRIVIAL(debug) << "trySuffix:" << s;
        }
      } else {
        BOOST_LOG_TRIVIAL(debug) << "trySuffixes is empty";
      }
      if (tryPrefixes.size() > 0) {
        for (auto p : tryPrefixes) {
          BOOST_LOG_TRIVIAL(debug) << "tryPrefix:" << p;
        }
      } else {
        BOOST_LOG_TRIVIAL(debug) << "tryPrefixes is empty";
      }
      if (tryAbsolutes.size() > 0) {
        for (auto a : tryAbsolutes) {
          BOOST_LOG_TRIVIAL(debug) << "tryAbsolute:" << a;
        }
      } else {
        BOOST_LOG_TRIVIAL(debug) << "tryAbsolutes is empty";
      }
      **/
      vector<string> suffixVariations{ path };

      for (const string& suffix : trySuffixes) {
        suffixVariations.push_back(path + suffix);
      }

      vector<string> prefixVariations{ suffixVariations };
      for (const string& prefix : tryPrefixes) {
        filesystem::path prefixPath(prefix);
        for (const string& variation : suffixVariations) {
          filesystem::path variationPath(variation);
          if (variationPath.is_relative()) {
            prefixVariations.push_back((prefixPath / variation).string());
          }
        }
      }
      vector<string> absoluteVariations{ prefixVariations };
      vector<string> allAbsolutes{ SearchAbsolutes };
      allAbsolutes.insert(allAbsolutes.end(), tryAbsolutes.begin(), tryAbsolutes.end());
      for (const string& absolute : allAbsolutes) {
        filesystem::path absolutePath(absolute);
        for (const filesystem::path variation : prefixVariations) {
          if (variation.is_relative()) {
            absoluteVariations.push_back((absolutePath / variation).string());
          }
        }
      }
      //stringstream vstr;
      //for (const string& variation : absoluteVariations) {
      //  vstr << endl << "path: '" << variation << "'";
      //}
      //BOOST_LOG_TRIVIAL(debug) << "holo::ShareFiles(...)"
      //                         << " searching paths:" << endl
      //                         << vstr.str();
      for (const string& variation : absoluteVariations) {
        if (filesystem::exists(variation)) {
          BOOST_LOG_TRIVIAL(info) << " found: '" << path << "' at '"
                                  << variation << "'";
          return Found[path] = variation;
        }
      }
      // If we make it through the for loop to here, we did not find it.
      // We return "" to indicate not found.
      BOOST_LOG_TRIVIAL(warning) << __PRETTY_FUNCTION__ << " path not found: '" << path << "'";
      return "";
    }
    return Found[path];
  }

  string ShareFiles::Require(
    const string& path, const vector<string>& trySuffixes, const vector<string>& tryPrefixes,
    const vector<string>& tryAbsolutes
  ) {
    string found{ Find(path, trySuffixes, tryPrefixes, tryAbsolutes) };
    if (!Found.contains(path)) {
      throw std::runtime_error("ShareFiles::Require() file not found: `" + path + "`.");
    }
    return found;
  }
} // namespace holo
