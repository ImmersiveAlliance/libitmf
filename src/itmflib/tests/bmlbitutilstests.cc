#include "gtest/gtest.h"
#include "../core/bmlbitutils.h"

namespace itmflib {

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
	TEST(ConstructorTest, VUIEInt32SpecTest1) {
		BMLBitVector a(63);
		EXPECT_EQ(a.getBitVector(), std::vector<bool>({ 0, 0, 1, 1, 1, 1, 1, 1 })); // 0x3f
	}

	TEST(ConstructorTest, VUIEInt32SpecTest2) {
		BMLBitVector a(64);
		EXPECT_EQ(a.getBitVector(), std::vector<bool>({ 0, 1, 0, 0, 0, 0, 0, 0 })); // 0x40
	}

	TEST(ConstructorTest, VUIEInt32SpecTest3) {
		BMLBitVector a(537);
		EXPECT_EQ(a.getBitVector(), std::vector<bool>({ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1 })); // 0x82, 0x19
	}

	TEST(ConstructorTest, VUIEInt32SpecTest4) {
		BMLBitVector a(100000);
		EXPECT_EQ(a.getBitVector(), std::vector<bool>({ 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 })); // 0xC1, 0x86, 0xA0
	}

	TEST(ConstructorTest, VSIEInt32SpecTest1) {
		BMLBitVector a(63, Encoding::VSIE);
		EXPECT_EQ(a.getBitVector(), std::vector<bool>({ 0, 0, 1, 1, 1, 1, 1, 1 })); // 0x3f
		EXPECT_EQ(a.getIsNegative(), false);
	}

	TEST(ConstructorTest, VSIEInt32SpecTest2) {
		BMLBitVector a(-64, Encoding::VSIE);
		EXPECT_EQ(a.getBitVector(), BMLBitVector(std::vector<bool>({ 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 }), Encoding::VSIE).getBitVector()); // 0x20, 0x40
		EXPECT_EQ(a.getIsNegative(), true);
	}

	TEST(ConstructorTest, VSIEInt32SpecTest3) {
		BMLBitVector a(537, Encoding::VSIE);
		EXPECT_EQ(a.getBitVector(), BMLBitVector(std::vector<bool>({ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1 }), Encoding::VSIE).getBitVector()); // 0x02, 0x19
		EXPECT_EQ(a.getIsNegative(), false);
	}

	TEST(ConstructorTest, VSIEInt32SpecTest4) {
		BMLBitVector a(-100000, Encoding::VSIE);
		EXPECT_EQ(a.getBitVector(), BMLBitVector(std::vector<bool>({ 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 }), Encoding::VSIE).getBitVector()); // 0x11, 0x86, 0xA0
		EXPECT_EQ(a.getIsNegative(), true);
	}

	TEST(ConstructorTest, ComplexTest) {
		BMLBitVector a(2231902501);
		EXPECT_EQ(a.getBitVector(), std::vector<bool>({ 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1 }));
	}

	TEST(ConstructorTest, VSIE8ByteTest) {
		BMLBitVector b(-48036386720219192, VSIE);
		EXPECT_EQ(b.getBitVector(), std::vector<bool>({ 1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,1,0,1,0,1,1,0,1,1,0,1,0,1,1,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0 }));
	}

	TEST(ConstructorTest, VUIEMultiByteExtension1) {
		BMLBitVector b(16981570985633284152);
		EXPECT_EQ(b.getBitVector(), std::vector<bool>({ 1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,1,0,1,0,1,1,0,1,1,0,1,0,1,1,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0 }));
	}

	TEST(ConstructorTest, VUIEMultiByteExtension2) {
		BMLBitVector b(12615736);
		EXPECT_EQ(b.getBitVector(), std::vector<bool>({ 1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0 }));
	}

	TEST(ConstructorTest, VSIEMultiByteExtension1) {
		BMLBitVector b(-12615736, VSIE);
		EXPECT_EQ(b.getBitVector(), std::vector<bool>({ 1,1,1,0,1,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0 }));
	}

	TEST(ConstructorTest, VUIENonMultipleof8Size) {
		BMLBitVector b(218636581);
		EXPECT_EQ(b.getBitVector(), std::vector<bool>({ 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1 }));
	}

