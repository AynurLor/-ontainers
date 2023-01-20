#ifndef SRC_S21_ARRAY_H
#define SRC_S21_ARRAY_H

#include <initializer_list>
#include <iostream>

namespace s21 {
template <class T, size_t N>
class Array {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

 private:
  size_type size_;
  value_type array_[N];

 public:
  /*=========================================================*/
  /*                                                         */
  /*                  ARRAT MEMBER FUNCTIONS                 */
  /*                                                         */
  /*=========================================================*/
  Array() : size_(N) {}
  Array(std::initializer_list<value_type> const &items) : size_(N) {
    if (size_ < items.size()) throw std::out_of_range("Too many initializers");
    for (auto i = 0, it = items.begin(); (std::size_t)i < items.size();
         i++, it++)
      array_[i] = *it;
  }
  Array(const Array &other) : size_(other.size_) {
    std::copy(other.cbegin(), other.cend(), array_);
  }
  Array(Array &&other) : size_(other.size_) {
    std::move(other.cbegin(), other.cend(), array_);
    other.size_ = 0;
  }
  ~Array() {}

  void operator=(Array &&other) {
    size_ = other.size_;
    std::move(other.cbegin(), other.cend(), array_);
    other.size_ = 0;
  }
  void operator=(Array &other) {
    size_ = other.size_;
    std::copy(other.cbegin(), other.cend(), array_);
  }

  /*=========================================================*/
  /*                                                         */
  /*                   ARRAY ELEMENT ACCESS                  */
  /*                                                         */
  /*=========================================================*/
  reference at(size_type pos) {
    if (pos >= size_) throw std::runtime_error("Index is not correct");
    return array_[pos];
  }
  reference operator[](size_type pos) { return array_[pos]; }
  const_reference front() { return array_[0]; }
  const_reference back() { return array_[size_ - 1]; }
  iterator data() { return array_; }

  /*=========================================================*/
  /*                                                         */
  /*                      ARRAY ITERATORS                    */
  /*                                                         */
  /*=========================================================*/
  iterator begin() { return &array_[0]; }
  iterator end() { return &array_[size_]; }
  const_iterator cbegin() const { return &array_[0]; }
  const_iterator cend() const { return &array_[size_]; }

  /*=========================================================*/
  /*                                                         */
  /*                       ARRAY CAPACITY                    */
  /*                                                         */
  /*=========================================================*/
  bool empty() {
    if (size_ == 0) return true;
    return false;
  }
  size_type size() { return size_; }
  size_type max_size() { return size_; }

  /*=========================================================*/
  /*                                                         */
  /*                      ARRAY MODIFIERS                    */
  /*                                                         */
  /*=========================================================*/
  void swap(Array &other) {
    s21::Array<value_type, N> helper(*this);
    helper = *this;
    *this = other;
    other = helper;
  }
  void fill(const_reference value) {
    for (auto i = 0; i < (int)size_; i++) array_[i] = value;
  }
};
}  // namespace s21

#endif  // !SRC_S21_ARRAY_H