#ifndef SRC_QUEUE_S21_QUEUE_H
#define SRC_QUEUE_S21_QUEUE_H

#include <iostream>
#include <list>

namespace s21 {
template <class T, class Container = std::list<T>>
class Queue {
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
  /*                  QUEUE MEMBER FUNCTIONS                 */
  /*                                                         */
  /*=========================================================*/
  Queue(const container_type &container = container_type())
      : _container(container) {}
  Queue(std::initializer_list<value_type> const &items) : _container(items) {}
  Queue(const Queue &other) : _container(other._container) {}
  Queue(Queue &&other) : _container(std::move(other._container)) {}
  ~Queue() {}

  Queue &operator=(const Queue &other) {
    _container = other._container;
    return *this;
  }
  Queue &operator=(Queue &&other) {
    _container = std::move(other._container);
    return *this;
  }

  /*=========================================================*/
  /*                                                         */
  /*                   QUEUE ELEMENT ACCESS                  */
  /*                                                         */
  /*=========================================================*/

  reference front() { return _container.front(); }
  const_reference front() const { return _container.front(); }
  reference back() { return _container.back(); }
  const_reference back() const { _container.back(); }

  /*=========================================================*/
  /*                                                         */
  /*                      QUEUE CAPACITY                     */
  /*                                                         */
  /*=========================================================*/

  bool empty() const { return _container.empty(); }
  size_type size() const { return _container.size(); }

  /*=========================================================*/
  /*                                                         */
  /*                      QUEUE MODIFIERS                    */
  /*                                                         */
  /*=========================================================*/

  void push(const_reference value) { _container.push_back(value); }
  void push(value_type &&value) { _container.push_back(std::move(value)); }
  void pop() { _container.pop_front(); }
  void swap(Queue &other) { _container.swap(other._container); }

  /*=========================================================*/
  /*                                                         */
  /*                      QUEUE MODIFIERS                    */
  /*                                                         */
  /*=========================================================*/

  template <class... Args>
  void emplace_back(Args &&...args) {
    _container.emplace_back(std::forward<Args>(args)...);
  }
};
}  // namespace s21

#endif  // !SRC_QUEUE_S21_QUEUE_H