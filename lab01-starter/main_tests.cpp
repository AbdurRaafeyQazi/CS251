#include <gtest/gtest.h>

#include "main.h"

TEST(Average, OneNumber) {
  ASSERT_DOUBLE_EQ(average({5}), 5.0);
}

TEST(Average, TwoNumbers) {
  ASSERT_DOUBLE_EQ(average({5, 6}), 5.5);
}

TEST(Average, ManyNumbers) {
  ASSERT_DOUBLE_EQ(average({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}), 5.5);
}
