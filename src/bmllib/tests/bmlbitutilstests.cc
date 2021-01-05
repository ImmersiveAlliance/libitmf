#include "gtest/gtest.h"
#include "../core/bmlbitutils.h"

TEST(leftShiftTestSuite, leftShiftTest) {
	bmllib::BMLbitset arr{ 0, 0, 0, 0, 1, 1, 1, 1 };
	arr << 3;
	ASSERT_EQ(arr, bmllib::BMLbitset({ 0, 1, 1, 1, 1, 0, 0, 0 }));
}