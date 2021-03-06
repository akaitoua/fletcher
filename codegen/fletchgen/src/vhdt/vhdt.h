// Copyright 2018 Delft University of Technology
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <regex>
#include <map>

#include "../logging.h"

namespace fletchgen {

// @brief Structure to hold a template replacement string location
struct trloc {
  trloc(size_t line, size_t start) : line(line), start(start) {};
  size_t line;
  size_t start;
};

/// @brief Class to hold and modify a VHDL template file.
class VHDLTemplate {
 public:
  ///@brief Construct a VHDL template file holder.
  explicit VHDLTemplate(const std::string &filename);
  ///@brief Replace a template replacement string with some number.
  void replace(const std::string &str, int with);
  ///@brief Replace a template replacement string with some other string.
  void replace(const std::string &str, const std::string &with);
  ///@brief Return the file as a string.
  std::string toString();
 private:
  std::map<std::string, std::vector<trloc>> replace_list_; ///< Map from a template replacement string to a vector of line numbers.
  std::vector<std::string> lines_; ///< Lines of the file.
};

} //namespace fletchgen
