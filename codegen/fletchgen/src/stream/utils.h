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

namespace fletchgen {
namespace stream {

class Named {
 public:
  explicit Named(std::string name)
      : name_(std::move(name)) {}
  std::string name() const { return name_; }
 private:
  std::string name_;
};

struct ClockDomain : public Named {
  explicit ClockDomain(std::string name)
      : Named(std::move(name)) {}

  static std::shared_ptr<ClockDomain> Make(std::string name) { return std::make_shared<ClockDomain>(name); }
};

}  // namespace stream
}  // namespace fletchgen