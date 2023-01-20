#include <gtest/gtest.h>

#include <iostream>
#include <map>
#include <set>

#include "../s21_containers.hpp"
#include "../s21_containersplus.hpp"

using namespace std;
using testing::InitGoogleTest;

/******************************** SET ***************************************/

TEST(Set, constructors_init_list) {
  s21::Set<int> set1 = {1, 0, 5, 20, 203, 9};
  std::set<int> set2 = {1, 0, 5, 20, 203, 9};

  ASSERT_EQ(*set1.begin(), *set2.begin());
}

TEST(Set, constructors_copy) {
  s21::Set<int> set1 = {1, 0, 5, 20, 203, 9};
  s21::Set<int> set2 = set1;

  ASSERT_EQ(*set1.begin(), *set2.begin());
}

TEST(Set, operator_eq) {
  s21::Set<int> set1 = {1, 0, 5, 20, 203, 9};
  s21::Set<int> set2 = {2, 3, 45, 5};

  set1 = std::move(set2);
  ASSERT_EQ(set1.size(), 4);
}

TEST(Set, iterators) {
  s21::Set<int> set1 = {1, 0, 5, 20, 203, 9, -13};
  std::set<int> set2 = {1, 0, 5, 20, 203, 9, -13};
  auto i_begin = set1.begin();
  auto i_end = set1.end();
  auto i_begin_o = set2.begin();

  ASSERT_EQ(*i_begin, *i_begin_o);
  ASSERT_EQ(*i_begin, -13);
  ASSERT_EQ(i_end.get_pointer(), set1.get_nill());
}

TEST(Set, capacity) {
  s21::Set<double> set1;
  std::set<double> set2 = {2.3};
  ASSERT_EQ(set1.empty(), true);
  set1.insert(2.3);
  ASSERT_EQ(set1.size(), set2.size());
  ASSERT_EQ(set1.max_size(), set2.max_size());
}

TEST(Set, clear) {
  s21::Set<int> set1 = {1, 0, 5, 20, 203, 9, -13};
  std::set<int> set2 = {1, 0, 5, 20, 203, 9, -13};

  set1.clear();
  ASSERT_EQ(set1.size(), 0);
}

TEST(Set, insert) {
  s21::Set<int> set1 = {1, 0, 5, 20, 203, 9, -13};
  std::set<int> set2 = {1, 0, 5, 20, 203, 9, -13};

  auto res = set1.insert(-1);
  auto res2 = set2.insert(-1);

  ASSERT_EQ(res.second, res2.second);
  res = set1.insert(0);
  res2 = set2.insert(0);

  ASSERT_EQ(res.second, res2.second);
  res = set1.insert(-100);
  res2 = set2.insert(-100);

  ASSERT_EQ(*res.first, *res2.first);
}

TEST(Set, erase) {
  s21::Set<int> set1 = {1, 0, 5, 20, 203, 9, -13};
  std::set<int> set2 = {1, 0, 5, 20, 203, 9, -13};

  auto iter = set1.find(5);
  auto iter2 = set2.find(5);
  set1.erase(iter);
  set2.erase(iter2);

  ASSERT_EQ(set1.size(), set2.size());
  ASSERT_EQ(*set1.begin(), *set2.begin());
}

TEST(Set, swap) {
  s21::Set<int> set1 = {1, 0, 5, 20, 203, 9, -13};
  std::set<int> set2 = {1, 0, 5, 20, 203, 9, -13};
  s21::Set<int> set3 = {355, 555, -100};
  std::set<int> set4 = {355, 555, -100};

  set1.swap(set3);
  set2.swap(set4);

  ASSERT_EQ(set1.size(), set2.size());
  ASSERT_EQ(*set1.begin(), *set2.begin());
}

TEST(Set, merge) {
  s21::Set<int> set1 = {1, 0, 5, 20, 203, 9, -13};
  s21::Set<int> set2 = {5, 555, -100};

  auto size_tmp = set1.size();
  set1.merge(set2);

  ASSERT_EQ(set1.size(), size_tmp + 2);
  ASSERT_EQ(*set1.begin(), -100);
}

TEST(Set, find) {
  s21::Set<int> set1 = {1, 0, 5, 20, 203, 9, -13};
  std::set<int> set2 = {1, 0, 5, 20, 203, 9, -13};

  auto iter1 = set1.find(5);
  auto iter2 = set2.find(5);

  ASSERT_EQ(*iter1, *iter2);
}

TEST(Set, contains) {
  s21::Set<int> set1 = {1, 0, 5, 20, 203, 9, -13};
  std::set<int> set2 = {1, 0, 5, 20, 203, 9, -13};
  bool res1 = set1.contains(1);
  ASSERT_EQ(res1, true);

  res1 = set1.contains(-100);
  ASSERT_EQ(res1, false);
}

