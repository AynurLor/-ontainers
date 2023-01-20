#ifndef SRC_S21_TREE_ITERATOR_H_
#define SRC_S21_TREE_ITERATOR_H_

#include <cstddef>
#include <iostream>
#include <memory>

#include "s21_compare.hpp"
#include "s21_node_tree.hpp"

namespace s21 {
template <class Key, class Compare = s21::Compare<Key>>
class ConstTreeIterator {
  using cmp_type = Compare;
  using node_p = NodeTree<Key, cmp_type> *;
  using node_t = NodeTree<Key, cmp_type>;
  using iterator = ConstTreeIterator<Key, cmp_type>;

 protected:
  node_p pointer_;
  cmp_type comp_;

 public:
  ConstTreeIterator() : pointer_(nullptr) {}
  explicit ConstTreeIterator(node_p NodeTree) : pointer_(NodeTree) {}
  ConstTreeIterator(ConstTreeIterator &other) : ConstTreeIterator() {
    pointer_ = other.pointer_;
  }
  ConstTreeIterator(ConstTreeIterator &&other) noexcept : ConstTreeIterator() {
    pointer_ = other.pointer_;
    other.pointer_ = nullptr;
  }
  ~ConstTreeIterator() = default;

  iterator operator++(int) {
    iterator tmp(*this);
    node_p nill = pointer_->get_nill();
    node_p last_node = pointer_->get_max();
    if (pointer_ == nill) {
    } else if (pointer_ == last_node) {
      pointer_ = nill;
    } else if (pointer_->right_ != nill) {
      if (pointer_->right_->left_ != nill) {
        pointer_ = pointer_->right_->left_;
        while (pointer_->left_ != nill) {
          pointer_ = pointer_->left_;
        }
      } else {
        pointer_ = pointer_->right_;
      }
    } else if (pointer_->right_ == nill || pointer_->left_ == nill) {
      if (pointer_->parent_->key_ <= pointer_->key_) {
        Key remember_key = pointer_->key_;
        while (pointer_->parent_->key_ <= remember_key) {
          pointer_ = pointer_->parent_;
        }
        pointer_ = pointer_->parent_;
      } else {
        pointer_ = pointer_->parent_;
      }
    }
    return tmp;
  }

  iterator operator++() {
    node_p nill = pointer_->get_nill();
    node_p last_node = pointer_->get_max();
    if (pointer_ == nill) {
    } else if (pointer_ == last_node) {
      pointer_ = nill;
    } else if (pointer_->right_ != nill) {
      if (pointer_->right_->left_ != nill) {
        pointer_ = pointer_->right_->left_;
        while (pointer_->left_ != nill) {
          pointer_ = pointer_->left_;
        }
      } else {
        pointer_ = pointer_->right_;
      }
    } else if (pointer_->right_ == nill || pointer_->left_ == nill) {
      if (pointer_->parent_->key_ <= pointer_->key_) {
        Key remember_key = pointer_->key_;
        while (pointer_->parent_->key_ <= remember_key) {
          pointer_ = pointer_->parent_;
        }
        pointer_ = pointer_->parent_;
      } else {
        pointer_ = pointer_->parent_;
      }
    }
    return pointer_;
  }

  node_p get_pointer() { return pointer_; }

  bool operator!=(const iterator &it) {
    return (this->pointer_ != it.pointer_);
  }

  void operator=(iterator &other) { this->pointer_ = other.pointer_; }

  void operator=(iterator &&other) {
    this->pointer_ = other.pointer_;
    other.pointer_ = nullptr;
  }

  const Key operator*() { return pointer_->key_; }

  bool operator==(iterator &other) {
    return (this->pointer_ == other.pointer_);
  }
};  // ConstTreeIterator

template <class Key, class Compare = s21::Compare<Key>>
class TreeIterator {
  using cmp_type = Compare;
  using node_p = NodeTree<Key, cmp_type> *;
  using node_t = NodeTree<Key, cmp_type>;
  using iterator = TreeIterator<Key, cmp_type>;

 protected:
  node_p pointer_;
  cmp_type cmp_;

 public:
  TreeIterator() : pointer_(nullptr) {}
  explicit TreeIterator(node_p NodeTree) : pointer_(NodeTree) {}
  TreeIterator(iterator &other) : iterator() { pointer_ = other.pointer_; }
  TreeIterator(iterator &&other) noexcept : iterator() {
    pointer_ = other.pointer_;
  }
  ~TreeIterator() = default;

  iterator operator++(int) {
    iterator tmp(*this);
    node_p nill = pointer_->get_nill();
    node_p last_node = pointer_->get_max();
    if (pointer_ == nill) {
    } else if (pointer_ == last_node) {
      pointer_ = nill;
    } else if (pointer_->right_ != nill) {
      if (pointer_->right_->left_ != nill) {
        pointer_ = pointer_->right_->left_;
        while (pointer_->left_ != nill) {
          pointer_ = pointer_->left_;
        }
      } else {
        pointer_ = pointer_->right_;
      }
    } else if (pointer_->right_ == nill || pointer_->left_ == nill) {
      if (pointer_->parent_->key_ < pointer_->key_) {
        Key remember_key = pointer_->key_;
        while (pointer_->parent_->key_ < remember_key) {
          pointer_ = pointer_->parent_;
        }
        pointer_ = pointer_->parent_;
      } else {
        pointer_ = pointer_->parent_;
      }
    }
    return tmp;
  }

  iterator operator++() {
    iterator tmp(*this);
    node_p nill = pointer_->get_nill();
    node_p last_node = pointer_->get_max();
    if (pointer_ == nill) {
    } else if (pointer_ == last_node) {
      pointer_ = nill;
    } else if (pointer_->right_ != nill) {
      if (pointer_->right_->left_ != nill) {
        pointer_ = pointer_->right_->left_;
        while (pointer_->left_ != nill) {
          pointer_ = pointer_->left_;
        }
      } else {
        pointer_ = pointer_->right_;
      }
    } else if (pointer_->right_ == nill || pointer_->left_ == nill) {
      if (pointer_->parent_->key_ < pointer_->key_) {
        Key remember_key = pointer_->key_;
        while (pointer_->parent_->key_ < remember_key) {
          pointer_ = pointer_->parent_;
        }
        pointer_ = pointer_->parent_;
      } else {
        pointer_ = pointer_->parent_;
      }
    }
    return tmp;
  }

  node_p get_pointer() { return pointer_; }

  bool operator!=(const iterator &it) {
    return (this->pointer_ != it.pointer_);
  }

  void operator=(iterator &other) { this->pointer_ = other.pointer_; }

  void operator=(iterator &&other) {
    this->pointer_ = other.pointer_;
    other.pointer_ = nullptr;
  }

  const Key operator*() { return pointer_->key_; }

  bool operator==(iterator &other) {
    return (this->pointer_ == other.pointer_);
  }
};  // TreeIterator
}  // namespace s21

#endif  // SRC_S21_TREE_ITERATOR.H