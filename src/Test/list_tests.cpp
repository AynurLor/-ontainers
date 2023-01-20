#include <list>

#include "../List/s21_list.hpp"
#include "gtest/gtest.h"

TEST(tests_of_list, push_back) {
  s21::List<int> Mylist_1 = {1};
  Mylist_1.push_back(2);
  Mylist_1.push_back(3);
  Mylist_1.push_back(4);

  auto Mylist_2 = {1, 2, 3, 4};
  auto it_2 = Mylist_2.begin();
  for (auto it = Mylist_1.begin(); it != Mylist_1.end();) {
    EXPECT_EQ(*it_2, *it);
    ++it;
    ++it_2;
  }

  auto it = Mylist_1.begin();
  for (size_t i = 1; i <= Mylist_1.size(); i++) {
    EXPECT_EQ(i, *it);
    ++it;
  }
  auto Mylist_3 = std::move(Mylist_1);
}

TEST(tests_of_List, push_front) {
  s21::List<int> MyList_1;
  MyList_1.push_front(1);
  MyList_1.push_front(2);
  MyList_1.push_front(3);
  auto it = MyList_1.begin();
  int i = 3;
  size_t size = 0;
  while (size < MyList_1.size()) {
    ASSERT_EQ(i, *it);
    i--;
    ++it;
    size++;
  }
}
TEST(tests_of_List, pop_back) {
  s21::List<int> MyList_1;
  MyList_1.push_front(1);
  MyList_1.push_front(2);
  MyList_1.push_front(3);
  MyList_1.pop_back();
  auto it = MyList_1.begin();
  int i = 3;
  size_t size = 0;
  while (size < MyList_1.size()) {
    ASSERT_EQ(i, *it);
    i--;
    ++it;
    size++;
  }
}
TEST(tests_of_List, pop_front) {
  s21::List<int> MyList_1;
  MyList_1.push_front(1);
  MyList_1.push_front(2);
  MyList_1.push_front(3);
  MyList_1.pop_front();
  auto it = MyList_1.begin();
  int i = 2;
  size_t size = 0;
  while (size < MyList_1.size()) {
    ASSERT_EQ(i, *it);
    i--;
    ++it;
    size++;
  }
}

TEST(tests_of_List, front) {
  s21::List<int> MyList_1 = {1, 2, 3};
  int a = MyList_1.front();
  ASSERT_EQ(1, a);
}

TEST(tests_of_List, back) {
  s21::List<int> MyList_1 = {1, 2, 3};
  int a = MyList_1.back();
  ASSERT_EQ(3, a);
}

TEST(tests_of_List, empty) {
  s21::List<int> MyList_1 = {1, 2, 3};
  int a = MyList_1.empty();
  ASSERT_EQ(0, a);
}
TEST(tests_of_List, empty_2) {
  s21::List<int> MyList_1;
  int a = MyList_1.empty();
  ASSERT_EQ(1, a);
}
TEST(tests_of_List, clear) {
  std::list<int> stdlist = {1, 2, 3, 4};
  s21::List<int> MyList_1 = {1, 2, 3, 4};
  stdlist.clear();
  MyList_1.clear();
  int a = MyList_1.empty();
  int b = stdlist.empty();
  auto it = MyList_1.begin();
  ASSERT_EQ(a, b);
}
TEST(tests_of_List, size) {
  s21::List<int> MyList_1 = {1, 2, 3, 4};
  size_t a = MyList_1.size();
  ASSERT_EQ(4, a);
}

TEST(tests_of_List, swap) {
  s21::List<int> MyList_1 = {1, 2, 3, 4};
  s21::List<int> MyList_2 = {4, 3, 2, 1};

  MyList_1.swap(MyList_2);
  std::list<int> stdList1 = {1, 2, 3, 4};
  std::list<int> stdList2 = {4, 3, 2, 1};
  stdList2.swap(stdList1);

  auto std_it = stdList2.begin();

  for (auto it = MyList_2.begin(); it != MyList_2.end(); ++it) {
    EXPECT_EQ(*std_it, *it);
    std_it++;
  }
}

TEST(tests_of_List, swap_1) {
  s21::List<int> MyList_1 = {7, 8};
  s21::List<int> MyList_2 = {4, 3, 2, 1};
  MyList_2.swap(MyList_1);
  auto it = MyList_2.begin();
  int i = 7;
  size_t size = 0;
  while (size < MyList_2.size()) {
    ASSERT_EQ(i, *it);
    i++;
    ++it;
    size++;
  }
}

TEST(tests_of_List, reverse) {
  s21::List<int> MyList_2 = {4, 3, 2, 1};
  std::list<int> stdList = {4, 3, 2, 1};
  MyList_2.reverse();
  stdList.reverse();
  auto it = MyList_2.begin();
  for (auto itStd = stdList.begin(); itStd != stdList.end(); ++itStd) {
    EXPECT_EQ(*it, *itStd);
    ++it;
  }
}