TEST(Set, emplace) {
  s21::Set<int> set1 = {1, 0, 5, 20, 203, 9, -13};
  std::set<int> set2 = {1, 0, 5, 20, 203, 9, -13};

  auto res1 = set1.emplace(2);
  auto res2 = set2.emplace(2);
}

/******************************** MAP ***************************************/

TEST(Map, constructors) {
  s21::Map<int, int> m1 = {{1, 1}, {1, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {1, 2}, {3, 3}, {4, 4}, {5, 5}};
  auto it1 = m1.begin();
  for (auto it2 = m2.begin(); it2 != m2.end(); it1++, it2++) {
    EXPECT_EQ((*it1).second, (*it2).second);
  }
  it1 = m1.begin();
  for (auto it2 = m2.begin(); it2 != m2.end(); it1++, it2++) {
    EXPECT_EQ((*it1).first, (*it2).first);
  }
}

TEST(Map, copy_constructor) {
  s21::Map<int, int> map1 = {{1, 0}, {5, 20}, {203, 9}};
  s21::Map<int, int> map2 = map1;

  ASSERT_EQ(*map1.begin(), *map2.begin());
}

TEST(Map, operator_eq) {
  s21::Map<int, int> map1 = {{1, 0}, {5, 20}, {203, 9}};
  s21::Map<int, int> map2 = {{2, 3}, {45, 5}};

  map1 = std::move(map2);
  ASSERT_EQ(map1.size(), 2);
}

TEST(Map, at) {
  s21::Map<int, int> m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  for (size_t i = 1; i < m1.size(); i++) EXPECT_EQ(m1.at(i), m2.at(i));
}

TEST(Map, at_throw) {  // leak
  s21::Map<int, int> m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  EXPECT_ANY_THROW(m1.at(0));
  EXPECT_ANY_THROW(m2.at(0));
}

TEST(Map, operator_brackets) {
  s21::Map<int, int> m1 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  EXPECT_EQ(m1[100], m2[100]);
  EXPECT_NO_THROW(m1[-2] = 3);
  EXPECT_NO_THROW(m2[-2] = 3);
  EXPECT_NO_THROW(m1.at(-2) = 5);
  EXPECT_NO_THROW(m2.at(-2) = 5);
  EXPECT_EQ(m1.at(-2), m2.at(-2));
}

TEST(Map, begin_end) {
  s21::Map<int, int> map1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> map2 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};

  auto i_begin = map1.begin();
  auto i_end = map1.end();

  auto i_begin_o = map2.begin();
  auto i_end_o = map2.end();

  EXPECT_EQ((*i_begin).second, (*i_begin_o).second);
  EXPECT_EQ((*i_end).second, (*i_end_o).second);
}

TEST(Map, capacity) {
  s21::Map<int, int> m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  EXPECT_EQ(m1.empty(), m2.empty());
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m1.max_size(), m2.max_size());
}

TEST(Map, insert) {
  s21::Map<int, int> map1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> map2 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};

  std::pair<int, int> pair = {3, 1};

  EXPECT_EQ(map1.insert(pair).second, map2.insert(pair).second);
}

TEST(Map, insert_or_assign) {
  s21::Map<int, int> m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {3, 1}, {4, 4}, {5, 5}};
  m1.insert_or_assign(3, 1);
  EXPECT_EQ(m1[3], m2[3]);
  EXPECT_EQ(m1.at(3), m2.at(3));
}

TEST(Map, erase) {
  s21::Map<int, int> m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  m1.erase(m1.begin());
  m2.erase(m2.begin());
  EXPECT_EQ((*m1.begin()).second, (*m2.begin()).second);
}

TEST(Map, swap) {
  s21::Map<int, int> m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};

  s21::Map<int, int> m3 = {{4, 4}, {5, 5}};
  std::map<int, int> m4 = {{4, 4}, {5, 5}};

  m1.swap(m3);
  m2.swap(m4);

  ASSERT_EQ((*m1.begin()).second, (*m2.begin()).second);
}

TEST(Map, merge) {
  s21::Map<int, int> m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}};
  s21::Map<int, int> m3 = {{4, 4}, {5, 5}};

  m1.merge(m3);
  ASSERT_NO_THROW(m1.at(5));  // leak
}

TEST(Map, contains) {
  s21::Map<int, int> m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  ASSERT_FALSE(m1.contains({6, 6}));
  ASSERT_TRUE(m1.contains({2, 2}));
}

// /******************************** MULTISET
//  * ***************************************/

