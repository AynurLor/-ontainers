#ifndef SRC_S21_COMPARE_H_
#define SRC_S21_COMPARE_H_

namespace s21 {
template <class Key>
struct Compare {
  bool less_then(const Key &x, const Key &y) const { return x < y; }
  bool grater_then(const Key &x, const Key &y) const { return x > y; }
  bool less_or_equal(const Key &x, const Key &y) const { return x <= y; }
  bool grater_or_equal(const Key &x, const Key &y) const { return x >= y; }
  bool eq(const Key &x, const Key &y) const { return x == y; }
  bool no_eq(const Key &x, const Key &y) const { return x != y; }
};
}  // namespace s21
#endif  // SRC_S21_COMPARE_H_
