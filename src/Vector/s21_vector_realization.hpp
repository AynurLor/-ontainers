#ifndef SRC_VECTOR_S21_VECTOR_REALIZATION_H
#define SRC_VECTOR_S21_VECTOR_REALIZATION_H

#include "s21_vector.hpp"

namespace s21 {
/*=========================================================*/
/*                                                         */
/*                    VECTOR REALIZATION                   */
/*                                                         */
/*=========================================================*/

template <typename T, typename A>
Vector<T, A>::Vector(size_type size, const T &value, const A &allocator)
    : allocator_(allocator) {
  data_ = allocate_memory(size, size, value, allocator_);
  size_ = capacity_ = size;
}

template <typename T, typename A>
Vector<T, A>::Vector(const Vector &other) {
  data_ =
      allocate_memory(other.size_, other.capacity_, other.data_, allocator_);
  size_ = other.size_;
  capacity_ = other.capacity_;
}

template <typename T, typename A>
Vector<T, A>::Vector(Vector &&other)
    : size_(other.size_),
      capacity_(other.capacity_),
      data_(other.data_),
      allocator_(other.allocator_) {
  other.size_ = 0;
  other.capacity_ = 0;
  other.data_ = nullptr;
  other.allocator_ = A();
  /* Хер знает почему но приватная функция swap_ выдает сегу */
}

template <typename T, typename A>
Vector<T, A>::Vector(std::initializer_list<value_type> const &items, const A &a)
    : size_(items.size()), capacity_(size_), allocator_(a) {
  data_ = allocate_memory(size_, size_, *items.begin(), allocator_);
  size_type i = 0;
  iterator p;
  try {
    iterator end = data_ + size_;
    for (p = data_; p != end; ++p) {
      traits::construct(allocator_, p, *(items.begin() + i++));
    }
  } catch (...) {
    for (iterator q = data_; q != p; ++q) {
      traits::destroy(allocator_, q);
    }
    traits::deallocate(allocator_, data_, capacity_);
  }
}

template <typename T, typename A>
Vector<T, A>::~Vector() {
  deallocate_memory(size_, capacity_, data_, allocator_);
  size_ = capacity_ = 0;
}

template <typename T, typename A>
Vector<T, A> &Vector<T, A>::operator=(const Vector &other) {
  if (this == &other) {
    return *this;
  }

  A tmp_allocator = other.allocator_;
  value_type *newarr = allocate_memory(other.size(), other.capacity(),
                                       other.data_, tmp_allocator);
  deallocate_memory(size_, capacity_, data_, allocator_);

  data_ = newarr;
  size_ = other.size();
  capacity_ = other.capacity();
  allocator_ = std::move(tmp_allocator);
  return *this;
}

template <typename T, typename A>
Vector<T, A> &Vector<T, A>::operator=(Vector &&other) {
  if (this == &other) {
    return *this;
  }

  deallocate_memory(size_, capacity_, data_, allocator_);
  swap_(*this, other);
  allocator_ = std::move(other.allocator_);
  return *this;
}

template <typename T, typename A>
T &Vector<T, A>::at(size_type pos) {
  if (!(pos < size())) {
    throw std::out_of_range("Index is out of range of vector");
  }
  return data_[pos];
}

template <typename T, typename A>
const T &Vector<T, A>::at(size_type pos) const {
  if (!(pos < size())) {
    throw std::out_of_range("Index is out of range of vector");
  }
  return data_[pos];
}

template <typename T, typename A>
void Vector<T, A>::reserve(size_type size) {
  if (size < capacity_) {
    return;
  }
  Vector<T, A> tmp_copy(*this);
  deallocate_memory(size_, capacity_, data_, allocator_);
  data_ = allocate_memory(size_, size, tmp_copy.data_, allocator_);
  capacity_ = size;
}

template <typename T, typename A>
void Vector<T, A>::shrink_to_fit() {
  if (size_ == capacity_) {
    return;
  }
  value_type *buffer = data_;
  deallocate_memory(size_, capacity_, data_, allocator_);
  data_ = allocate_memory(size_, size_, buffer, allocator_);
  capacity_ = size_;
}

template <typename T, typename A>
void Vector<T, A>::clear() noexcept {
  if (capacity_ != 0u) {
    for (iterator p = data_; p != data_ + size_; ++p) {
      traits::destroy(allocator_, p);
    }
    size_ = 0;
  }
}

template <typename T, typename A>
void Vector<T, A>::push_back(const_reference value) {
  if (size_ == capacity_) {
    capacity_ == 0u ? capacity_ = 1u : capacity_;
    reserve(capacity_ * 2u);
  }
  traits::construct(allocator_, end(), value);
  size_++;
}

template <typename T, typename A>
void Vector<T, A>::push_back(value_type &&value) {
  if (size_ == capacity_) {
    capacity_ == 0u ? capacity_ = 1u : capacity_;
    reserve(capacity_ * 2u);
  }
  traits::construct(allocator_, end(), value);
  size_++;
}

template <typename T, typename A>
T *Vector<T, A>::insert(iterator pos, const_reference value) {
  iterator position = pos;
  if (pos == end()) {
    push_back(value);
  } else if (pos > end()) {
    position = nullptr;
  } else {
    value_type *buffer =
        allocate_memory(size_, capacity_ + 1u, data_[0], allocator_);
    iterator p;
    size_type i = 0u;
    for (p = begin(); p != end(); ++p) {
      if (p == pos) {
        traits::construct(allocator_, buffer + i, value);
        position = buffer + i;
        i++;
      }
      traits::construct(allocator_, buffer + i, *p);
      i++;
    }
    deallocate_memory(size_, capacity_, data_, allocator_);
    data_ = buffer;
    size_ += 1u;
    if (size_ == capacity_) {
      reserve(capacity_ * 2);
    }
  }
  return position;
}

template <typename T, typename A>
void Vector<T, A>::erase(iterator pos) {
  if (pos >= end()) {
    throw std::out_of_range("pos is out of range");
    return;
  }
  value_type *buffer =
      allocate_memory(size_ - 1, capacity_, data_[0], allocator_);
  iterator p;
  size_type i = 0;
  for (p = data_; p != end(); ++p) {
    if (p != pos) {
      traits::construct(allocator_, buffer + i, *p);
      i++;
    }
  }
  deallocate_memory(size_, capacity_, data_, allocator_);
  data_ = buffer;
  size_ -= 1u;
}

template <typename T, typename A>
void Vector<T, A>::pop_back() {
  traits::destroy(allocator_, end() - 1u);
  size_--;
}

template <typename T, typename A>
void Vector<T, A>::swap(Vector &other) {
  swap_(*this, other);
  std::swap(allocator_, other.allocator_);
}

template <typename T, typename A>
void Vector<T, A>::resize(size_type count) {
  if (count > capacity_) reserve(count);
  if (size_ > count) {
    while (size_ != count) pop_back();
  }
  while (size_ < count) {
    traits::construct(allocator_, data_ + size_);
    size_++;
  }
}

template <typename T, typename A>
void Vector<T, A>::resize(size_type count, const_reference value) {
  if (count > capacity_) reserve(count);
  if (size_ > count) {
    while (size_ != count) pop_back();
  }
  while (size_ < count) {
    traits::construct(allocator_, data_ + size_, value);
    size_++;
  }
}

/*=========================================================*/
/*                                                         */
/*               VECTOR PRIVATE REALIZATION                */
/*                                                         */
/*=========================================================*/

template <typename T, typename A>
T *Vector<T, A>::allocate_memory(size_type size, size_type capacity,
                                 const T &value, A &a) {
  value_type *newarr = traits::allocate(a, capacity);
  iterator p;
  try {
    iterator end = newarr + size;
    for (p = newarr; p != end; ++p) {
      traits::construct(a, p, value);
    }
  } catch (...) {
    for (iterator q = newarr; q != p; ++q) {
      traits::destroy(a, q);
    }
    traits::deallocate(a, newarr, capacity);
    throw;
  }
  return newarr;
}

template <typename T, typename A>
T *Vector<T, A>::allocate_memory(size_type size, size_type capacity,
                                 const_pointer arr, A &a) {
  value_type *newarr = traits::allocate(a, capacity);
  iterator p;
  try {
    size_type i = 0;
    iterator end = newarr + size;
    for (p = newarr; p != end; ++p) {
      traits::construct(a, p, arr[i++]);
    }
  } catch (...) {
    for (iterator q = newarr; q != p; ++q) {
      traits::destroy(a, q);
    }
    traits::deallocate(a, newarr, capacity);
    throw;
  }
  return newarr;
}

template <typename T, typename Alloc>
template <class... Args>
typename Vector<T, Alloc>::iterator Vector<T, Alloc>::emplace(
    const_iterator pos, Args &&...args) {
  if (pos = cend()) {
    return emplace_back((args)...);
  }

  capacity_ == 0 ? capacity_ = 1 : capacity_;
  reserve(capacity_ * 2);

  Vector<T, Alloc>::iterator it_res;
  Vector<T, Alloc>::const_iterator it = cbegin();

  for (; it != pos; ++it) {
  }
}

template <typename T, typename A>
void Vector<T, A>::deallocate_memory(size_type size, size_type capacity,
                                     pointer arr, A &a) {
  if (arr != nullptr) {
    for (iterator p = arr; p != arr + size; ++p) {
      traits::destroy(a, p);
    }
    traits::deallocate(a, arr, capacity);
  }
}

template <typename T, typename Alloc>
template <class... Args>
typename Vector<T, Alloc>::reference Vector<T, Alloc>::emplace_back(
    Args &&...args) {
  if (size_ == capacity_) {
    capacity_ == 0 ? capacity_ = 1 : capacity_;
    reserve(capacity_ * 2);
  }

  traits::construct(allocator_, data_ + size_, std::forward<Args>(args)...);
  return data_[size_++];
}

template <typename T, typename A>
void Vector<T, A>::swap_(Vector &to, Vector &from) {
  std::swap(to.size_, from.size_);
  std::swap(to.capacity_, from.capacity_);
  std::swap(to.data_, from.data_);
}

}  // namespace s21

#endif  // !SRC_VECTOR_S21_VECTOR_REALIZATION_H
