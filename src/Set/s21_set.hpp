#ifndef SRC_S21_SET_H_
#define SRC_S21_SET_H_

#include <cstddef>
#include <iostream>
#include <memory>
#include <vector>

#include "s21_compare.hpp"
#include "s21_node_tree.hpp"
#include "s21_tree_iterator.hpp"

using namespace std;

namespace s21 {
template <class Key, class Compare = s21::Compare<Key>>
class Set {
 public:
  using key_type = Key;
  using value_type = Key;
  using cmp_type = Compare;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = TreeIterator<Key, cmp_type>;
  using const_iterator = ConstTreeIterator<Key, cmp_type>;
  using size_type = size_t;
  using node_p = NodeTree<Key, cmp_type> *;
  using node_t = NodeTree<Key, cmp_type>;
  using allocator = std::allocator<key_type>;

 protected:
  cmp_type comp_;
  node_p root_;
  node_p nill_ = new node_t();
  size_type size_;
  allocator alloc_;

 public:
  /*=========================================================*/
  /*                                                         */
  /*                   SET MEMBER FUNCTIONS                  */
  /*                                                         */
  /*=========================================================*/

  Set() : root_(nullptr), size_(0) {}
  Set(std::initializer_list<key_type> const &items) : Set() {
    for (auto i = items.begin(); i != items.end(); i++) InsertIthem(*i);
    size_ = items.size();
  }
  Set(const Set &s) : Set() {
    this->set_copy(s.root_);
    this->size_ = s.size_;
  }

  Set(Set &&s) : Set() {
    if (this != s) {
      delete this->nill_;
      this->root_ = s.root_;
      this->nill_ = s.nill_;
      this->size_ = s.size_;
      s.root_ = nullptr;
      s.nill_ = nullptr;
      s.size_ = 0;
    }
  }

  ~Set() {
    clear();
    delete this->nill_;
  }

  void operator=(Set &&s) {
    this->clear();
    set_copy(s.root_);
    s.clear();
  }

  /*=========================================================*/
  /*                                                         */
  /*                       SET ITERATORS                     */
  /*                                                         */
  /*=========================================================*/

  iterator begin() {
    node_p begin_node = root_;
    if (size_ != 0) {
      while (begin_node->left_ != nill_) {
        begin_node = begin_node->left_;
        while (begin_node->right_ != nill_ &&
               comp_.eq(begin_node->right_->key_, begin_node->key_))
          begin_node = begin_node->right_;
      }
    } else {
      begin_node = nill_;
    }
    return iterator(begin_node);
  }

  const_iterator cbegin() {
    node_p begin_node = root_;
    if (size_ != 0) {
      while (begin_node->left_ != nill_) {
        begin_node = begin_node->left_;
        while (begin_node->right_ != nill_ &&
               comp_.eq(begin_node->right_->key_, begin_node->key_))
          begin_node = begin_node->right_;
      }
    } else {
      begin_node = nill_;
    }
    return const_iterator(begin_node);
  }

  const_iterator cend() { return const_iterator(nill_); }
  iterator end() { return iterator(nill_); }

  /*=========================================================*/
  /*                                                         */
  /*                       SET CAPACITY                      */
  /*                                                         */
  /*=========================================================*/

  bool empty() { return (size_ == 0); }
  size_type size() { return size_; }
  size_type max_size() { return alloc_.max_size() / 5; }

  /*=========================================================*/
  /*                                                         */
  /*                       SET MODIFIERS                     */
  /*                                                         */
  /*=========================================================*/

  void clear() {
    root_->clear_node();
    root_ = nullptr;
    size_ = 0;
  }

  std::pair<iterator, bool> insert(const value_type &value) {
    std::pair<node_p, bool> my_pair = InsertIthem(value);
    return {iterator(my_pair.first), my_pair.second};
  }

  void erase(iterator pos) {
    node_p base = pos.get_pointer();
    if (base == root_) {
      erase_root(base);
    } else {
      rebuild_set(base, nill_);
    }
    delete base;
    this->size_ -= 1;
  }

  void swap(Set &other) {
    node_p tmp_root = this->root_;
    node_p tmp_nill = this->nill_;
    size_t tmp_size = this->size_;

    this->root_ = other.root_;
    this->nill_ = other.nill_;
    this->size_ = other.size_;

    other.root_ = tmp_root;
    other.nill_ = tmp_nill;
    other.size_ = tmp_size;

    tmp_root->clear_node();
    tmp_nill->clear_node();
  }

  void merge(Set &other) {
    if (other.size_ > 0) {
      size_t remember_size = this->size_;
      merge_node(other.root_, other.nill_);
      other.size_ += (remember_size - this->size_);
    }
  }

  /*=========================================================*/
  /*                                                         */
  /*                        SET LOOKUP                       */
  /*                                                         */
  /*=========================================================*/

  iterator find(const Key &key) {
    iterator i = this->begin();
    for (auto it = i; it != end(); ++it) {
      if (comp_.eq(*it, key)) {
        i = it;
        break;
      } else {
        i = this->end();
      }
    }
    return i;
  }