TEST(Multiset, constructor) {
  s21::Multiset<int> ms1 = {1, 1, 2, 1, 3, 4, 5, 3, 4, 6, 9, 6, 6, 6, 7};
  std::multiset<int> ms2 = {1, 1, 2, 1, 3, 4, 5, 3, 4, 6, 9, 6, 6, 6, 7};
  auto it1 = ms1.begin();
  for (auto it2 = ms2.begin(); it2 != ms2.end(); it1++, it2++)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(ms1.size(), ms2.size());
}

TEST(Multiset, copy_constructor) {
  s21::Multiset<int> ms1 = {1, 1, 2, 1, 3, 4, 5, 3, 4, 6, 9, 6, 6, 6, 7};
  std::multiset<int> ms2 = {1, 1, 2, 1, 3, 4, 5, 3, 4, 6, 9, 6, 6, 6, 7};
  auto ms11 = ms1;
  auto ms22 = ms2;
  auto it1 = ms11.begin();
  for (auto it2 = ms22.begin(); it2 != ms22.end(); it1++, it2++)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(ms11.size(), ms22.size());
  it1 = ms1.begin();
  for (auto it2 = ms2.begin(); it2 != ms2.end(); it1++, it2++)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(ms1.size(), ms2.size());
}

TEST(Multiset, move_constructor) {
  s21::Multiset<int> ms1 = {1, 1, 2, 1, 3, 4, 5, 3, 4, 6, 9, 6, 6, 6, 7};
  std::multiset<int> ms2 = {1, 1, 2, 1, 3, 4, 5, 3, 4, 6, 9, 6, 6, 6, 7};
  auto ms11 = std::move(ms1);
  auto ms22 = std::move(ms2);
  auto it1 = ms11.begin();
  for (auto it2 = ms22.begin(); it2 != ms22.end(); it1++, it2++)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(ms11.size(), ms22.size());
  it1 = ms1.begin();
  for (auto it2 = ms2.begin(); it2 != ms2.end(); it1++, it2++)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(ms1.size(), ms2.size());
}

TEST(Multiset, constructor_sort) {
  s21::Multiset<std::string> ms1 = {"some", "not",  "sorted", "words",
                                    "will", "come", "out",    "sorted"};
  std::multiset<std::string> ms2 = {"some", "not",  "sorted", "words",
                                    "will", "come", "out",    "sorted"};
  auto it1 = ms1.begin();
  for (auto it2 = ms2.begin(); it2 != ms2.end(); it1++, it2++)
    EXPECT_EQ(*it1, *it2);
}

TEST(Multiset, begin) {
  s21::Multiset<int> ms1 = {1, 1, 2, 1, 3, 4, 5, 3, 4, 6, 9, 6, 6, 6, 7};
  std::multiset<int> ms2 = {1, 1, 2, 1, 3, 4, 5, 3, 4, 6, 9, 6, 6, 6, 7};
  auto it1 = ms1.begin();
  auto it2 = ms2.begin();
  EXPECT_EQ(*it1, *it2);
}

TEST(Multiset, capasity) {
  s21::Multiset<int> ms1;
  std::multiset<int> ms2;
  EXPECT_EQ(ms1.empty(), ms2.empty());
  EXPECT_EQ(ms1.size(), ms2.size());
}

TEST(Multiset, clear) {
  s21::Multiset<int> ms1 = {1, 1, 2, 1, 3, 4, 5, 3, 4, 6, 9, 6, 6, 6, 7};
  std::multiset<int> ms2 = {1, 1, 2, 1, 3, 4, 5, 3, 4, 6, 9, 6, 6, 6, 7};
  ms1.clear();
  ms2.clear();
  EXPECT_EQ(ms1.empty(), ms2.empty());
}

TEST(Multiset, insert) {
  s21::Multiset<int> ms1;
  std::multiset<int> ms2;
  for (int i = 0; i < 1000; i++) {
    int num = rand();
    ms1.insert(num);
    ms2.insert(num);
  }
  auto it1 = ms1.begin();
  for (auto it2 = ms2.begin(); it2 != ms2.end(); it1++, it2++)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(ms1.size(), ms2.size());
}

TEST(Multiset, erase) {
  s21::Multiset<int> ms1 = {1, 1, 2, 1, 3, 4, 5, 3, 4, 6, 9, 6, 6, 6, 7};
  std::multiset<int> ms2 = {1, 1, 2, 1, 3, 4, 5, 3, 4, 6, 9, 6, 6, 6, 7};
  EXPECT_EQ(ms1.size(), ms2.size());
  auto it1 = ms1.begin();
  auto it2 = ms2.begin();
  ms1.erase(it1);
  ms2.erase(it2);
  it1 = ms1.begin();
  it2 = ms2.begin();
  for (; it2 != ms2.end(); it1++, it2++) EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(ms1.size(), ms2.size());
}

