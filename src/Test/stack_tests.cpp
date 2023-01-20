#include <Stack>

#include "../Stack/s21_stack.hpp"
#include "gtest/gtest.h"

TEST(tests_of_stack, push_1) {
  s21::Stack<int> Mystack_1;
  Mystack_1.push(1);
  Mystack_1.push(2);
  Mystack_1.push(3);

  int i = 3;
  size_t size = 0;
  while (size < Mystack_1.size()) {
    ASSERT_EQ(i, Mystack_1.top());
    i--;
    size++;
    Mystack_1.pop();
  }
}
TEST(tests_of_stack, pop_1) {
  s21::Stack<int> Mystack_1;
  Mystack_1.push(1);
  Mystack_1.push(2);
  Mystack_1.push(3);

  Mystack_1.pop();
  Mystack_1.pop();
  Mystack_1.pop();

  bool empty_stack = Mystack_1.empty();
  ASSERT_EQ(1, empty_stack);
}

TEST(tests_of_stack, top) {
  s21::Stack<int> Mystack_1;
  Mystack_1.push(1);
  Mystack_1.push(2);
  Mystack_1.push(3);
  auto it = Mystack_1.top();
  ASSERT_EQ(3, it);
}

TEST(tests_of_stack, top_2) {
  s21::Stack<int> Mystack_1;
  Mystack_1.push(1);
  Mystack_1.push(2);
  Mystack_1.pop();
  Mystack_1.pop();

  Mystack_1.top();
}

TEST(tests_of_stack, size_1) {
  s21::Stack<int> Mystack_1;
  Mystack_1.push(1);
  Mystack_1.push(2);
  Mystack_1.push(3);
  auto it = Mystack_1.size();
  ASSERT_EQ(3, it);
}
TEST(tests_of_stack, size_2) {
  s21::Stack<int> Mystack_1;
  auto it = Mystack_1.size();
  ASSERT_EQ(0, it);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
