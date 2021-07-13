#include "gtest/gtest.h"
#include "bmltypes.h"
#include <limits.h>

namespace itmf {
// Encode tag tests
	TEST(EncodeTagTest, AllZeroTag) {
		std::vector<char> actual_tag = encodeTag(0, 0);
		std::vector<char> expected_tag = std::vector<char>({ 0x00 });
		EXPECT_EQ(actual_tag, expected_tag);
	}

	TEST(EncodeTagTest, SingleByteTag1) {
		std::vector<char> actual_tag = encodeTag(10, 3);

		std::vector<char> expected_tag = std::vector<char>({ 0b01010011 });
		EXPECT_EQ(actual_tag, expected_tag);
	}

	TEST(EncodeTagTest, SingleByteTag2) {
		std::vector<char> actual_tag = encodeTag(15, 6);
		std::vector<char> expected_tag = std::vector<char>({ 0b01111110 });
		EXPECT_EQ(actual_tag, expected_tag);
	}

	TEST(EncodeTagTest, SingleByteTag3) {
		std::vector<char> actual_tag = encodeTag(10, 1);
		std::vector<char> expected_tag = std::vector<char>({ 0b01010001 });
		EXPECT_EQ(actual_tag, expected_tag);
	}

	TEST(EncodeTagTest, MultiByteTag1) {
		std::vector<char> actual_tag = encodeTag(101, 6);
		size_t expected_size = 2;
		EXPECT_EQ(actual_tag.size(), expected_size);
		EXPECT_EQ(actual_tag[0], '\x83');
		EXPECT_EQ(actual_tag[1], '\x2E');
	}

	TEST(EncodeTagTest, MultiByteTag2) {
		std::vector<char> actual_tag = encodeTag(255, 1);
		size_t expected_size = 2;
		EXPECT_EQ(actual_tag.size(), expected_size);
		EXPECT_EQ(actual_tag[0], '\x87');
		EXPECT_EQ(actual_tag[1], '\xF9');
	}

	TEST(EncodeTagTest, MultiByteTag3) {
		std::vector<char> actual_tag = encodeTag(1000, 2);
		size_t expected_size = 2;
		EXPECT_EQ(actual_tag.size(), expected_size);
		EXPECT_EQ(actual_tag[0], '\x9F');
		EXPECT_EQ(actual_tag[1], '\x42');
	}

	TEST(EncodeTagTest, MultiByteTag4) {
		std::vector<char> actual_tag = encodeTag(20, 3);
		size_t expected_size = 2;
		EXPECT_EQ(actual_tag.size(), expected_size);
		EXPECT_EQ(actual_tag[0], '\x80');
		EXPECT_EQ(actual_tag[1], '\xA3');
	}
	
// Encoding tests

	// Int
	TEST(EncodeTest, BMLIntEncode1) {
		BMLint i(0, 1);
		std::vector<char> i_encoded = i.encode();
		EXPECT_EQ(i_encoded, std::vector<char>({ 0x02, 0x01 }));
	}

	TEST(EncodeTest, BMLIntEncode2) {
		BMLint i(0, -1);
		std::vector<char> i_encoded = i.encode();
		EXPECT_EQ(i_encoded, std::vector<char>({ 0x02, 0x41 }));
	}

	TEST(EncodeTest, BMLIntEncode3) {
		BMLint i(12, 63);
		std::vector<char> i_encoded = i.encode();
		EXPECT_EQ(i_encoded, std::vector<char>({ 0x62, 0x3F }));
	}

	TEST(EncodeTest, BMLIntEncode4) {
		BMLint i(32, -64);
		std::vector<char> i_encoded = i.encode();
		size_t expected_length = 4;
		EXPECT_EQ(i_encoded.size(), expected_length);
		EXPECT_EQ(i_encoded[0], '\x81');
		EXPECT_EQ(i_encoded[1], '\x02');
		EXPECT_EQ(i_encoded[2], '\xA0');
		EXPECT_EQ(i_encoded[3], '\x40');
	}

	// Long
	TEST(EncodeTest, BMLLongEncode1) {
		BMLlong l(1, 100000000000);
		std::vector<char> l_encoded = l.encode();
		size_t expected_length = 7;
		EXPECT_EQ(l_encoded.size(), expected_length);
		EXPECT_EQ(l_encoded[0], '\x0B');
		EXPECT_EQ(l_encoded[1], '\xF8');
		EXPECT_EQ(l_encoded[2], '\x17');
		EXPECT_EQ(l_encoded[3], '\x48');
		EXPECT_EQ(l_encoded[4], '\x76');
		EXPECT_EQ(l_encoded[5], '\xE8');
		EXPECT_EQ(l_encoded[6], '\x00');
	}