  bool contains(const Key &key) {
    bool res = false;
    for (auto it : *this) {
      if (it == key) {
        res = true;
      }
    }
    return res;
  }

  template <class... Args>
  vector<std::pair<iterator, bool>> emplace(Args &&...args) {
    std::vector<std::pair<iterator, bool>> res;
    std::vector<typename Set<key_type, Compare>::value_type> argsVector = {
        args...};
    for (auto &i : argsVector) {
      res.push_back(insert(i));
    }
    return res;
  }

  node_p get_nill() { return nill_; }

  void set_copy(node_p other) {
    this->InsertIthem(other->key_);
    if (other->left_ != other->get_nill()) this->set_copy(other->left_);
    if (other->right_ != other->get_nill()) this->set_copy(other->right_);
  }

 private:
  std::pair<node_p, bool> InsertIthem(const key_type &NewKey) {
    std::pair<node_p, bool> pair_res = {nullptr, true};
    auto NewNode = new node_t(NewKey, nullptr, nill_, nill_);
    this->size_ += 1;
    if (this->root_ == nullptr) {
      (this->root_) = NewNode;
      pair_res = {(this->root_), true};
    } else {
      pair_res = this->insertIthem_(root_, NewNode);
    }
    return pair_res;
  }

  std::pair<node_p, bool> add_node(node_p &currentNode, node_p &newNode) {
    std::pair<node_p, bool> pair_res;
    if (currentNode == nill_) {
      currentNode = newNode;
      pair_res = {currentNode, true};
    } else {
      pair_res = this->insertIthem_(currentNode, newNode);
    }
    return pair_res;
  }

  std::pair<node_p, bool> insertIthem_(node_p currentNode, node_p newNode) {
    std::pair<node_p, bool> pair_res = {nullptr, true};
    newNode->parent_ = currentNode;
    if (comp_.less_then(newNode->key_, currentNode->key_)) {
      pair_res = add_node(currentNode->left_, newNode);
    } else if (comp_.grater_then(newNode->key_, currentNode->key_)) {
      pair_res = add_node(currentNode->right_, newNode);
    } else {
      pair_res = {currentNode, false};
    }
    return pair_res;
  }

  void erase_root(node_p &base) {
    if (base->right_ != nill_) {
      root_ = base->right_;
      base->right_->parent_ = nullptr;
    }
    if (base->left_ != nill_) {
      node_p leftest_el = base->right_;
      while (leftest_el->left_ != nill_) {
        leftest_el = leftest_el->left_;
      }
      leftest_el->left_ = base->left_;
      base->left_->parent_ = leftest_el;
    }
  }

  void past_to_rightest_elem(node_p &base, node_p &nill_) {
    if (base->left_->right_ != nill_) {
      node_p rightest_el = base->left_->right_;
      while (rightest_el->right_ != nill_) {
        rightest_el = rightest_el->right_;
      }
      rightest_el->right_ = base->right_;
    } else if (base->right_ != nill_) {
      base->left_->right_ = base->right_;
    }
  }

  void rebuild_set(node_p base, node_p nill_) {
    if (base->right_ == nill_ && base->left_ == nill_) {
      (base == base->parent_->left_) ? base->parent_->left_ = nill_
                                     : base->parent_->right_ = nill_;
    }
    if (base == base->parent_->left_) {
      if (base->left_ != nill_) {
        base->parent_->left_ = base->left_;
        base->left_->parent_ = base->parent_;
        past_to_rightest_elem(base, nill_);
      } else {
        base->parent_->left_ = base->right_;
        base->right_->parent_ = base->parent_;
      }
    } else if (base == base->parent_->right_) {
      if (base->right_ != nill_) {
        base->parent_->right_ = base->right_;
        base->right_->parent_ = base->parent_;
        if (base->left_ != nill_) {
          past_to_rightest_elem(base, nill_);
        }
      } else {
        base->parent_->right_ = base->left_;
        base->left_->parent_ = base->parent_;
      }
    }
  }

  void pop_node(node_p &base, const node_p &nill) {
    if (base->left_ == nill && base->right_ == nill) {
      base == base->parent_->left_ ? base->parent_->left_ = nill
                                   : base->parent_->right_ = nill;
    } else {
      rebuild_set(base, nill);
    }
    base->left_ = base->right_ = nill_;
  }

  void insert_merge(node_p base, const node_p &nill) {
    int flag = 0;
    for (auto it : *this) {
      if (comp_.eq(it, base->key_)) {
        flag = 1;
      }
    }
    if (flag == 0) {
      pop_node(base, nill);
      this->size_ += 1;
      if (this->root_ == nullptr) {
        (this->root_) = base;
      } else {
        this->insertIthem_(root_, base);
      }
    }
  }

  void merge_node(node_p root_, const node_p &nill) {
    node_p base = root_;
    if (base->left_ != nill) {
      merge_node(base->left_, nill);
    }
    if (base->right_ != nill) {
      merge_node(base->right_, nill);
    }
    insert_merge(base, nill);
  }
};
}  // namespace s21
#endif  // SRC_S21_SET_H_