TEST(Multiset, swap) {
  s21::Multiset<int> ms1 = {1, 1, 2, 1, 3, 4, 5, 3, 4, 6, 9, 6, 6, 6, 7};
  std::multiset<int> ms2 = {1, 1, 2, 1, 3, 4, 5, 3, 4, 6, 9, 6, 6, 6, 7};
  s21::Multiset<int> ms11;
  std::multiset<int> ms22;
  ms1.swap(ms11);
  ms2.swap(ms22);
  EXPECT_EQ(ms1.size(), ms2.size());
  EXPECT_EQ(ms11.size(), ms22.size());
  auto it1 = ms1.begin();
  auto it11 = ms11.begin();
  auto it2 = ms2.begin();
  auto it22 = ms22.begin();
  for (; it2 != ms2.end(); it1++, it2++) EXPECT_EQ(*it1, *it2);
  for (; it22 != ms22.end(); it11++, it22++) EXPECT_EQ(*it11, *it22);
}

// TEST(Multiset, merge) {
//   s21::Multiset<int> ms1 = {1, 1, 2, 1, 3, 4, 5, 3, 4, 6, 9, 6, 6, 6, 7};
//   std::multiset<int> ms2 = {1, 1, 2, 1, 3, 4, 5, 3, 4, 6, 9, 6, 6, 6, 7};
//   s21::Multiset<int> ms11 = {1, 1, 2, 1, 3};
//   std::multiset<int> ms22 = {1, 1, 2, 1, 3};
//   ms1.merge(ms11);
//   ms2.merge(ms22);
//   auto it1 = ms1.begin();
//   for (auto it2 = ms2.begin(); it2 != ms2.end(); it1++, it2++) {
//     EXPECT_EQ(*it1, *it2);
//   }
// }

TEST(Multiset, count) {
  s21::Multiset<int> ms1 = {1, 1, 2, 1, 3, 4, 5, 3, 4, 6, 9, 6, 6, 6, 7};
  std::multiset<int> ms2 = {1, 1, 2, 1, 3, 4, 5, 3, 4, 6, 9, 6, 6, 6, 7};
  EXPECT_EQ(ms1.count(1), ms2.count(1));
  EXPECT_EQ(ms1.count(2), ms2.count(2));
  EXPECT_EQ(ms1.count(6), ms2.count(6));
}

TEST(Multiset, find) {
  s21::Multiset<int> ms1 = {1, 1, 2, 1, 3, 4, 5, 3, 4, 6, 9, 6, 6, 6, 7};
  std::multiset<int> ms2 = {1, 1, 2, 1, 3, 4, 5, 3, 4, 6, 9, 6, 6, 6, 7};
  EXPECT_EQ(*ms1.find(1), *ms2.find(1));
  EXPECT_EQ(*ms1.find(2), *ms2.find(2));
  EXPECT_EQ(*ms1.find(6), *ms2.find(6));
}

TEST(Multiset, contains) {
  s21::Multiset<int> ms1 = {1, 1, 2, 1, 3, 4, 5, 3, 4, 6, 9, 6, 6, 6, 7};
  EXPECT_EQ(ms1.contains(1), true);
  EXPECT_EQ(ms1.contains(2), true);
  EXPECT_EQ(ms1.contains(6), true);
}

TEST(Multiset, equal_range) {
  s21::Multiset<int> ms1 = {1, 1, 2, 1, 3, 4, 5, 3, 4, 6, 9, 6, 6, 6, 7};
  std::multiset<int> ms2 = {1, 1, 2, 1, 3, 4, 5, 3, 4, 6, 9, 6, 6, 6, 7};
  auto pair1 = ms1.equal_range(9);
  auto pair2 = ms2.equal_range(9);
  EXPECT_EQ(*(pair1.first), *(pair2.first));
  pair1 = ms1.equal_range(1);
  pair2 = ms2.equal_range(1);
  EXPECT_EQ(*(pair1.first), *(pair2.first));
  EXPECT_EQ(*(pair1.second), *(pair2.second));
  pair1 = ms1.equal_range(2);
  pair2 = ms2.equal_range(2);
  EXPECT_EQ(*(pair1.first), *(pair2.first));
  EXPECT_EQ(*(pair1.second), *(pair2.second));
}

TEST(Multiset, upper_bound) {
  s21::Multiset<int> ms1 = {1, 1, 2, 1, 3, 4, 5, 3, 4, 6, 9, 6, 6, 6, 7};
  std::multiset<int> ms2 = {1, 1, 2, 1, 3, 4, 5, 3, 4, 6, 9, 6, 6, 6, 7};
  auto it1 = ms1.upper_bound(1);
  auto it2 = ms2.upper_bound(1);
  EXPECT_EQ(*(it1), *(it2));
  it1 = ms1.upper_bound(2);
  it2 = ms2.upper_bound(2);
  EXPECT_EQ(*(it1), *(it2));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
