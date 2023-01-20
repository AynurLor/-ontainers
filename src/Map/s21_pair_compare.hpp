#ifndef SRC_S21_PAIR_COMPARE_H_
#define SRC_S21_PAIR_COMPARE_H_
#include <utility>
namespace s21 {
template <class A, class B>
struct PairCompare {
 public:
  using pair = const std::pair<A, B>;

 public:
  bool less_then(pair &x, pair &y) const { return x.first < y.first; }
  bool grater_then(pair &x, pair &y) const { return x.first > y.first; }
  bool less_or_equal(pair &x, pair &y) const { return x.first <= y.first; }
  bool grater_or_equal(pair &x, pair &y) const { return x.first >= y.first; }
  bool eq(pair &x, pair &y) const { return x.first == y.first; }
  bool no_eq(pair &x, pair &y) const { return x.first != y.first; }
};
}  // namespace s21
#endif  // SRC_S21_PAIR_COMPARE_H_