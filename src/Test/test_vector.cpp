#include <gtest/gtest.h>

#include <vector>

#include "../s21_containers.hpp"

using namespace std;
using testing::InitGoogleTest;

TEST(vector_test, at1) {
  s21::Vector<int> vec1 = {1, 2, 3, 4, 5};
  std::vector<int> vec2 = {1, 2, 3, 4, 5};
  EXPECT_EQ(vec1.size(), vec2.size());
  EXPECT_EQ(vec1.capacity(), vec2.capacity());
}

TEST(vector_test, operator_brackets) {
  s21::Vector<int> vec1 = {1, 2, 3, 4, 5};
  std::vector<int> vec2 = {1, 2, 3, 4, 5};
  for (size_t i = 0; i < vec1.size(); i++) {
    EXPECT_EQ(vec1[i], vec2[i]);
  }
  EXPECT_EQ(vec1.size(), vec2.size());
  EXPECT_EQ(vec1.capacity(), vec2.capacity());
}

TEST(vector_test, front) {
  s21::Vector<int> vec1 = {1, 2, 3};
  std::vector<int> vec2 = {1, 2, 3};
  EXPECT_EQ(vec1.front(), vec2.front());
  EXPECT_EQ(vec1.size(), vec2.size());
  EXPECT_EQ(vec1.capacity(), vec2.capacity());
}

TEST(vector_test, back) {
  s21::Vector<int> vec1 = {1, 2, 3};
  std::vector<int> vec2 = {1, 2, 3};
  EXPECT_EQ(vec1.back(), vec2.back());
  EXPECT_EQ(vec1.size(), vec2.size());
  EXPECT_EQ(vec1.capacity(), vec2.capacity());
}

TEST(vector_test, data) {
  s21::Vector<int> vec1;
  EXPECT_EQ(vec1.data(), nullptr);
  s21::Vector<int> vec2 = {1, 2, 3};
  EXPECT_FALSE(vec2.data() == nullptr);
}

TEST(vector_test, begin) {
  s21::Vector<int> vec1 = {1, 2, 3, 4, 5};
  std::vector<int> vec2 = {1, 2, 3, 4, 5};
  auto iter1 = vec1.begin();
  auto iter2 = vec2.begin();
  EXPECT_EQ(*iter1, *iter2);
  EXPECT_EQ(vec1.size(), vec2.size());
  EXPECT_EQ(vec1.capacity(), vec2.capacity());
}

TEST(vector_test, end) {
  s21::Vector<int> vec1 = {1, 2, 3, 4, 5};
  std::vector<int> vec2 = {1, 2, 3, 4, 5};
  auto iter1 = vec1.end();
  auto iter2 = vec2.end();
  EXPECT_EQ(*(iter1 - 1), *(iter2 - 1));
  EXPECT_EQ(vec1.size(), vec2.size());
  EXPECT_EQ(vec1.capacity(), vec2.capacity());
}

TEST(vector_test, size) {
  s21::Vector<int> vec1;
  std::vector<int> vec2 = {1, 2, 3};
  EXPECT_EQ(vec1.size(), 0);
  vec1 = {1, 2, 3};
  EXPECT_EQ(vec1.size(), vec2.size());
  EXPECT_EQ(vec1.size(), vec2.size());
  EXPECT_EQ(vec1.capacity(), vec2.capacity());
}

TEST(vector_test, reserve) {
  s21::Vector<int> vec1 = {1, 2, 3};
  std::vector<int> vec2 = {1, 2, 3};
  vec1.reserve(100);
  vec2.reserve(100);
  EXPECT_EQ(vec1.size(), vec2.size());
  EXPECT_EQ(vec1.capacity(), vec2.capacity());
}

TEST(vector_test, capacity) {
  s21::Vector<int> vec1;
  std::vector<int> vec2;
  EXPECT_EQ(vec1.size(), vec2.size());
  EXPECT_EQ(vec1.capacity(), vec2.capacity());
  vec1 = {1, 2, 3};
  vec2 = {1, 2, 3};
  EXPECT_EQ(vec1.size(), vec2.size());
  EXPECT_EQ(vec1.capacity(), vec2.capacity());
}

TEST(vector_test, shrink_to_fit) {
  s21::Vector<int> vec1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<int> vec2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  vec1.push_back(11);
  vec2.push_back(11);
  EXPECT_EQ(vec1.size(), vec2.size());
  EXPECT_EQ(vec1.capacity(), vec2.capacity());
}

TEST(vector_test, clear) {
  s21::Vector<int> vec1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<int> vec2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  vec1.clear();
  vec2.clear();

  EXPECT_EQ(vec1.size(), vec2.size());
  EXPECT_EQ(vec1.capacity(), vec2.capacity());
}

TEST(vector_test, push_back) {
  s21::Vector<int> vec1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<int> vec2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  vec1.push_back(11);
  vec2.push_back(11);
  EXPECT_EQ(vec1[10], vec2[10]);
  EXPECT_EQ(vec1.size(), vec2.size());
  EXPECT_EQ(vec1.capacity(), vec2.capacity());
}

TEST(vector_test, pop_back) {
  s21::Vector<int> vec1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<int> vec2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  vec1.pop_back();
  vec2.pop_back();

  EXPECT_EQ(vec1.size(), vec2.size());
  EXPECT_EQ(vec1.capacity(), vec2.capacity());
  s21::Vector<int> vec3;
  std::vector<int> vec4;
  vec3.pop_back();
  vec4.pop_back();
  EXPECT_EQ(vec3.size(), vec4.size());
  EXPECT_EQ(vec3.capacity(), vec4.capacity());
}

TEST(vector_test, swap) {
  s21::Vector<int> vec1 = {1, 2, 3};
  s21::Vector<int> vec1_1 = {3, 2, 1};
  vec1.swap(vec1_1);
  for (int i = 0, j = 3; i < 3; i++) {
    EXPECT_EQ(vec1_1[i], i + 1);
    EXPECT_EQ(vec1[i], j--);
  }
}

TEST(vector_test, resize) {
  s21::Vector<int> vec1 = {1, 2, 3};
  std::vector<int> vec2 = {3, 2, 1};
  vec1.push_back(5);
  vec2.push_back(5);

  vec1.resize(10);
  vec2.resize(10);
  EXPECT_EQ(vec1.size(), vec2.size());
  EXPECT_EQ(vec1.capacity(), vec2.capacity());

  s21::Vector<int> vec3 = {1, 2, 3};
  std::vector<int> vec4 = {3, 2, 1};
  vec1.resize(2);
  vec2.resize(2);
  EXPECT_EQ(vec3.size(), vec4.size());
  EXPECT_EQ(vec3.capacity(), vec4.capacity());
}

TEST(vector_test, operator_eq) {
  s21::Vector<int> vec1 = {1, 2, 3, 5, 6, 3, 4};
  s21::Vector<int> vec2;
  vec2 = vec1;
  EXPECT_EQ(vec1.size(), vec2.size());
  EXPECT_EQ(vec1.capacity(), vec2.capacity());
  auto it_2 = vec2.begin();
  for (auto it = vec1.begin(); it != vec1.end(); ++it) {
    EXPECT_EQ(*it, *it_2);
    ++it_2;
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
