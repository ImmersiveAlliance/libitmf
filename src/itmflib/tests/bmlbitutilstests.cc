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
		EXPECT_EQ(a.getBitVector(), std::vector<bool>({ 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1 })); // 0x82, 0x19
	}

	TEST(ConstructorTest, VUIEInt32SpecTest4) {
		BMLBitVector a(100000);
		EXPECT_EQ(a.getBitVector(), std::vector<bool>({ 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 })); // 0xC1, 0x86, 0xA0
	}

	TEST(ConstructorTest, VSIEInt32SpecTest1) {
		BMLBitVector a(63, Encoding::VSIE);
		EXPECT_EQ(a.getBitVector(), std::vector<bool>({ 0, 0, 1, 1, 1, 1, 1, 1 })); // 0x3f
		EXPECT_EQ(a.getIsNegative(), false);
	}

	TEST(ConstructorTest, VSIEInt32SpecTest2) {
		BMLBitVector a(-64, Encoding::VSIE);
		EXPECT_EQ(a, BMLBitVector(std::vector<bool>({ 0, 1, 0, 0, 0, 0, 0, 0 }), Encoding::VSIE)); // 0x20, 0x40
		EXPECT_EQ(a.getIsNegative(), true);
	}

	TEST(ConstructorTest, VSIEInt32SpecTest3) {
		BMLBitVector a((int32_t)537, Encoding::VSIE);
		EXPECT_EQ(a, BMLBitVector(std::vector<bool>({ 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1 }), Encoding::VSIE)); // 0x02, 0x19
		EXPECT_EQ(a.getIsNegative(), false);
	}

	TEST(ConstructorTest, VSIEInt32SpecTest4) {
		BMLBitVector a((int32_t)-100000, Encoding::VSIE);
		EXPECT_EQ(a, BMLBitVector(std::vector<bool>({ 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 }), Encoding::VSIE)); // 0x11, 0x86, 0xA0
		EXPECT_EQ(a.getIsNegative(), true);
	}

	TEST(ConstructorTest, ComplexTest) {
		BMLBitVector a(2231902501);
		EXPECT_EQ(a.getBitVector(), std::vector<bool>({ 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0 , 1 }));
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
		EXPECT_EQ(arr.getBitVector(), BMLBitVector(295104).getBitVector());
	}

	TEST(LeftShiftTest, HandlesMultipleBytes2) {
		BMLBitVector arr(16312969);
		arr = arr << 3;
		EXPECT_EQ(arr.getBitVector(), BMLBitVector(13063240).getBitVector());
	}

	TEST(RightShiftTest, HandlesSingleByteMSB0) {
		BMLBitVector arr(72);
		arr = arr >> 3;
		EXPECT_EQ(arr.getBitVector(), BMLBitVector(9).getBitVector());
	}

	TEST(RightShiftTest, HandlesSingleByteMSB1) {
		BMLBitVector arr(137);
		arr = arr >> 3;
		EXPECT_EQ(arr.getBitVector(), BMLBitVector(241).getBitVector());
	}

	TEST(RightShiftTest, HandlesMultipleBytes1) {
		BMLBitVector arr(12619800);
		arr = arr >> 3;
		EXPECT_EQ(arr.getBitVector(), BMLBitVector(16257539).getBitVector());
	}

	TEST(RightShiftTest, HandlesMultipleBytes2) {
		BMLBitVector arr(2231902501);
		arr = arr >> 3;
		EXPECT_EQ(arr.getBitVector(), BMLBitVector(4037084196).getBitVector());
	}

	TEST(XorTest, SameLength) {
		BMLBitVector arr1(255);
		BMLBitVector arr2(85);
		BMLBitVector result = arr1 ^ arr2;
		EXPECT_EQ(result.getBitVector(), BMLBitVector(170).getBitVector());
	}

	TEST(XorTest, DifferentLengths1) {
		BMLBitVector arr1(511);
		BMLBitVector arr2(85);
		BMLBitVector result = arr1 ^ arr2;
		EXPECT_EQ(result.getBitVector(), std::vector<bool>({ 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0 }));
	}

	TEST(XorTest, DifferentLengths2) {
		BMLBitVector arr1(255);
		BMLBitVector arr2(25941);
		BMLBitVector result = arr1 ^ arr2;
		EXPECT_EQ(result.getBitVector(), std::vector<bool>({ 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0 }));
	}

	TEST(OrTest, SameLength) {
		BMLBitVector arr1(255);
		BMLBitVector arr2(85);
		BMLBitVector result = arr1 | arr2;
		EXPECT_EQ(result.getBitVector(), BMLBitVector(255).getBitVector());
	}

	TEST(OrTest, DifferentLengths1) {
		BMLBitVector arr1(255);
		BMLBitVector arr2(1365);
		BMLBitVector result = arr1 | arr2;
		EXPECT_EQ(result.getBitVector(), BMLBitVector(1535).getBitVector());
	}

	TEST(OrTest, DifferentLengths2) {
		BMLBitVector arr1(511);
		BMLBitVector arr2(85);
		BMLBitVector result = arr1 | arr2;
		EXPECT_EQ(result.getBitVector(), BMLBitVector(511).getBitVector());
	}

	TEST(AndTest, SameLength) {
		BMLBitVector arr1(255);
		BMLBitVector arr2(85);
		BMLBitVector result = arr1 & arr2;
		EXPECT_EQ(result.getBitVector(), BMLBitVector(85).getBitVector());
	}

	TEST(AndTest, DifferentLengths1) {
		BMLBitVector arr1(255);
		BMLBitVector arr2(1365);
		BMLBitVector result = arr1 & arr2;
		EXPECT_EQ(result.getBitVector(), std::vector<bool>({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1 }));
	}

	TEST(AndTest, DifferentLengths2) {
		BMLBitVector arr1(511);
		BMLBitVector arr2(85);
		BMLBitVector result = arr1 & arr2;
		EXPECT_EQ(result.getBitVector(), std::vector<bool>({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1 }));
	}

	/* PREPARING ENCODING TESTS */
	TEST(PrepareEncodingTest, VUIESingleByte1) {
		BMLBitVector b(63);
		b.prepareForEncoding();
		EXPECT_EQ(b.getBitVector(), std::vector<bool>({ 0, 0, 1, 1, 1, 1, 1, 1 }));
	}

	TEST(PrepareEncodingTest, VUIESingleByte2) {
		BMLBitVector b(64);
		b.prepareForEncoding();
		EXPECT_EQ(b.getBitVector(), std::vector<bool>({ 0, 1, 0, 0, 0, 0, 0, 0 }));
	}

	TEST(PrepareEncodingTest, VSIESingleByte1) {
		BMLBitVector b(-3, VSIE);
		b.prepareForEncoding();
		EXPECT_EQ(b.getBitVector(), std::vector<bool>({ 0, 1, 0, 0, 0, 0, 1, 1 }));
	}

	TEST(PrepareEncodingTest, VSIESingleByte2) {
		BMLBitVector b(20, VSIE);
		b.prepareForEncoding();
		EXPECT_EQ(b.getBitVector(), std::vector<bool>({ 0, 0, 0, 1, 0, 1, 0, 0 }));
	}

	TEST(PrepareEncodingTest, VUIEMultiByteNoExtension1) {
		BMLBitVector b(537);
		b.prepareForEncoding();
		EXPECT_EQ(b.getBitVector(), std::vector<bool>({ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1 }));
	}

	TEST(PrepareEncodingTest, VUIEMultiByteNoExtension2) {
		BMLBitVector b(100000);
		b.prepareForEncoding();
		EXPECT_EQ(b.getBitVector(), std::vector<bool>({ 1,1,0,0,0,0,0,1,1,0,0,0,0,1,1,0,1,0,1,0,0,0,0,0 }));
	}

	TEST(PrepareEncodingTest, VSIEMultiByteNoExtension1) {
		BMLBitVector b(-537, VSIE);
		b.prepareForEncoding();
		EXPECT_EQ(b.getBitVector(), std::vector<bool>({ 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1 }));
	}

	TEST(PrepareEncodingTest, VSIEMultiByteNoExtension2) {
		BMLBitVector b(-100000, VSIE);
		b.prepareForEncoding();
		EXPECT_EQ(b.getBitVector(), std::vector<bool>({ 1,1,0,1,0,0,0,1,1,0,0,0,0,1,1,0,1,0,1,0,0,0,0,0 }));
	}

	TEST(PrepareEncodingTest, VSIESingleByteExtension) {
		BMLBitVector b(-64, VSIE);
		b.prepareForEncoding();
		EXPECT_EQ(b.getBitVector(), std::vector<bool>({ 1,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0 }));
	}

	TEST(PrepareEncodingTest, VUIEMultiByteExtension1) {
		BMLBitVector b(16981570985633284152);
		b.prepareForEncoding();
		EXPECT_EQ(b.getBitVector(), std::vector<bool>({ 1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,1,0,1,0,1,1,0,1,1,0,1,0,1,1,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0 }));
	}

	TEST(PrepareEncodingTest, VUIEMultiByteExtension2) {
		BMLBitVector b(12615736);
		b.prepareForEncoding();
		EXPECT_EQ(b.getBitVector(), std::vector<bool>({ 1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0 }));
	}

	TEST(PrepareEncodingTest, VSIEMultiByteExtension1) {
		BMLBitVector b(-48036386720219192, VSIE);
		b.prepareForEncoding();
		EXPECT_EQ(b.getBitVector(), std::vector<bool>({ 1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,1,0,1,0,1,1,0,1,1,0,1,0,1,1,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0 }));
	}

	TEST(PrepareEncodingTest, VSIEMultiByteExtension2) {
		BMLBitVector b(-12615736, VSIE);
		b.prepareForEncoding();
		EXPECT_EQ(b.getBitVector(), std::vector<bool>({ 1,1,1,0,1,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0 }));
	}

	/* CONVERSION TESTS */

	TEST(ConversionTest, VUIEInt32Test1) {
		BMLBitVector b(std::vector<bool>({ 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1 }));
		uint32_t i = b.to_uint32();
		EXPECT_EQ(i, 43807);
	}

	TEST(ConversionTest, VUIEInt32Test2) {
		BMLBitVector b(std::vector<bool>({ 0, 0, 0, 1, 1, 1, 1, 1 }));
		uint32_t i = b.to_uint32();
		EXPECT_EQ(i, 31);
	}

	TEST(ConversionTest, VUIELargerThanInt32Test) {
		BMLBitVector b(std::vector<bool>({ 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1 }));
		uint32_t i = b.to_uint32();
		EXPECT_EQ(i, 1842588447);
	}

	TEST(ConversionTest, VUIEInt64Test1) {
		BMLBitVector b(std::vector<bool>({ 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1 }));
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

	/* ENCODING TAGS TEST */

	TEST(EncodingTagsTest, SingleByteTag1) {
		BMLBitVector b;
		b.encodeTag(3, 6);
		EXPECT_EQ(b.getBitVector(), std::vector<bool>({ 0, 0, 0, 1, 1, 1, 1, 0 }));
	}

	TEST(EncodingTagsTest, SingleByteTag2) {
		BMLBitVector b;
		b.encodeTag(30, 2);
		EXPECT_EQ(b.getBitVector(), std::vector<bool>({ 1, 1, 1, 1, 0, 0, 1, 0 }));
	}
}