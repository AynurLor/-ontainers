#include <gtest/gtest.h>

#include <queue>

#include "../Queue/s21_queue.hpp"

TEST(tests_of_Queue, push) {
  s21::Queue<int> MyQueue_1;
  MyQueue_1.push(2);
  MyQueue_1.push(3);
  MyQueue_1.push(4);
  std::queue<int> stdQueue;
  stdQueue.push(2);
  stdQueue.push(3);
  stdQueue.push(4);

  EXPECT_EQ(MyQueue_1.front(), stdQueue.front());
  EXPECT_EQ(MyQueue_1.back(), stdQueue.back());
  MyQueue_1.pop();
  stdQueue.pop();
  EXPECT_EQ(MyQueue_1.back(), stdQueue.back());

  s21::Queue<int> MyQueue_2 = {1, 2};
  s21::Queue<int> MyQueue_4;
  MyQueue_4 = MyQueue_2;
  EXPECT_EQ(MyQueue_4.front(), 1);
  EXPECT_EQ(MyQueue_4.back(), 2);

  auto MyQueue_3 = std::move(MyQueue_1);
}

TEST(tests_of_Queue, pop_1) {
  s21::Queue<int> MyQueue_1;
  MyQueue_1.push(1);
  MyQueue_1.push(2);
  MyQueue_1.push(3);

  MyQueue_1.pop();
  MyQueue_1.pop();
  MyQueue_1.pop();

  bool empty_Queue = MyQueue_1.empty();
  EXPECT_EQ(1, empty_Queue);
}

TEST(tests_of_Queue, size_1) {
  s21::Queue<int> MyQueue_1;
  MyQueue_1.push(1);
  MyQueue_1.push(2);
  MyQueue_1.push(3);
  auto it = MyQueue_1.size();
  EXPECT_EQ(3, it);
}

TEST(tests_of_Queue, size_2) {
  s21::Queue<int> MyQueue_1;
  auto it = MyQueue_1.size();
  EXPECT_EQ(0, it);
}

TEST(tests_of_Queue, emplace) {
  s21::Queue<int> Queue_1 = {2, 4};
  Queue_1.emplace_back(2);
  EXPECT_EQ(Queue_1.back(), 2);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
