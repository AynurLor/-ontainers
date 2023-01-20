#ifndef SRC_S21_NODE_TREE_HPP_
#define SRC_S21_NODE_TREE_HPP_

#include "s21_compare.hpp"

namespace s21 {
template <class Key, class Compare = Compare<Key>>
class NodeTree {
 public:
  using key_type = Key;
  using cmp_type = Compare;
  cmp_type comp_;
  NodeTree *parent_;
  NodeTree *left_;
  NodeTree *right_;
  key_type key_;

 public:
  NodeTree() : parent_(nullptr), left_(), right_(nullptr) {}  // default
  NodeTree(key_type data, NodeTree *parent = nullptr, NodeTree *left = nullptr,
           NodeTree *right = nullptr)
      : key_(data), parent_(parent), left_(left), right_(right) {}
  NodeTree(const NodeTree &other) : NodeTree() {
    parent_ = other->parent_;
    left_ = other->left_;
    right_ = other->right_;
    key_ = other->key_;
  }
  NodeTree(NodeTree &&other) = default;
  void operator=(const NodeTree &other) {
    parent_ = other->parent_;
    left_ = other->left_;
    right_ = other->right_;
    key_ = other->key_;
  }
  ~NodeTree() {}

  NodeTree *get_nill() {
    NodeTree *tmp = this;
    while (tmp->parent_ != nullptr) {
      tmp = tmp->parent_;
    }
    while (tmp->right_ != nullptr) {
      tmp = tmp->right_;
    }
    return tmp;
  }

  NodeTree *get_max() {
    NodeTree *tmp = this;
    while (tmp->parent_ != nullptr) {
      tmp = tmp->parent_;
    }
    while (tmp->right_->right_ != nullptr) {
      tmp = tmp->right_;
    }
    return tmp;
  }

  NodeTree *get_min() {
    NodeTree *tmp = this;
    while (tmp->left_->left_ != nullptr) {
      tmp = tmp->left_;
    }
    return tmp;
  }

  void clear_node() {
    this->~NodeTree();
    if (this) {
      if (left_ != nullptr) left_->clear_node();
      if (right_ != nullptr) right_->clear_node();
    }
  }
};
}  // namespace s21

#endif  // SRC_S21_NODE_TREE_HPP_