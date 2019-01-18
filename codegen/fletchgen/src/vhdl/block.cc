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

#include <iostream>
#include <sstream>

#include "./block.h"

namespace fletchgen {
namespace vhdl {

Line &operator<<(Line &lhs, const std::string &str) {
  lhs.parts.emplace_back(str);
  return lhs;
}

Line &operator<<(Line &lhs, const Line &rhs) {
  lhs.parts.insert(lhs.parts.end(), rhs.parts.begin(), rhs.parts.end());
  return lhs;
}

Line &operator+=(Line &lhs, const std::string &str) {
  lhs.parts.back().append(str);
  return lhs;
}

std::vector<size_t> Block::GetAlignments() const {
  std::vector<size_t> ret = {0};
  for (const auto &l : lines) {
    for (uint p = 0; p < l.parts.size(); p++) {
      if (p >= ret.size()) {
        ret.push_back(l.parts[p].length());
      } else if (l.parts[p].length() > ret[p]) {
        ret[p] = l.parts[p].length();
      }
    }
  }
  return ret;
}

std::string Block::str() const {
  std::stringstream ret;
  auto a = GetAlignments();
  for (const auto &l : lines) {
    ret << std::string(2 * indent, ' ');
    for (size_t p = 0; p < l.parts.size(); p++) {
      auto align = a[p];
      auto plen = l.parts[p].length();
      auto diff = align - plen;
      if (diff != 0) {
        auto padding = std::string(diff, ' ');
        ret << l.parts[p] + padding;
      } else {
        ret << l.parts[p];
      }
    }
    ret << "\n";
  }
  return ret.str();
}

Block &operator<<(Block &lhs, const Line &line) {
  lhs.lines.push_back(line);
  return lhs;
}

Block &operator<<(Block &lhs, const Block &rhs) {
  lhs.lines.insert(std::end(lhs.lines), std::begin(rhs.lines), std::end(rhs.lines));
  return lhs;
}

Block &prepend(const std::string &lhs, Block &rhs) {
  for (auto &l : rhs.lines) {
    if (!l.parts.empty()) {
      l.parts.front() = lhs + l.parts.front();
    } else {
      l << lhs;
    }
  }
  return rhs;
}

Block &operator<<(Block &lhs, const std::string &rhs) {
  if (!lhs.lines.empty()) {
    for (auto &l : lhs.lines) {
      if (!l.parts.empty()) {
        l.parts.back().append(rhs);
      }
    }
  } else {
    Line t;
    t << rhs;
    lhs << t;
  }
  return lhs;
}

Block &operator<<=(Block &lhs, const std::string &rhs) {
  for (uint i = 0; i < lhs.lines.size() - 1; i++) {
    lhs.lines[i].parts.back().append(rhs);
  }
  return lhs;
}

MultiBlock &operator<<(MultiBlock &lhs, const Block &rhs) {
  lhs.blocks.push_back(rhs);
  return lhs;
}

MultiBlock &operator<<(MultiBlock &lhs, const Line &rhs) {
  Block tmp(lhs.indent);
  tmp << rhs;
  lhs << tmp;
  return lhs;
}

std::string MultiBlock::str() const {
  std::stringstream ret;
  for (const auto &b: blocks) {
    ret << b.str();
  }
  return ret.str();
}

}
}