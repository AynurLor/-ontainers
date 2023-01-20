#ifndef SRC_STACK_S21_STACK_H
#define SRC_STACK_S21_STACK_H

#include <initializer_list>
#include <iostream>

#include "../List/s21_list.hpp"

namespace s21 {
template <class T, class Container = s21::List<T>>
class Stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using container_type = Container;

 private:
  container_type _container;

 public:
  /*=========================================================*/
  /*                                                         */
  /*                  STACK MEMBER FUNCTIONS                 */
  /*                                                         */
  /*=========================================================*/

  Stack(const container_type &container = container_type())
      : _container(container) {}
  Stack(std::initializer_list<value_type> const &items) : _container(items) {}
  Stack(const Stack &other) : _container(other) {}
  Stack(Stack &&other) : _container(std::move(other)) {}
  ~Stack() {}

  Stack &operator=(const Stack &other) {
    _container = other._container;
    return *this;
  }
  Stack &operator=(Stack &&other) {
    _container = std::move(other._container);
    return *this;
  }

  /*=========================================================*/
  /*                                                         */
  /*                   STACK ELEMENT ACCESS                  */
  /*                                                         */
  /*=========================================================*/

  reference top() { return _container.back(); }
  const_reference top() const { return _container.back(); }

  /*=========================================================*/
  /*                                                         */
  /*                      STACK CAPACITY                     */
  /*                                                         */
  /*=========================================================*/

  bool empty() const { return _container.empty(); }
  size_type size() const { return _container.size(); }

  /*=========================================================*/
  /*                                                         */
  /*                      STACK MODIFIERS                    */
  /*                                                         */
  /*=========================================================*/

  void push(const_reference value) { _container.push_back(value); }
  void push(value_type &&value) { _container.push_back(std::move(value)); }
  void pop() { _container.pop_back(); }
  void swap(Stack &other) { _container.swap(other._container); }

  /*=========================================================*/
  /*                                                         */
  /*                      STACK MODIFIERS                    */
  /*                                                         */
  /*=========================================================*/

  template <class... Args>
  void emplace_front(Args &&...args) {
    _container.emplace_front(std::forward<Args>(args)...);
  }
};
}  // namespace s21

#endif  // !SRC_STACK_S21_STACK_H