TEST(tests_of_List, unique) {
  s21::List<int> MyList_2 = {1, 1, 2, 3, 4};
  std::list<int> stdList = {1, 1, 2, 3, 4};
  MyList_2.unique();
  stdList.unique();
  auto it = MyList_2.begin();
  for (auto itStd = stdList.begin(); itStd != stdList.end(); ++itStd) {
    EXPECT_EQ(*it, *itStd);
    ++it;
  }
}

TEST(tests_of_List, unique_2) {
  s21::List<int> MyList_2 = {1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4};
  std::list<int> stdList = {1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4};
  MyList_2.unique();
  stdList.unique();
  auto it = MyList_2.begin();
  for (auto itStd = stdList.begin(); itStd != stdList.end(); ++itStd) {
    EXPECT_EQ(*it, *itStd);
    ++it;
  }
}

TEST(tests_of_List, unique_3) {
  s21::List<int> MyList_2 = {1, 2, 3, 4, 1};
  std::list<int> stdList = {1, 2, 3, 4, 1};
  MyList_2.unique();
  stdList.unique();
  auto it = MyList_2.begin();
  for (auto itStd = stdList.begin(); itStd != stdList.end(); ++itStd) {
    EXPECT_EQ(*it, *itStd);
    ++it;
  }
}

TEST(tests_of_List, merge) {
  s21::List<int> MyList_1 = {1, 5, 7, 8, 12};
  s21::List<int> MyList_2 = {2, 3, 4, 7, 9};
  s21::List<int> result = {1, 2, 3, 4, 5, 7, 7, 8, 9, 12};
  MyList_1.merge(MyList_2);

  auto it = MyList_1.begin();
  for (auto it_res = result.begin(); it_res != result.end(); ++it_res) {
    EXPECT_EQ(*it, *it_res);
    ++it;
  }
  EXPECT_EQ(MyList_1.size(), result.size());
  EXPECT_EQ(true, MyList_2.empty());
}

TEST(tests_of_List, erase) {
  s21::List<int> MyList_2 = {1, 1, 2, 3, 4};
  s21::List<int>::iterator it_1 = MyList_2.begin();
  MyList_2.erase(it_1.node());
  auto it = MyList_2.begin();
  int i = 1;
  size_t size = 0;
  while (size < MyList_2.size()) {
    ASSERT_EQ(i, *it);
    i++;
    ++it;
    size++;
  }
}