	// Single
	TEST(EncodeTest, BMLSingleEncode1) {
		BMLsingle s(1, 0.1f);
		std::vector<char> s_encoded = s.encode();
		size_t expected_length = 5;
		EXPECT_EQ(s_encoded.size(), expected_length);
		EXPECT_EQ(s_encoded[0], '\x0C');
		EXPECT_EQ(s_encoded[1], '\xCD');
		EXPECT_EQ(s_encoded[2], '\xCC');
		EXPECT_EQ(s_encoded[3], '\xCC');
		EXPECT_EQ(s_encoded[4], '\x3D');
	}

	TEST(EncodeTest, BMLSingleEncode2) {
		BMLsingle s(10, -0.1f);
		std::vector<char> s_encoded = s.encode();
		size_t expected_length = 5;
		EXPECT_EQ(s_encoded.size(), expected_length);
		EXPECT_EQ(s_encoded[0], '\x54');
		EXPECT_EQ(s_encoded[1], '\xCD');
		EXPECT_EQ(s_encoded[2], '\xCC');
		EXPECT_EQ(s_encoded[3], '\xCC');
		EXPECT_EQ(s_encoded[4], '\xBD');
	}

	TEST(EncodeTest, BMLSingleEncode3) {
		BMLsingle s(3, 123.456f);
		std::vector<char> s_encoded = s.encode();
		size_t expected_length = 5;
		EXPECT_EQ(s_encoded.size(), expected_length);
		EXPECT_EQ(s_encoded[0], '\x1C');
		EXPECT_EQ(s_encoded[1], '\x79');
		EXPECT_EQ(s_encoded[2], '\xE9');
		EXPECT_EQ(s_encoded[3], '\xF6');
		EXPECT_EQ(s_encoded[4], '\x42');
	}

	TEST(EncodeTest, BMLSingleEncodeMax) {
		BMLsingle s(3, 3.402823466e+38f);
		std::vector<char> s_encoded = s.encode();
		size_t expected_length = 5;
		EXPECT_EQ(s_encoded.size(), expected_length);
		EXPECT_EQ(s_encoded[0], '\x1C');
		EXPECT_EQ(s_encoded[1], '\xFF');
		EXPECT_EQ(s_encoded[2], '\xFF');
		EXPECT_EQ(s_encoded[3], '\x7F');
		EXPECT_EQ(s_encoded[4], '\x7F');
	}

	TEST(EncodeTest, BMLSingleEncodeMin) {
		BMLsingle s(3, -1.175494351e-38f);
		std::vector<char> s_encoded = s.encode();
		size_t expected_length = 5;
		EXPECT_EQ(s_encoded.size(), expected_length);
		EXPECT_EQ(s_encoded[0], '\x1C');
		EXPECT_EQ(s_encoded[1], '\x00');
		EXPECT_EQ(s_encoded[2], '\x00');
		EXPECT_EQ(s_encoded[3], '\x80');
		EXPECT_EQ(s_encoded[4], '\x80');
	}

	// Double
	TEST(EncodeTest, BMLDoubleEncode1) {

	}

	TEST(EncodeTest, BMLDoubleEncodeMax) {
		BMLdouble d(4, DBL_MAX);
		std::vector<char> d_encoded = d.encode();
		size_t expected_length = 9;
		EXPECT_EQ(d_encoded.size(), expected_length);
		EXPECT_EQ(d_encoded[0], '\x25');
		EXPECT_EQ(d_encoded[1], '\xFF');
		EXPECT_EQ(d_encoded[2], '\xFF');
		EXPECT_EQ(d_encoded[3], '\xFF');
		EXPECT_EQ(d_encoded[4], '\xFF');
		EXPECT_EQ(d_encoded[5], '\xFF');
		EXPECT_EQ(d_encoded[6], '\xFF');
		EXPECT_EQ(d_encoded[7], '\xEF');
		EXPECT_EQ(d_encoded[8], '\x7F');
	}

	TEST(EncodeTest, BMLDoubleEncodeMin) {
		BMLdouble d(1, -DBL_MIN);
		std::vector<char> d_encoded = d.encode();
		size_t expected_length = 9;
		EXPECT_EQ(d_encoded.size(), expected_length);
		EXPECT_EQ(d_encoded[0], '\x0D');
		EXPECT_EQ(d_encoded[1], '\x00');
		EXPECT_EQ(d_encoded[2], '\x00');
		EXPECT_EQ(d_encoded[3], '\x00');
		EXPECT_EQ(d_encoded[4], '\x00');
		EXPECT_EQ(d_encoded[5], '\x00');
		EXPECT_EQ(d_encoded[6], '\x00');
		EXPECT_EQ(d_encoded[7], '\x10');
		EXPECT_EQ(d_encoded[8], '\x80');
	}

	// Blob
	TEST(EncodeTest, BMLBlobEncode1) {

	}

	// Object

// Writing tests

// Reading tests

// Constructor test

// Conversion tests

// Operator tests
}