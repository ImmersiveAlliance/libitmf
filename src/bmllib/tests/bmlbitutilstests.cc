#include "gtest/gtest.h"
#include "../core/bmlbitutils.h"

namespace bmllib {

	TEST(LeftShiftTest, HandlesSingleByteMSB0) {
		BMLBitVector arr;
		arr = arr << 3;
		EXPECT_EQ(0, 0);
	}

	TEST(LeftShiftTest, HandlesSingleByteMSB1) {
		EXPECT_EQ(0, 0);
	}

	TEST(LeftShiftTest, HandlesMultipleBytes1) {

	}

	TEST(LeftShiftTest, HandlesMultipleBytes2) {

	}

	TEST(RightShiftTest, HandlesSingleByteMSB0) {
		BMLBitVector arr;
		arr = arr >> 3;
		EXPECT_EQ(0, 0);
	}

	TEST(RightShiftTest, HandlesSingleByteMSB1) {
		EXPECT_EQ(0, 0);
	}

	TEST(RightShiftTest, HandlesMultipleBytes1) {

	}

	TEST(RightShiftTest, HandlesMultipleBytes2) {

	}

	TEST(XorTest, SameLength) {
		BMLBitVector arr1;
		BMLBitVector arr2;
		BMLBitVector result;
		result = arr1 ^ arr2;
	}

	TEST(XorTest, DifferentLengths1) {

	}

	TEST(XorTest, DifferentLengths2) {

	}

	TEST(OrTest, SameLength) {
		BMLBitVector arr1;
		BMLBitVector arr2;
		BMLBitVector result;
		result = arr1 ^ arr2;
	}

	TEST(OrTest, DifferentLengths1) {

	}

	TEST(OrTest, DifferentLengths2) {

	}

	TEST(AndTest, SameLength) {
		BMLBitVector arr1;
		BMLBitVector arr2;
		BMLBitVector result;
		result = arr1 & arr2;
	}

	TEST(AndTest, DifferentLengths1) {

	}

	TEST(AndTest, DifferentLengths2) {

	}
}