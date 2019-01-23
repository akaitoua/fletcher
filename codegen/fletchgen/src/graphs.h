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
#include <memory>
#include <utility>
#include <deque>

#include "./nodes.h"

namespace fletchgen {

struct Graph : public Named {
  explicit Graph(std::string name) : Named(name) {}
  std::deque<std::shared_ptr<Node>> nodes;
  std::deque<std::shared_ptr<Graph>> children;

  /// @brief Get a node of a specific type with a specific name
  std::shared_ptr<Node> Get(Node::ID id, std::string name) const;

  /// @brief Add a node to the component
  Graph &Add(std::shared_ptr<Node> node);

  /// @brief Count nodes of a specific node type
  size_t CountNodes(Node::ID id) const;

  /// @brief Add a child component
  Graph &Add(const std::shared_ptr<Graph> &child);

  template<typename T>
  std::deque<std::shared_ptr<T>> GetAll() {
    std::deque<std::shared_ptr<T>> ret;
    for (const auto &n : nodes) {
      if (Cast<T>(n) != nullptr) {
        ret.push_back(Cast<T>(n));
      }
    }
    return ret;
  }
};

struct Component : public Graph {

  /// @brief Construct an empty Component
  explicit Component(std::string name) : Graph(std::move(name)) {}

  /// @brief Construct a Component with initial parameters and ports.
  static std::shared_ptr<Component> Make(std::string name,
                                         std::initializer_list<std::shared_ptr<Parameter>> parameters,
                                         std::initializer_list<std::shared_ptr<Port>> ports,
                                         std::initializer_list<std::shared_ptr<Signal>> signals);

  static std::shared_ptr<Component> Make(std::string name) { return Make(name, {}, {}, {}); }
};

struct Instance : public Graph {
  std::shared_ptr<Component> component;

  /// @brief Construct an instance of a component, copying over all its ports and parameters
  explicit Instance(std::string name, std::shared_ptr<Component> comp);

  /// @brief Construct a Component with initial parameters and ports.
  static std::shared_ptr<Instance> Make(std::string name, std::shared_ptr<Component> component);
};

template<typename T>
const std::shared_ptr<T> Cast(const std::shared_ptr<Graph> &obj) {
  return std::dynamic_pointer_cast<T>(obj);
}

}  // namespace fletchgen