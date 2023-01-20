#include <gtest/gtest.h>

#include <array>

#include "../Array/s21_array.hpp"

TEST(array, constr_default) {
  s21::Array<int, 10> arr1;
  std::array<int, 10> arr2;
  EXPECT_EQ(arr1.size(), arr2.size());
  EXPECT_EQ(arr1.max_size(), arr2.max_size());
}

TEST(array, constr_init_list) {
  s21::Array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  EXPECT_EQ(arr1.size(), arr2.size());
  EXPECT_EQ(arr1.max_size(), arr2.max_size());
  for (int i = 0; i < 10; i++) EXPECT_EQ(arr1.at(i), arr2.at(i));
}

TEST(array, constr_copy) {
  s21::Array<int, 3> arr1 = {1, 2, 3};
  std::array<int, 3> arr2 = {1, 2, 3};
  auto arr11 = arr1;
  auto arr22 = arr2;
  auto it1 = arr11.begin();
  for (auto it2 = arr22.begin(); it2 != arr22.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(arr1.size(), arr2.size());
  EXPECT_EQ(arr11.size(), arr22.size());
}

TEST(array, at) {
  s21::Array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  for (int i = 0; i < 10; i++) EXPECT_EQ(arr1.at(i), arr2.at(i));
}

TEST(array, operator_brackets) {
  s21::Array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  for (int i = 0; i < 10; i++) EXPECT_EQ(arr1[i], arr2[i]);
}

TEST(array, front) {
  s21::Array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  EXPECT_EQ(arr1.front(), arr2.front());
}

TEST(array, back) {
  s21::Array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  EXPECT_EQ(arr1.back(), arr2.back());
}

TEST(array, data) {
  s21::Array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  EXPECT_EQ(*(arr1.data()), *(arr2.data()));
}

TEST(array, begin) {
  s21::Array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto it1 = arr1.begin();
  auto it2 = arr2.begin();
  EXPECT_EQ(*it1, *it2);
}

TEST(array, end) {
  s21::Array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  auto it1 = arr1.end();
  auto it2 = arr2.end();
  it1--, it2--;
  EXPECT_EQ(*it2, *it1);
}

TEST(array, empty) {
  s21::Array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  EXPECT_EQ(arr1.empty(), arr2.empty());
}

TEST(array, size) {
  s21::Array<int, 10> arr1;
  std::array<int, 10> arr2;
  EXPECT_EQ(arr1.size(), arr2.size());
}

TEST(array, max_size) {
  s21::Array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  EXPECT_EQ(arr1.max_size(), arr2.max_size());
}

TEST(array, swap) {
  s21::Array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::Array<int, 10> arr11 = {389, 3829, 111, 189, 11};
  std::array<int, 10> arr22 = {389, 3829, 111, 189, 11};
  arr1.swap(arr11);
  arr2.swap(arr22);
  EXPECT_EQ(arr1.size(), arr2.size());
  EXPECT_EQ(arr11.size(), arr22.size());
  auto it1 = arr11.begin();
  for (auto it2 = arr22.begin(); it2 != arr22.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(array, fill) {
  s21::Array<int, 0> arr1;
  std::array<int, 0> arr2;
  arr1.fill(225);
  arr2.fill(225);
  EXPECT_EQ(arr1.size(), arr2.size());
  auto it1 = arr1.begin();
  for (auto it2 = arr2.begin(); it2 != arr2.end(); ++it2) EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(arr1.size(), arr2.size());
}

TEST(array, iter_plus) {
  s21::Array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto it1 = arr1.begin();
  auto it2 = arr2.begin();
  for (int i = 0; i < 4; i++) ++it1, ++it2;
  EXPECT_EQ(*it1, *it2);
}

TEST(array, iter_minus) {
  s21::Array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto it1 = arr1.end();
  auto it2 = arr2.end();
  for (int i = 0; i < 3; i++) --it1, --it2;
  EXPECT_EQ(*it1, *it2);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}