TEST(tests_of_List, splice) {
  s21::List<int> MyList_1 = {1, 4, 5, 6};
  s21::List<int> MyList_2 = {2, 3};
  auto it_1 = MyList_1.begin();
  ++it_1;
  MyList_1.splice(it_1.node(), MyList_2);
  auto it = MyList_1.begin();
  std::list<int> result = {1, 2, 3, 4, 5, 6};

  for (auto it_res = result.begin(); it_res != result.end(); it_res++) {
    EXPECT_EQ(*it, *it_res);
    ++it;
  }

  std::list<int> result_2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::List<int> MyList3 = {7, 8, 9};
  MyList_1.splice(MyList_1.end(), MyList3);
  it = MyList_1.begin();
  for (auto it_res = result_2.begin(); it_res != result_2.end(); it_res++) {
    EXPECT_EQ(*it, *it_res);
    ++it;
  }

  std::list<int> result_3 = {-3, -2, -1, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::List<int> MyList4 = {-3, -2, -1};
  MyList_1.splice(MyList_1.begin(), MyList4);
  it = MyList_1.begin();
  for (auto it_res = result_3.begin(); it_res != result_3.end(); it_res++) {
    EXPECT_EQ(*it, *it_res);
    ++it;
  }
}

TEST(tests_of_List, sort) {
  s21::List<int> MyList_2 = {1, 534, 63, 123, 87, 123, 23, 9, 0};
  std::list<int> stdList = {1, 534, 63, 123, 87, 123, 23, 9, 0};
  MyList_2.sort();
  stdList.sort();
  auto it = MyList_2.begin();
  for (auto it_res = stdList.begin(); it_res != stdList.end(); it_res++) {
    EXPECT_EQ(*it, *it_res);
    ++it;
  }
}

TEST(tests_of_List, insert) {
  s21::List<int> MyList_1 = {1, 2, 3, 4, 5};
  std::list<int> stdList = {1, 2, 3, 4, 5};
  auto it_1 = MyList_1.begin();
  auto it_std = stdList.begin();

  auto it_2 = MyList_1.insert(it_1, 0);
  auto it_std_2 = stdList.insert(it_std, 0);

  ASSERT_EQ(*it_std_2, *it_2);

  it_1 += 3;
  for (size_t i = 0; i < 3; i++) {
    it_std++;
  }
  it_2 = MyList_1.insert(it_1, 6);
  it_std_2 = stdList.insert(it_std, 6);
  ASSERT_EQ(*it_std_2, *it_2);

  it_1 = MyList_1.end();
  it_std = stdList.end();
  it_2 = MyList_1.insert(it_1, 7);
  it_std_2 = stdList.insert(it_std, 7);
  ASSERT_EQ(*it_std_2, *it_2);
}

// TEST(list, emplace_test_1) {
//   struct structure {
//     int x_;
//     long double y_;
//     char z_;
//     bool operator==(const structure &other) const {
//       return (x_ == other.x_ && y_ == other.y_ && z_ == other.z_);
//     }
//     structure() {
//       x_ = 0;
//       y_ = 0;
//       z_ = 0;
//     }
//     structure(int x, long double y, char z) : x_(x), y_(y), z_(z) {}
//   };

//   structure elem1 = {1, 2., '3'};
//   structure elem2 = {7, 8., '9'};
//   structure expecting_result = {6, 7., '8'};
//   std::initializer_list<structure> a = {elem1, elem2};
//   s21::List<structure> my_list(a);
//   auto itr = my_list.cbegin();
//   ++itr;
//   auto return_itr = my_list.emplace(itr, 6, 7., '8');
//   EXPECT_TRUE(*return_itr == expecting_result);
//   EXPECT_TRUE(*itr == elem2);
//   --itr;
//   --itr;
//   EXPECT_TRUE(*itr == elem1);
// }

// TEST(list, emplace_test_2) {
//   struct structure {
//     int x_;
//     long double y_;
//     char z_;
//     bool operator==(const structure &other) const {
//       return (x_ == other.x_ && y_ == other.y_ && z_ == other.z_);
//     }
//     structure() {
//       x_ = 0;
//       y_ = 0;
//       z_ = 0;
//     }
//     structure(int x, long double y, char z) : x_(x), y_(y), z_(z) {}
//   };
//   structure expecting_result = {6, 7., '8'};
//   std::initializer_list<structure> a;
//   s21::List<structure> my_list(a);
//   auto itr = my_list.cbegin();
//   auto return_itr = my_list.emplace(itr, 6, 7., '8');
//   EXPECT_TRUE(*return_itr == expecting_result);
//   EXPECT_TRUE(*(my_list.begin()) == expecting_result);
// }

// TEST(list, emplace_test_3) {
//   s21::List<int> my_list;
//   auto itr = my_list.cbegin();
//   auto return_itr = my_list.emplace(itr, 6);
//   EXPECT_EQ(*return_itr, 6);
// }

// TEST(list, emplace_back_test) {
//   struct structure {
//     int x_;
//     long double y_;
//     char z_;
//     bool operator==(const structure &other) const {
//       return (x_ == other.x_ && y_ == other.y_ && z_ == other.z_);
//     }
//     structure() {
//       x_ = 0;
//       y_ = 0;
//       z_ = 0;
//     }
//     structure(int x, long double y, char z) : x_(x), y_(y), z_(z) {}
//   };

//   structure elem1 = {1, 2., '3'};
//   structure elem2 = {6, 7., '8'};
//   structure expecting_result = {7, 8., '9'};
//   std::initializer_list<structure> a = {elem1, elem2};
//   s21::List<structure> my_list(a);
//   auto itr = my_list.begin();

//   my_list.emplace_back(7, 8., '9');
//   EXPECT_TRUE(*itr == elem1);
//   ++itr;
//   EXPECT_TRUE(*itr == elem2);
//   ++itr;
//   EXPECT_TRUE(*itr == expecting_result);
// }

// TEST(list, emplace_front_test) {
//   struct structure {
//     int x_;
//     long double y_;
//     char z_;
//     bool operator==(const structure &other) {
//       return (x_ == other.x_ && y_ == other.y_ && z_ == other.z_);
//     }

//     structure() {
//       x_ = 0;
//       y_ = 0;
//       z_ = 0;
//     }
//     structure(int x, long double y, char z) : x_(x), y_(y), z_(z) {}
//   };

//   structure elem1 = {6, 7., '8'};
//   structure elem2 = {7, 8., '9'};
//   structure expecting_result = {1, 2., '3'};
//   std::initializer_list<structure> a = {elem1, elem2};
//   s21::List<structure> my_list(a);
//   my_list.emplace_front(1, 2., '3');
//   auto itr = my_list.begin();
//   EXPECT_TRUE(*itr == expecting_result);
//   ++itr;
//   EXPECT_TRUE(*itr == elem1);
//   ++itr;
//   EXPECT_TRUE(*itr == elem2);
// }

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
