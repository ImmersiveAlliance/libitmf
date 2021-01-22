#include "gtest/gtest.h"
#include "../core/bmlbitutils.h"

namespace itmflib {
	TEST(TestChecker, CheckTestsWorking) {
		EXPECT_EQ(true, true);
	}
	/*
	TEST(CountBitsTest, SimpleIntTest) {
		int num = 65;
		int num2 = -65;

		EXPECT_EQ(countBits(num), 7);
		EXPECT_EQ(countBits(num2), 7);
	}

	TEST(CountBytesTest, SimpleIntTest) {
		int num = 65;
		int num2 = -65;

		EXPECT_EQ(countBytes(num), 1);
		EXPECT_EQ(countBytes(num2), 1);
	}

	// Constructor tests
	TEST(ConstuctorTest, VUIEInt32SpecTest1) {
		BMLBitVector a((int32_t)63);
		EXPECT_EQ(a, BMLBitVector({ 0x3F }));
	}

	TEST(ConstuctorTest, VUIEInt32SpecTest2) {
		BMLBitVector a((int32_t)64);
		EXPECT_EQ(a, BMLBitVector({ 0x40 }));
	}

	TEST(ConstuctorTest, VUIEInt32SpecTest3) {
		BMLBitVector a((int32_t)537);
		EXPECT_EQ(a, BMLBitVector(std::vector<unsigned char>({ 0x82, 0x19 }))); // 0x02, 0x19
	}
	
	TEST(ConstuctorTest, VUIEInt32SpecTest4) {
		BMLBitVector a((int32_t)100000);
		EXPECT_EQ(a, BMLBitVector(std::vector<unsigned char>({ 0xC1, 0x86, 0xA0 }))); // 0x01, 0x86, 0xA0
	}

	TEST(ConstuctorTest, VSIEInt32SpecTest1) {
		BMLBitVector a((int32_t)63, Encoding::VSIE);
		EXPECT_EQ(a, BMLBitVector({ 0x3F }));
	}

	TEST(ConstuctorTest, VSIEInt32SpecTest2) {
		BMLBitVector a((int32_t)-64, Encoding::VSIE);
		EXPECT_EQ(a, BMLBitVector(std::vector<unsigned char>({ 0xA0, 0x40 }), Encoding::VSIE)); // 0x20, 0x40
	}

	TEST(ConstuctorTest, VSIEInt32SpecTest3) {
		BMLBitVector a((int32_t)537, Encoding::VSIE);
		EXPECT_EQ(a, BMLBitVector(std::vector<unsigned char>({ 0x82, 0x19 }), Encoding::VSIE)); // 0x02, 0x19
	}

	TEST(ConstuctorTest, VSIEInt32SpecTest4) {
		BMLBitVector a((int32_t)-100000, Encoding::VSIE);
		EXPECT_EQ(a, BMLBitVector(std::vector<unsigned char>({ 0xD1, 0x86, 0xA0 }), Encoding::VSIE)); // 0x11, 0x86, 0xA0
	}

	// Shift tests
	TEST(LeftShiftTest, HandlesSingleByteMSB0) {
		BMLBitVector arr((int32_t)32);
		arr = arr << 3;
		EXPECT_EQ(arr, BMLBitVector((int32_t)256));
	}

	TEST(LeftShiftTest, HandlesSingleByteMSB1) {
		BMLBitVector arr((int32_t)72);
		arr = arr << 3;
		EXPECT_EQ(arr, BMLBitVector((int32_t)1088));
	}

	TEST(LeftShiftTest, HandlesMultipleBytes1) {
		BMLBitVector arr((int32_t)12619800);
		arr = arr << 3;
		EXPECT_EQ(arr, BMLBitVector((int32_t)100958400));
	}

	TEST(LeftShiftTest, HandlesMultipleBytes2) {
		BMLBitVector arr((int32_t)12619800);
		arr = arr << 3;
		EXPECT_EQ(arr, BMLBitVector((int32_t)100958400));
	}

	TEST(RightShiftTest, HandlesSingleByteMSB0) {
		BMLBitVector arr((int32_t)72);
		arr = arr >> 3;
		EXPECT_EQ(arr, BMLBitVector((int32_t)9));
	}

	TEST(RightShiftTest, HandlesSingleByteMSB1) {
		BMLBitVector arr((int32_t)137);
		arr = arr >> 3;
		EXPECT_EQ(arr, BMLBitVector((int32_t)241));
	}

	TEST(RightShiftTest, HandlesMultipleBytes1) {
		BMLBitVector arr((int32_t)12619800);
		arr = arr << 3;
		EXPECT_EQ(arr, BMLBitVector((int32_t)100958400));
	}

	TEST(RightShiftTest, HandlesMultipleBytes2) {
		BMLBitVector arr((int32_t)2231902501);
		arr = arr >> 3;
		EXPECT_EQ(arr, BMLBitVector((int32_t)100958400));
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
	*/
}