	TEST(ConstructorTest, VUIENonMultipleOf8LargeByteSize) {
		BMLBitVector b(117473493101343);
		EXPECT_EQ(b.getBitVector(), std::vector<bool>({ 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1 }));
	}

	/* BIT OPERATION TESTS */

	// Shift tests
	TEST(LeftShiftTest, HandlesSingleByteMSB0) {
		BMLBitVector arr(32);
		arr = arr << 3;
		EXPECT_EQ(arr.getBitVector(), BMLBitVector(0).getBitVector());
	}

	TEST(LeftShiftTest, HandlesSingleByteMSB1) {
		BMLBitVector arr(72);
		arr = arr << 3;
		EXPECT_EQ(arr.getBitVector(), BMLBitVector(64).getBitVector());
	}

	TEST(LeftShiftTest, HandlesMultipleBytes1) {
		BMLBitVector arr(12619800);
		arr = arr << 3;
		EXPECT_EQ(arr.getBitVector(), BMLBitVector(100958400).getBitVector());
	}

	TEST(LeftShiftTest, HandlesMultipleBytes2) {
		BMLBitVector arr(16312969);
		arr = arr << 3;
		EXPECT_EQ(arr.getBitVector(), BMLBitVector(130503752).getBitVector());
	}

	TEST(RightShiftTest, HandlesSingleByteMSB0) {
		BMLBitVector arr(72);
		arr = arr >> 3;
		EXPECT_EQ(arr.getBitVector(), BMLBitVector(9).getBitVector());
	}

	TEST(RightShiftTest, HandlesSingleByteMSB1) {
		BMLBitVector arr(137);
		arr = arr >> 3;
		EXPECT_EQ(arr.getBitVector(), std::vector<bool>({ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 }));
	}

	TEST(RightShiftTest, HandlesMultipleBytes1) {
		BMLBitVector arr(36888);
		arr = arr >> 3;
		EXPECT_EQ(arr.getBitVector(), std::vector<bool>({ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0 , 0, 0, 0, 1, 1 }));
	}

	TEST(RightShiftTest, HandlesMultipleBytes2) {
		BMLBitVector arr(218636581);
		arr = arr >> 3;
		EXPECT_EQ(arr.getBitVector(), BMLBitVector(27329572).getBitVector());
	}

	TEST(XorTest, SameLength) {
		BMLBitVector arr1(127);
		BMLBitVector arr2(85);
		BMLBitVector result = arr1 ^ arr2;
		EXPECT_EQ(result.getBitVector(), BMLBitVector(42).getBitVector());
	}

	TEST(XorTest, DifferentLengths1) {
		BMLBitVector arr1(511);
		BMLBitVector arr2(85);
		BMLBitVector result = arr1 ^ arr2;
		EXPECT_EQ(result.getBitVector(), BMLBitVector(426).getBitVector());
	}

	TEST(XorTest, DifferentLengths2) {
		BMLBitVector arr1(255);
		BMLBitVector arr2(25941);
		BMLBitVector result = arr1 ^ arr2;
		EXPECT_EQ(result.getBitVector(), BMLBitVector(26026).getBitVector());
	}

	TEST(OrTest, SameLength) {
		BMLBitVector arr1(127);
		BMLBitVector arr2(85);
		BMLBitVector result = arr1 | arr2;
		EXPECT_EQ(result.getBitVector(), BMLBitVector(127).getBitVector());
	}

	TEST(OrTest, DifferentLengths1) {
		BMLBitVector arr1(127);
		BMLBitVector arr2(1365);
		BMLBitVector result = arr1 | arr2;
		EXPECT_EQ(result.getBitVector(), BMLBitVector(1407).getBitVector());
	}

	TEST(OrTest, DifferentLengths2) {
		BMLBitVector arr1(511);
		BMLBitVector arr2(85);
		BMLBitVector result = arr1 | arr2;
		EXPECT_EQ(result.getBitVector(), BMLBitVector(511).getBitVector());
	}

	TEST(AndTest, SameLength) {
		BMLBitVector arr1(127);
		BMLBitVector arr2(85);
		BMLBitVector result = arr1 & arr2;
		EXPECT_EQ(result.getBitVector(), BMLBitVector(85).getBitVector());
	}

