#include "gtest/gtest.h"

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <array>

#include "linkedList.h"

#define BIG_SIZE 1000

/*
 * list_create
 */

TEST(ListCreateTest, Empty) {
  struct list l;

  list_create(&l);

  EXPECT_TRUE(list_empty(&l));
  EXPECT_EQ(list_size(&l), 0u);

  list_destroy(&l);
}

/*
 * list_create_from
 */

TEST(ListCreateFromTest, OneElement) {
  static const int origin[] = { 1 };

  struct list l;
  list_create_from(&l, origin, std::size(origin));

  EXPECT_FALSE(list_empty(&l));
  EXPECT_EQ(list_size(&l), std::size(origin));
  EXPECT_TRUE(list_equals(&l, origin, std::size(origin)));

  list_destroy(&l);
}

TEST(ListCreateFromTest, ManyElements) {
  static const int origin[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  struct list l;
  list_create_from(&l, origin, std::size(origin));

  EXPECT_FALSE(list_empty(&l));
  EXPECT_EQ(list_size(&l), std::size(origin));
  EXPECT_TRUE(list_equals(&l, origin, std::size(origin)));

  list_destroy(&l);
}

/*
 * list_equals
 */

TEST(ListEqualsTest, DifferentElement) {
  static const int origin[]    = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  static const int reference[] = { 1, 2, 3, 4, 5, 6, 7, 8, 10 };

  struct list l;
  list_create_from(&l, origin, std::size(origin));

  EXPECT_FALSE(list_equals(&l, reference, std::size(reference)));

  list_destroy(&l);
}

TEST(ListEqualsTest, SizeShorter) {
  static const int origin[]    = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  static const int reference[] = { 1, 2, 3, 4, 5, 6, 7, 8 };

  struct list l;
  list_create_from(&l, origin, std::size(origin));

  EXPECT_FALSE(list_equals(&l, reference, std::size(reference)));

  list_destroy(&l);
}

TEST(ListEqualsTest, SizeLarger) {
  static const int origin[]    = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  static const int reference[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

  struct list l;
  list_create_from(&l, origin, std::size(origin));

  EXPECT_FALSE(list_equals(&l, reference, std::size(reference)));

  list_destroy(&l);
}

/*
 * list_push_front
 */

TEST(ListPushFrontTest, OneElement) {
  struct list l;
  list_create(&l);

  list_push_front(&l, 1);

  EXPECT_FALSE(list_empty(&l));
  EXPECT_EQ(list_size(&l), 1u);
  EXPECT_EQ(list_get(&l, 0), 1);

  list_destroy(&l);
}


TEST(ListPushFrontTest, ManyElements) {
  static const int origin[] = { 8, 4, 1, 6, 10, 3, 0, 9, 5, 2, 7 };

  struct list l;
  list_create(&l);

  for (std::size_t i = 0; i < std::size(origin); ++i) {
    list_push_front(&l, origin[std::size(origin) - i - 1]);
  }

  EXPECT_FALSE(list_empty(&l));
  EXPECT_EQ(list_size(&l), std::size(origin));

  for (std::size_t i = 0; i < std::size(origin); ++i) {
    EXPECT_EQ(list_get(&l, i), origin[i]);
  }

  EXPECT_TRUE(list_equals(&l, origin, std::size(origin)));

  list_destroy(&l);
}


TEST(ListPushFrontTest, Stressed) {
  struct list l;
  list_create(&l);

  for (int i = 0; i < BIG_SIZE; ++i) {
    list_push_front(&l, i + 1);
    EXPECT_EQ(list_get(&l, 0), i + 1);
    EXPECT_EQ(list_size(&l), static_cast<std::size_t>(i + 1));
  }

  EXPECT_FALSE(list_empty(&l));
  EXPECT_EQ(list_size(&l), static_cast<std::size_t>(BIG_SIZE));

  for (int i = 0; i < BIG_SIZE; ++i) {
    EXPECT_EQ(list_get(&l, BIG_SIZE - i - 1), i + 1);
  }

  list_destroy(&l);
}

/*
 * list_pop_front
 */

TEST(ListPopFrontTest, OneElement) {
  static const int origin[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  struct list l;
  list_create_from(&l, origin, std::size(origin));

  EXPECT_EQ(list_size(&l), std::size(origin));

  list_pop_front(&l);

  EXPECT_EQ(list_size(&l), std::size(origin) - 1);

  for (std::size_t i = 0; i < std::size(origin) - 1; ++i) {
    EXPECT_EQ(list_get(&l, i), origin[i + 1]);
  }

  list_destroy(&l);
}

TEST(ListPopFrontTest, ManyElements) {
  static const int origin[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  struct list l;
  list_create_from(&l, origin, std::size(origin));

  EXPECT_EQ(list_size(&l), std::size(origin));

  for (std::size_t i = 0; i < std::size(origin); ++i) {
    list_pop_front(&l);
  }

  EXPECT_TRUE(list_empty(&l));
  EXPECT_EQ(list_size(&l), 0u);

  list_destroy(&l);
}

/*
 * list_push_back
 */

TEST(ListPushBackTest, OneElement) {
  struct list l;
  list_create(&l);

  list_push_back(&l, 1);

  EXPECT_FALSE(list_empty(&l));
  EXPECT_EQ(list_size(&l), 1u);
  EXPECT_EQ(list_get(&l, 0), 1);

  list_destroy(&l);
}


TEST(ListPushBackTest, ManyElements) {
  static const int origin[] = { 8, 4, 1, 6, 10, 3, 0, 9, 5, 2, 7 };

  struct list l;
  list_create(&l);

  for (std::size_t i = 0; i < std::size(origin); ++i) {
    list_push_back(&l, origin[i]);
  }

  EXPECT_FALSE(list_empty(&l));
  EXPECT_EQ(list_size(&l), std::size(origin));

  for (std::size_t i = 0; i < std::size(origin); ++i) {
    EXPECT_EQ(list_get(&l, i), origin[i]);
  }

  EXPECT_TRUE(list_equals(&l, origin, std::size(origin)));

  list_destroy(&l);
}


TEST(ListPushBackTest, Stressed) {
  struct list l;
  list_create(&l);

  for (int i = 0; i < BIG_SIZE; ++i) {
    list_push_back(&l, i + 1);
    EXPECT_EQ(list_get(&l, i), i + 1);
    EXPECT_EQ(list_size(&l), static_cast<std::size_t>(i + 1));
  }

  EXPECT_FALSE(list_empty(&l));
  EXPECT_EQ(list_size(&l), static_cast<std::size_t>(BIG_SIZE));

  for (int i = 0; i < BIG_SIZE; ++i) {
    EXPECT_EQ(list_get(&l, i), i + 1);
  }

  list_destroy(&l);
}

/*
 * list_pop_back
 */

TEST(ListPopBackTest, OneElement) {
  static const int origin[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  struct list l;
  list_create_from(&l, origin, std::size(origin));

  EXPECT_EQ(list_size(&l), std::size(origin));

  list_pop_back(&l);

  EXPECT_EQ(list_size(&l), std::size(origin) - 1);

  for (std::size_t i = 0; i < std::size(origin) - 1; ++i) {
    EXPECT_EQ(list_get(&l, i), origin[i]);
  }

  list_destroy(&l);
}

TEST(ListPopBackTest, ManyElements) {
  static const int origin[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  struct list l;
  list_create_from(&l, origin, std::size(origin));

  EXPECT_EQ(list_size(&l), std::size(origin));

  for (std::size_t i = 0; i < std::size(origin); ++i) {
    list_pop_back(&l);
  }

  EXPECT_TRUE(list_empty(&l));
  EXPECT_EQ(list_size(&l), 0u);

  list_destroy(&l);
}

/*
 * list_insert
 */

TEST(ListInsertTest, Beginning) {
  static const int origin[] = { 9, 3, 7, 2, 4, 0, 8 };
  static const int expected[] = { 42, 9, 3, 7, 2, 4, 0, 8 };

  struct list l;
  list_create_from(&l, origin, std::size(origin));

  list_insert(&l, 42, 0); // insert at the beginning

  EXPECT_EQ(list_size(&l), std::size(expected));
  EXPECT_TRUE(list_equals(&l, expected, std::size(expected)));

  list_destroy(&l);
}

TEST(ListInsertTest, Middle) {
  static const int origin[] = { 9, 3, 7, 2, 4, 0, 8 };
  static const int expected[] = { 9, 3, 7, 42, 2, 4, 0, 8 };

  struct list l;
  list_create_from(&l, origin, std::size(origin));

  list_insert(&l, 42, 3); // insert in the middle

  EXPECT_EQ(list_size(&l), std::size(expected));
  EXPECT_TRUE(list_equals(&l, expected, std::size(expected)));

  list_destroy(&l);
}

TEST(ListInsertTest, End) {
  static const int origin[] = { 9, 3, 7, 2, 4, 0, 8 };
  static const int expected[] = { 9, 3, 7, 2, 4, 0, 8, 42 };

  struct list l;
  list_create_from(&l, origin, std::size(origin));

  list_insert(&l, 42, std::size(origin)); // insert at the end

  EXPECT_EQ(list_size(&l), std::size(expected));
  EXPECT_TRUE(list_equals(&l, expected, std::size(expected)));

  list_destroy(&l);
}

TEST(ListInsertTest, Stressed) {
  static const int origin[] = { 9, 3, 7, 2, 4, 0, 8 };

  struct list l;
  list_create_from(&l, origin, std::size(origin));

  for (int i = 0; i < BIG_SIZE; ++i) {
    list_insert(&l, i + 1, 4);
    EXPECT_EQ(list_size(&l), std::size(origin) + i + 1);
  }

  list_destroy(&l);
}

/*
 * list_remove
 */

TEST(ListRemoveTest, Beginning) {
  static const int origin[] = { 9, 3, 7, 2, 4, 0, 8 };
  static const int expected[] = { 3, 7, 2, 4, 0, 8 };

  struct list l;
  list_create_from(&l, origin, std::size(origin));

  list_remove(&l, 0); // remove at the beginning

  EXPECT_EQ(list_size(&l), std::size(expected));
  EXPECT_TRUE(list_equals(&l, expected, std::size(expected)));

  list_destroy(&l);
}

TEST(ListRemoveTest, Middle) {
  static const int origin[] = { 9, 3, 7, 2, 4, 0, 8 };
  static const int expected[] = { 9, 3, 7, 4, 0, 8 };

  struct list l;
  list_create_from(&l, origin, std::size(origin));

  list_remove(&l, 3); // remove in the middle

  EXPECT_EQ(list_size(&l), std::size(expected));
  EXPECT_TRUE(list_equals(&l, expected, std::size(expected)));

  list_destroy(&l);
}

TEST(ListRemoveTest, End) {
  static const int origin[] = { 9, 3, 7, 2, 4, 0, 8 };
  static const int expected[] = { 9, 3, 7, 2, 4, 0 };

  struct list l;
  list_create_from(&l, origin, std::size(origin));

  list_remove(&l, std::size(origin) - 1); // remove at the end

  EXPECT_EQ(list_size(&l), std::size(expected));
  EXPECT_TRUE(list_equals(&l, expected, std::size(expected)));

  list_destroy(&l);
}

/*
 * list_get
 */

TEST(ListGetTest, ValidIndex) {
  static const int origin[] = { 9, 3, 7, 2, 4, 0, 8 };

  struct list l;
  list_create_from(&l, origin, std::size(origin));

  for (std::size_t i = 0; i < std::size(origin); ++i) {
    EXPECT_EQ(list_get(&l, i), origin[i]);
  }

  list_destroy(&l);
}

TEST(ListGetTest, NotValidIndex) {
  static const int origin[] = { 9, 3, 7, 2, 4, 0, 8 };

  struct list l;
  list_create_from(&l, origin, std::size(origin));

  EXPECT_EQ(list_get(&l, std::size(origin)), 0);
  EXPECT_EQ(list_get(&l, -1), 0);

  list_destroy(&l);
}

/*
 * list_set
 */

TEST(ListSetTest, ValidIndex) {
  static const int origin[] = { 9, 3, 7, 2, 4, 0, 8 };

  struct list l;
  list_create_from(&l, origin, std::size(origin));

  for (std::size_t i = 0; i < std::size(origin); ++i) {
    list_set(&l, i, origin[i] - 1);
    EXPECT_EQ(list_get(&l, i), origin[i] - 1);
  }

  EXPECT_EQ(list_size(&l), std::size(origin));

  list_destroy(&l);
}

TEST(ListSetTest, NotValidIndex) {
  static const int origin[] = { 9, 3, 7, 2, 4, 0, 8 };

  struct list l;
  list_create_from(&l, origin, std::size(origin));

  list_set(&l, std::size(origin), 42);
  list_set(&l, -1, 42);

  EXPECT_EQ(list_size(&l), std::size(origin));

  for (std::size_t i = 0; i < std::size(origin); ++i) {
    EXPECT_EQ(list_get(&l, i), origin[i]);
  }

  list_destroy(&l);
}

/*
 * list_search
 */

TEST(ListSearchTest, Present) {
  static const int origin[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  struct list l;
  list_create_from(&l, origin, std::size(origin));

  for (size_t i = 0; i < std::size(origin); ++i) {
    size_t index = list_search(&l, origin[i]);
    EXPECT_EQ(index, i);
  }

  list_destroy(&l);
}

TEST(ListSearchTest, NotPresent) {
  static const int origin[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  struct list l;
  list_create_from(&l, origin, std::size(origin));

  size_t index = list_search(&l, -1);
  EXPECT_EQ(index, std::size(origin));

  list_destroy(&l);
}

/*
 * list_is_sorted
 */

TEST(ListIsSortedTest, Empty) {
  struct list l;
  list_create(&l);

  EXPECT_TRUE(list_is_sorted(&l));

  list_destroy(&l);
}

TEST(ListIsSortedTest, Sorted) {
  static const int origin[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

  struct list l;
  list_create_from(&l, origin, std::size(origin));

  EXPECT_TRUE(list_is_sorted(&l));

  list_destroy(&l);
}

TEST(ListIsSortedTest, NotSorted) {
  static const int origin[] = { 0, 1, 2, 3, 4, 5, 10, 9, 8, 7, 6 };

  struct list l;
  list_create_from(&l, origin, std::size(origin));

  EXPECT_FALSE(list_is_sorted(&l));

  list_destroy(&l);
}

TEST(ListIsSortedTest, NotSortedAtTheEnd) {
  static const int origin[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

  struct list l;
  list_create_from(&l, origin, std::size(origin));

  EXPECT_FALSE(list_is_sorted(&l));

  list_destroy(&l);
}

/*
 * list_split
 */

TEST(ListSplitTest, EventSize) {
  static const int origin[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  assert(std::size(origin) % 2 == 0);

  std::size_t half = std::size(origin) / 2;

  struct list l;
  list_create_from(&l, origin, std::size(origin));

  struct list l1;
  list_create(&l1);

  struct list l2;
  list_create(&l2);

  list_split(&l, &l1, &l2);

  EXPECT_TRUE(list_empty(&l));
  EXPECT_EQ(list_size(&l1), half);
  EXPECT_EQ(list_size(&l2), half);

  for (auto val : origin) {
    EXPECT_TRUE(list_search(&l1, val) != half || list_search(&l2, val) != half);
  }

  list_destroy(&l2);
  list_destroy(&l1);
  list_destroy(&l);
}


TEST(ListSplitTest, OddSize) {
  static const int origin[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
  assert(std::size(origin) % 2 == 1);

  std::size_t half = std::size(origin) / 2;

  struct list l;
  list_create_from(&l, origin, std::size(origin));

  struct list l1;
  list_create(&l1);

  struct list l2;
  list_create(&l2);

  list_split(&l, &l1, &l2);

  std::size_t sz1 = list_size(&l1);
  std::size_t sz2 = list_size(&l2);

  EXPECT_TRUE(list_empty(&l));
  EXPECT_EQ(sz1 + sz2, std::size(origin));

  EXPECT_TRUE((sz1 == half && sz2 == half + 1) || (sz1 == half + 1 && sz2 == half));

  for (auto val : origin) {
    EXPECT_TRUE(list_search(&l1, val) != sz1 || list_search(&l2, val) != sz2);
  }

  list_destroy(&l2);
  list_destroy(&l1);
  list_destroy(&l);
}

/*
 * list_merge
 */

TEST(ListMergeTest, BothNonEmpty) {
  static const int origin1[] = { 0, 1, 3, 6, 10 };
  static const int origin2[] = { 2, 4, 5, 7, 8, 9 };
  static const int expected[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

  struct list l;
  list_create(&l);

  struct list l1;
  list_create_from(&l1, origin1, std::size(origin1));

  struct list l2;
  list_create_from(&l2, origin2, std::size(origin2));

  list_merge(&l, &l1, &l2);

  EXPECT_TRUE(list_empty(&l1));
  EXPECT_TRUE(list_empty(&l2));
  EXPECT_EQ(list_size(&l), std::size(expected));
  EXPECT_TRUE(list_equals(&l, expected, std::size(expected)));

  list_destroy(&l2);
  list_destroy(&l1);
  list_destroy(&l);
}

TEST(ListMergeTest, FirstEmpty) {
  static const int origin[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

  struct list l;
  list_create(&l);

  struct list l1;
  list_create(&l1);

  struct list l2;
  list_create_from(&l2, origin, std::size(origin));

  list_merge(&l, &l1, &l2);

  EXPECT_TRUE(list_empty(&l1));
  EXPECT_TRUE(list_empty(&l2));
  EXPECT_EQ(list_size(&l), std::size(origin));
  EXPECT_TRUE(list_equals(&l, origin, std::size(origin)));

  list_destroy(&l2);
  list_destroy(&l1);
  list_destroy(&l);
}

TEST(ListMergeTest, SecondEmpty) {
  static const int origin[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

  struct list l;
  list_create(&l);

  struct list l1;
  list_create_from(&l1, origin, std::size(origin));

  struct list l2;
  list_create(&l2);

  list_merge(&l, &l1, &l2);

  EXPECT_TRUE(list_empty(&l1));
  EXPECT_TRUE(list_empty(&l2));
  EXPECT_EQ(list_size(&l), std::size(origin));
  EXPECT_TRUE(list_equals(&l, origin, std::size(origin)));

  list_destroy(&l2);
  list_destroy(&l1);
  list_destroy(&l);
}

/*
 * list_merge_sort
 */

TEST(ListMergeSortTest, NotSorted) {
  static const int origin[] = { 8, 4, 1, 6, 10, 3, 0, 9, 5, 2, 7 };

  struct list l;
  list_create_from(&l, origin, std::size(origin));

  EXPECT_FALSE(list_is_sorted(&l));

  list_merge_sort(&l);

  EXPECT_TRUE(list_is_sorted(&l));

  for (int val : origin) {
    EXPECT_NE(list_search(&l, val), std::size(origin));
  }

  list_destroy(&l);
}

TEST(ListMergeSortTest, SortedBackward) {
  static const int origin[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

  struct list l;
  list_create_from(&l, origin, std::size(origin));

  EXPECT_FALSE(list_is_sorted(&l));

  list_merge_sort(&l);

  EXPECT_TRUE(list_is_sorted(&l));

  for (int val : origin) {
    EXPECT_NE(list_search(&l, val), std::size(origin));
  }

  list_destroy(&l);
}

TEST(ListMergeSortTest, Sorted) {
  static const int origin[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

  struct list l;
  list_create_from(&l, origin, std::size(origin));

  EXPECT_TRUE(list_is_sorted(&l));

  list_merge_sort(&l);

  EXPECT_TRUE(list_is_sorted(&l));

  for (int val : origin) {
    EXPECT_NE(list_search(&l, val), std::size(origin));
  }

  list_destroy(&l);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}