	TEST(AndTest, DifferentLengths1) {
		BMLBitVector arr1(127);
		BMLBitVector arr2(1365);
		BMLBitVector result = arr1 & arr2;
		EXPECT_EQ(result.getBitVector(), std::vector<bool>({ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1 }));
	}

	TEST(AndTest, DifferentLengths2) {
		BMLBitVector arr1(12799);
		BMLBitVector arr2(85);
		BMLBitVector result = arr1 & arr2;
		EXPECT_EQ(result.getBitVector(), std::vector<bool>({ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1 }));
	}

	/* CONVERSION TESTS */
	TEST(ConversionTest, VUIEInt32Test1) {
		BMLBitVector b(43807);
		uint32_t i = b.to_uint32();
		EXPECT_EQ(i, 43807);
	}

	TEST(ConversionTest, VUIEInt32Test2) {
		BMLBitVector b(std::vector<bool>({ 0, 0, 0, 1, 1, 1, 1, 1 }));
		uint32_t i = b.to_uint32();
		EXPECT_EQ(i, 31);
	}

	TEST(ConversionTest, VUIELargerThanInt32Test) {
		BMLBitVector b(31907359519);
		uint32_t i = b.to_uint32();
		EXPECT_EQ(i, 1842588447);
	}

	TEST(ConversionTest, VUIEInt64Test1) {
		BMLBitVector b(925260557087);
		uint64_t i = b.to_uint64();
		EXPECT_EQ(i, 925260557087);
	}

	TEST(ConversionTest, VUIEInt64Test2) {
		BMLBitVector b(117473493101343);
		uint64_t i = b.to_uint64();
		EXPECT_EQ(i, 117473493101343);
	}

	TEST(ConversionTest, VSIEPositiveInt32Test1) {
		BMLBitVector b(253, VSIE);
		int32_t i = b.to_int32();
		EXPECT_EQ(i, 253);
	}

	TEST(ConversionTest, VSIEPositiveInt32Test2) {
		BMLBitVector b(100000, VSIE);
		int32_t i = b.to_int32();
		EXPECT_EQ(i, 100000);
	}

	TEST(ConversionTest, VSIENegativeInt32Test1) {
		BMLBitVector b(-253, VSIE);
		int32_t i = b.to_int32();
		EXPECT_EQ(i, -253);
	}

	TEST(ConversionTest, VSIENegativeInt32Test2) {
		BMLBitVector b(-100000, VSIE);
		int32_t i = b.to_int32();
		EXPECT_EQ(i, -100000);
	}

	TEST(ConversionTest, VSIEPositiveInt64Test1) {
		BMLBitVector b(117473493101343);
		int64_t i = b.to_int64();
		EXPECT_EQ(i, 117473493101343);
	}

	TEST(ConversionTest, VSIEPositiveInt64Test2) {
		BMLBitVector b(15184315101500);
		int64_t i = b.to_int64();
		EXPECT_EQ(i, 15184315101500);
	}

	TEST(ConversionTest, VSIENegativeInt64Test1) {
		BMLBitVector b(-15184315101500);
		int64_t i = b.to_int64();
		EXPECT_EQ(i, -15184315101500);
	}

	TEST(ConversionTest, VSIENegativeInt64Test2) {
		BMLBitVector b(-117473493101343);
		int64_t i = b.to_int64();
		EXPECT_EQ(i, -117473493101343);
	}

	/* SHRINK TESTS */
	/*
	TEST(ShrinkTest, ShrinkableVector1) {
		BMLBitVector b(std::vector<bool>({ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0 }));
		bool success = b.shrink();
		EXPECT_EQ(success, true);
		EXPECT_EQ(b.getBitVector(), std::vector<bool>({ 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0 }));
	}

	TEST(ShrinkTest, ShrinkableVector2) {
		BMLBitVector b(std::vector<bool>({ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1 }));
		bool success = b.shrink();
		EXPECT_EQ(success, true);
		EXPECT_EQ(b.getBitVector(), std::vector<bool>({ 0, 0, 1, 1, 0, 1, 1, 1 }));
	}

	TEST(ShrinkTest, UnshrinkableVector1) {
		BMLBitVector b(std::vector<bool>({ 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0 }));
		bool success = b.shrink();
		EXPECT_EQ(success, true);
		EXPECT_EQ(b.getBitVector(), std::vector<bool>({ 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0 }));
	}
	*/
	/* EXTEND TESTS */
}