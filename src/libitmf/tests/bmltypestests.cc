#include <limits.h>
#include <cmath>

#include "gtest/gtest.h"
#include "bmltypes.h"
#include "itmfenums.h"

namespace itmf {
// Encode tag tests
	TEST(EncodeTagTest, AllZeroTagTest) {
		std::vector<char> actual_tag = encodeTag(0, 0);
		std::vector<char> expected_tag = std::vector<char>({ 0x00 });
		EXPECT_EQ(actual_tag, expected_tag);
	}

	TEST(EncodeTagTest, SingleByteTagTest1) {
		std::vector<char> actual_tag = encodeTag(10, 3);

		std::vector<char> expected_tag = std::vector<char>({ 0b01010011 });
		EXPECT_EQ(actual_tag, expected_tag);
	}

	TEST(EncodeTagTest, SingleByteTagTest2) {
		std::vector<char> actual_tag = encodeTag(15, 6);
		std::vector<char> expected_tag = std::vector<char>({ 0b01111110 });
		EXPECT_EQ(actual_tag, expected_tag);
	}

	TEST(EncodeTagTest, SingleByteTagTest3) {
		std::vector<char> actual_tag = encodeTag(10, 1);
		std::vector<char> expected_tag = std::vector<char>({ 0b01010001 });
		EXPECT_EQ(actual_tag, expected_tag);
	}

	TEST(EncodeTagTest, MultiByteTagTest1) {
		std::vector<char> actual_tag = encodeTag(101, 6);
		size_t expected_size = 2;
		unsigned char expected_tag[] = { 0x83, 0x2E };
		EXPECT_EQ(actual_tag.size(), expected_size);
		EXPECT_EQ(actual_tag[0], '\x83');
		EXPECT_EQ(actual_tag[1], '\x2E');
	}

	TEST(EncodeTagTest, MultiByteTagTest2) {
		std::vector<char> actual_tag = encodeTag(255, 1);
		size_t expected_size = 2;
		EXPECT_EQ(actual_tag.size(), expected_size);
		EXPECT_EQ(actual_tag[0], '\x87');
		EXPECT_EQ(actual_tag[1], '\xF9');
	}

	TEST(EncodeTagTest, MultiByteTagTest3) {
		std::vector<char> actual_tag = encodeTag(1000, 2);
		size_t expected_size = 2;
		EXPECT_EQ(actual_tag.size(), expected_size);
		EXPECT_EQ(actual_tag[0], '\x9F');
		EXPECT_EQ(actual_tag[1], '\x42');
	}

	TEST(EncodeTagTest, MultiByteTagTest4) {
		std::vector<char> actual_tag = encodeTag(20, 3);
		size_t expected_size = 2;
		EXPECT_EQ(actual_tag.size(), expected_size);
		EXPECT_EQ(actual_tag[0], '\x80');
		EXPECT_EQ(actual_tag[1], '\xA3');
	}
	
// Encoding tests

	// Int
	TEST(EncodeTest, BMLIntEncodeTest1) {
		BMLint i(0, 1);
		std::vector<char> i_encoded = i.encode();
		EXPECT_EQ(i_encoded, std::vector<char>({ 0x02, 0x01 }));
	}

	TEST(EncodeTest, BMLIntEncodeTest2) {
		BMLint i(0, -1);
		std::vector<char> i_encoded = i.encode();
		EXPECT_EQ(i_encoded, std::vector<char>({ 0x02, 0x41 }));
	}

	TEST(EncodeTest, BMLIntEncodeTest3) {
		BMLint i(12, 63);
		std::vector<char> i_encoded = i.encode();
		EXPECT_EQ(i_encoded, std::vector<char>({ 0x62, 0x3F }));
	}

	TEST(EncodeTest, BMLIntEncodeTest4) {
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
	TEST(EncodeTest, BMLLongEncodeTest1) {
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
	TEST(EncodeTest, BMLSingleEncodeTest1) {
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

	TEST(EncodeTest, BMLSingleEncodeTest2) {
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

	TEST(EncodeTest, BMLSingleEncodeTest3) {
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

	TEST(EncodeTest, BMLSingleEncodeMaxTest) {
		BMLsingle s(3, FLT_MAX);
		std::vector<char> s_encoded = s.encode();
		size_t expected_length = 5;
		EXPECT_EQ(s_encoded.size(), expected_length);
		EXPECT_EQ(s_encoded[0], '\x1C');
		EXPECT_EQ(s_encoded[1], '\xFF');
		EXPECT_EQ(s_encoded[2], '\xFF');
		EXPECT_EQ(s_encoded[3], '\x7F');
		EXPECT_EQ(s_encoded[4], '\x7F');
	}

	TEST(EncodeTest, BMLSingleEncodeMinTest) {
		BMLsingle s(3, -FLT_MIN);
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
	TEST(EncodeTest, BMLDoubleEncodeTest1) {
		BMLdouble d(6, 5.0e50);
		std::vector<char> d_encoded = d.encode(); // 4A7561D276DDFDC0
		size_t expected_length = 9;
		EXPECT_EQ(d_encoded.size(), expected_length);
		EXPECT_EQ(d_encoded[0], '\x35');
		EXPECT_EQ(d_encoded[1], '\xC0');
		EXPECT_EQ(d_encoded[2], '\xFD');
		EXPECT_EQ(d_encoded[3], '\xDD');
		EXPECT_EQ(d_encoded[4], '\x76');
		EXPECT_EQ(d_encoded[5], '\xD2');
		EXPECT_EQ(d_encoded[6], '\x61');
		EXPECT_EQ(d_encoded[7], '\x75');
		EXPECT_EQ(d_encoded[8], '\x4A');
	}

	TEST(EncodeTest, BMLDoubleEncodeMaxTest) {
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

	TEST(EncodeTest, BMLDoubleEncodeMinTest) {
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

	// String
	TEST(EncodeTest, BMLStringEmptyTest) {
		std::string text("");
		BMLstring s(3, text);
		std::vector<char> s_encoded = s.encode();
		size_t expected_length = 2;
		EXPECT_EQ(s_encoded.size(), expected_length);
		std::vector<char> expected_encode = { 0x1E, 0x00 };
		EXPECT_EQ(s_encoded, expected_encode);
	}

	TEST(EncodeTest, BMLStringTest1) {
		std::string text("Test BML String");
		BMLstring s(3, text);
		std::vector<char> s_encoded = s.encode();
		size_t expected_length = 17;
		EXPECT_EQ(s_encoded.size(), expected_length);
		std::vector<char> expected_encode = { 0x1E, 0x0F, 'T', 'e', 's', 't', ' ', 'B', 'M', 'L', ' ', 'S', 't', 'r', 'i', 'n', 'g' };
		EXPECT_EQ(s_encoded, expected_encode);
	}

	TEST(EncodeTest, BMLStringTest2) {
		std::string text("Test BML \0 String", 17);
		BMLstring s(3, text);
		std::vector<char> s_encoded = s.encode();
		size_t expected_length = 19;
		EXPECT_EQ(s_encoded.size(), expected_length);
		std::vector<char> expected_encode = { 0x1E, 0x11, 'T', 'e', 's', 't', ' ', 'B', 'M', 'L', ' ', '\0', ' ', 'S', 't', 'r', 'i', 'n', 'g' };
		EXPECT_EQ(s_encoded, expected_encode);
	}

	// Blob
	TEST(EncodeTest, BMLBlobEmptyTest) {
		BMLblob b;
		std::vector<char> b_encoded = b.encode();
		size_t expected_length = 2;
		EXPECT_EQ(b_encoded.size(), expected_length);
		EXPECT_EQ(b_encoded[0], 0x07);
		EXPECT_EQ(b_encoded[1], 0x00);
	}
	
	TEST(EncodeTest, BMLBlobEncodeTest1) {
		char* blob = new char[6];
		strcpy(blob, "hello");
		std::shared_ptr<char> actual_blob(blob, std::default_delete<char[]>());
		BMLblob b(3, 6, actual_blob);
		std::vector<char> b_encoded = b.encode();
		size_t expected_length = 2;
		EXPECT_EQ(b_encoded.size(), expected_length);
		EXPECT_EQ(b_encoded[0], 0x1F);
		EXPECT_EQ(b_encoded[1], 0x06);
	}
	
	// Object (open and close tags)
	TEST(EncodeTest, BMLObjectOpenCloseTagTest1) {
		BMLobject o(1);
		std::vector<char> opentag = o.encodeOpenTag();
		std::vector<char> closetag = o.encodeCloseTag();
		std::vector<char> expected_opentag = { 0x09 };
		std::vector<char> expected_closetag = { 0x08 };
		EXPECT_EQ(opentag, expected_opentag);
		EXPECT_EQ(closetag, expected_closetag);
	}

// Writing tests
	TEST(WriteTest, BMLIntWriteTest1) {
		std::stringstream expected_ostream;
		unsigned char output_data[] = { 0x02, 0x01 };
		expected_ostream.write(reinterpret_cast<char*>(output_data), sizeof(output_data));
		
		std::stringstream test_ostream;
		BMLint i(0, 1);
		i.save(test_ostream);
		EXPECT_EQ(test_ostream.str(), expected_ostream.str());
	}

	TEST(WriteTest, BMLLongWriteTest1) {
		std::stringstream expected_ostream;
		unsigned char output_data[] = { 0x0B, 0xF8, 0x17, 0x48, 0x76, 0xE8, 0x00 };
		expected_ostream.write(reinterpret_cast<char*>(output_data), sizeof(output_data));

		std::stringstream test_ostream;

		BMLlong l(1, 100000000000);
		l.save(test_ostream);
		EXPECT_EQ(test_ostream.str(), expected_ostream.str());
	}

	TEST(WriteTest, BMLSingleWriteTest1) {
		std::stringstream expected_ostream;
		unsigned char output_data[] = { 0x0C, 0xCD, 0xCC, 0xCC, 0x3D };
		expected_ostream.write(reinterpret_cast<char*>(output_data), sizeof(output_data));

		std::stringstream test_ostream;

		BMLsingle s(1, 0.1f);
		s.save(test_ostream);
		EXPECT_EQ(test_ostream.str(), expected_ostream.str());
	}

	TEST(WriteTest, BMLDoubleWriteTest1) {
		std::stringstream expected_ostream;
		unsigned char output_data[] = { 0x35, 0xC0, 0xFD, 0xDD, 0x76, 0xD2, 0x61, 0x75, 0x4A };
		expected_ostream.write(reinterpret_cast<char*>(output_data), sizeof(output_data));

		std::stringstream test_ostream;

		BMLdouble d(6, 5.0e50);
		d.save(test_ostream);
		EXPECT_EQ(test_ostream.str(), expected_ostream.str());
	}

	TEST(WriteTest, BMLStringWriteTest1) {
		std::stringstream expected_ostream;
		unsigned char output_data[] = { 0x1E, 0x0F, 'T', 'e', 's', 't', ' ', 'B', 'M', 'L', ' ', 'S', 't', 'r', 'i', 'n', 'g' };
		expected_ostream.write(reinterpret_cast<char*>(output_data), sizeof(output_data));

		std::stringstream test_ostream;

		std::string text("Test BML String");
		BMLstring s(3, text);
		s.save(test_ostream);
		EXPECT_EQ(test_ostream.str(), expected_ostream.str());
	}

	TEST(WriteTest, BMLStringWriteTest2) {
		std::stringstream expected_ostream;
		unsigned char output_data[] = { 0x1E, 0x11, 'T', 'e', 's', 't', ' ', 'B', 'M', 'L', ' ', '\0', ' ', 'S', 't', 'r', 'i', 'n', 'g' };
		expected_ostream.write(reinterpret_cast<char*>(output_data), sizeof(output_data));

		std::stringstream test_ostream;

		std::string text("Test BML \0 String", 17);
		BMLstring s(3, text);
		s.save(test_ostream);
		EXPECT_EQ(test_ostream.str(), expected_ostream.str());
	}

	TEST(WriteTest, BMLBlobWriteTest1) {
		std::stringstream expected_ostream;
		unsigned char output_data[] = { 0x1F, 0x06, 'h', 'e', 'l', 'l', 'o', '\0' };
		expected_ostream.write(reinterpret_cast<char*>(output_data), sizeof(output_data));

		std::stringstream test_ostream;

		char* blob = new char[6];
		strcpy(blob, "hello");
		std::shared_ptr<char> actual_blob(blob, std::default_delete<char[]>());
		BMLblob b(3, 6, actual_blob);
		b.save(test_ostream);
		EXPECT_EQ(test_ostream.str(), expected_ostream.str());
	}

// Reading tests
	TEST(ReadTest, ReadVUIETest1) {
		std::stringstream test_istream;
		unsigned char input_data[] = { 0x3f };
		uint64_t expected_value = 63;

		test_istream.write(reinterpret_cast<char*>(input_data), sizeof(input_data));

		std::streampos begin_streampos = test_istream.tellg();
		BMLBitVector result = readVUIE(test_istream);
		std::streampos end_streampos = test_istream.tellg();

		EXPECT_EQ(result.to_uint64(), expected_value);
		std::streamoff stream_offset = end_streampos - begin_streampos;
		EXPECT_EQ(stream_offset, sizeof(input_data));
	}

	TEST(ReadTest, ReadVUIETest2) {
		std::stringstream test_istream;
		unsigned char input_data[] = { 0x40 };
		uint64_t expected_value = 64;

		test_istream.write(reinterpret_cast<char*>(input_data), sizeof(input_data));

		BMLBitVector result = readVUIE(test_istream);

		EXPECT_EQ(result.to_uint64(), expected_value);
	}

	TEST(ReadTest, ReadVUIETest3) {
		std::stringstream test_istream;
		unsigned char input_data[] = { 0x82, 0x19 };
		uint64_t expected_value = 537;

		test_istream.write(reinterpret_cast<char*>(input_data), sizeof(input_data));

		BMLBitVector result = readVUIE(test_istream);

		EXPECT_EQ(result.to_uint64(), expected_value);
	}

	TEST(ReadTest, ReadVUIETest4) {
		std::stringstream test_istream;
		unsigned char input_data[] = { 0xc1, 0x86, 0xa0 };
		uint64_t expected_value = 100000;

		test_istream.write(reinterpret_cast<char*>(input_data), sizeof(input_data));

		BMLBitVector result = readVUIE(test_istream);

		EXPECT_EQ(result.to_uint64(), expected_value);
	}

	TEST(ReadTest, ReadVSIETest1) {
		std::stringstream test_istream;
		unsigned char input_data[] = { 0x3f };
		int64_t expected_value = 63;

		test_istream.write(reinterpret_cast<char*>(input_data), sizeof(input_data));

		BMLBitVector result = readVSIE(test_istream);

		EXPECT_EQ(result.to_int64(), expected_value);
	}

	TEST(ReadTest, ReadVSIETest2) {
		std::stringstream test_istream;
		unsigned char input_data[] = { 0xa0, 0x40 };
		int64_t expected_value = -64;

		test_istream.write(reinterpret_cast<char*>(input_data), sizeof(input_data));

		BMLBitVector result = readVSIE(test_istream);

		EXPECT_EQ(result.to_int64(), expected_value);
	}

	TEST(ReadTest, ReadVSIETest3) {
		std::stringstream test_istream;
		unsigned char input_data[] = { 0x82, 0x19 };
		int64_t expected_value = 537;

		test_istream.write(reinterpret_cast<char*>(input_data), sizeof(input_data));

		BMLBitVector result = readVSIE(test_istream);

		EXPECT_EQ(result.to_int64(), expected_value);
	}

	TEST(ReadTest, ReadVSIETest4) {
		std::stringstream test_istream;
		unsigned char input_data[] = { 0xd1, 0x86, 0xa0 };
		int64_t expected_value = -100000;

		test_istream.write(reinterpret_cast<char*>(input_data), sizeof(input_data));

		BMLBitVector result = readVSIE(test_istream);

		EXPECT_EQ(result.to_int64(), expected_value);
	}

// Decoding tests

	TEST(ReadTest, DecodeTagTest1) {
		std::stringstream test_istream;
		unsigned char input_data[] = { 0b00010010 };
		int expected_id = 2;
		int expected_type = 2;
		int actual_id, actual_type;

		test_istream.write(reinterpret_cast<char*>(input_data), sizeof(input_data));

		std::streampos begin_streampos = test_istream.tellg();
		decodeTag(test_istream, actual_id, actual_type);
		std::streampos end_streampos = test_istream.tellg();

		std::streamoff stream_offset = end_streampos - begin_streampos;
		EXPECT_EQ(actual_id, expected_id);
		EXPECT_EQ(actual_type, expected_type);
		EXPECT_EQ(stream_offset, sizeof(input_data));
	}

	TEST(ReadTest, DecodeTagTest2) {
		std::stringstream test_istream;
		unsigned char input_data[] = { 0b10100000, 0b00000010 };
		int expected_id = 1024;
		int expected_type = 2;
		int actual_id, actual_type;

		test_istream.write(reinterpret_cast<char*>(input_data), sizeof(input_data));

		std::streampos begin_streampos = test_istream.tellg();
		decodeTag(test_istream, actual_id, actual_type);
		std::streampos end_streampos = test_istream.tellg();

		std::streamoff stream_offset = end_streampos - begin_streampos;
		EXPECT_EQ(actual_id, expected_id);
		EXPECT_EQ(actual_type, expected_type);
		EXPECT_EQ(stream_offset, sizeof(input_data));
	}

	TEST(ReadTest, DecodeTagTest3) {
		std::stringstream test_istream;
		unsigned char input_data[] = { 0b10100000, 0b00000111 };
		int expected_id = 1024;
		int expected_type = 7;
		int actual_id, actual_type;

		test_istream.write(reinterpret_cast<char*>(input_data), sizeof(input_data));

		std::streampos begin_streampos = test_istream.tellg();
		decodeTag(test_istream, actual_id, actual_type);
		std::streampos end_streampos = test_istream.tellg();

		std::streamoff stream_offset = end_streampos - begin_streampos;
		EXPECT_EQ(actual_id, expected_id);
		EXPECT_EQ(actual_type, expected_type);
		EXPECT_EQ(stream_offset, sizeof(input_data));
	}

	TEST(ReadTest, DecodeTagTest4) {
		std::stringstream test_istream;
		unsigned char input_data[] = { 0 };
		int expected_id = 0;
		int expected_type = 0;
		int actual_id, actual_type;

		test_istream.write(reinterpret_cast<char*>(input_data), sizeof(input_data));

		std::streampos begin_streampos = test_istream.tellg();
		decodeTag(test_istream, actual_id, actual_type);
		std::streampos end_streampos = test_istream.tellg();

		std::streamoff stream_offset = end_streampos - begin_streampos;
		EXPECT_EQ(actual_id, expected_id);
		EXPECT_EQ(actual_type, expected_type);
		EXPECT_EQ(stream_offset, sizeof(input_data));
	}

	TEST(ReadTest, PeekTagTest) {
		std::stringstream test_istream;
		unsigned char input_data[] = { 0b10100000, 0b00000111 };
		int expected_id = 1024;
		int expected_type = 7;
		int actual_id, actual_type;

		test_istream.write(reinterpret_cast<char*>(input_data), sizeof(input_data));

		std::streampos expected_streampos = test_istream.tellg();
		peekTag(test_istream, actual_id, actual_type);
		std::streampos actual_streampos = test_istream.tellg();

		EXPECT_EQ(actual_id, expected_id);
		EXPECT_EQ(actual_type, expected_type);
		EXPECT_EQ(actual_streampos, expected_streampos);
	}

	TEST(ReadTest, ReadBMLintTest1) {
		std::stringstream test_istream;
		unsigned char input_data[] = { 0b00010000 };
		int expected_value = 16;

		test_istream.write(reinterpret_cast<char*>(input_data), sizeof(input_data));

		BMLint test_int;
		test_int.parse(test_istream);

		EXPECT_EQ(test_int.getValue(), expected_value);
	}

	TEST(ReadTest, ReadBMLintTest2) {
		std::stringstream test_istream;
		unsigned char input_data[] = { 0b01010000 };
		int expected_value = -16;

		test_istream.write(reinterpret_cast<char*>(input_data), sizeof(input_data));

		BMLint test_int;
		test_int.parse(test_istream);

		EXPECT_EQ(test_int.getValue(), expected_value);
	}

	TEST(ReadTest, ReadBMLlongTest1) {
		std::stringstream test_istream;
		unsigned char input_data[] = { 0b00010000 };
		long expected_value = 16;

		test_istream.write(reinterpret_cast<char*>(input_data), sizeof(input_data));

		BMLlong test_long;
		test_long.parse(test_istream);

		EXPECT_EQ(test_long.getValue(), expected_value);
	}

	TEST(ReadTest, ReadBMLlongTest2) {
		std::stringstream test_istream;
		unsigned char input_data[] = { 0b01010000 };
		long expected_value = -16;

		test_istream.write(reinterpret_cast<char*>(input_data), sizeof(input_data));

		BMLlong test_long;
		test_long.parse(test_istream);

		EXPECT_EQ(test_long.getValue(), expected_value);
	}

	TEST(ReadTest, ReadBMLsingleTest1) {
		std::stringstream test_istream;
		unsigned char input_data[] = { 0x00, 0x00, 0x00, 0x40 };
		float expected_value = 2.0f;

		test_istream.write(reinterpret_cast<char*>(input_data), sizeof(input_data));

		BMLsingle test_single;
		test_single.parse(test_istream);

		EXPECT_EQ(test_single.getValue(), expected_value);
	}

	TEST(ReadTest, ReadBMLsingleTest2) {
		std::stringstream test_istream;
		unsigned char input_data[] = { 0x00, 0x00, 0x00, 0xC0 };
		float expected_value = -2.0f;

		test_istream.write(reinterpret_cast<char*>(input_data), sizeof(input_data));

		BMLsingle test_single;
		test_single.parse(test_istream);

		EXPECT_EQ(test_single.getValue(), expected_value);
	}

	TEST(ReadTest, ReadBMLsingleTest3) {
		std::stringstream test_istream;
		unsigned char input_data[] = { 0x00, 0x00, 0xc0, 0x40 };
		float expected_value = 6.0f;

		test_istream.write(reinterpret_cast<char*>(input_data), sizeof(input_data));

		BMLsingle test_single;
		test_single.parse(test_istream);

		EXPECT_EQ(test_single.getValue(), expected_value);
	}

	TEST(ReadTest, ReadBMLsingleTest4) {
		std::stringstream test_istream;
		unsigned char input_data[] = { 0x00, 0x00, 0x80, 0x3e };
		float expected_value = 0.25;

		test_istream.write(reinterpret_cast<char*>(input_data), sizeof(input_data));

		BMLsingle test_single;
		test_single.parse(test_istream);

		EXPECT_EQ(test_single.getValue(), expected_value);
	}

	TEST(ReadTest, ReadBMLsingleTest5) {
		std::stringstream test_istream;
		unsigned char input_data[] = { 0x00, 0x00, 0xc0, 0x7f };

		test_istream.write(reinterpret_cast<char*>(input_data), sizeof(input_data));

		BMLsingle test_single;
		test_single.parse(test_istream);

		EXPECT_TRUE(std::isnan(test_single.getValue()));
	}

	TEST(ReadTest, ReadBMLsingleTest6) {
		std::stringstream test_istream;
		unsigned char input_data[] = { 0x00, 0x00, 0x80, 0x7f };

		test_istream.write(reinterpret_cast<char*>(input_data), sizeof(input_data));

		BMLsingle test_single;
		test_single.parse(test_istream);

		EXPECT_TRUE(std::isinf(test_single.getValue()));
	}

	TEST(ReadTest, ReadBMLdoubleTest1) {
		std::stringstream test_istream;
		unsigned char input_data[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40 };
		float expected_value = 2.0;

		test_istream.write(reinterpret_cast<char*>(input_data), sizeof(input_data));

		BMLdouble test_double;
		test_double.parse(test_istream);

		EXPECT_EQ(test_double.getValue(), expected_value);
	}

	TEST(ReadTest, ReadBMLdoubleTest2) {
		std::stringstream test_istream;
		unsigned char input_data[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0 };
		float expected_value = -2.0;

		test_istream.write(reinterpret_cast<char*>(input_data), sizeof(input_data));

		BMLdouble test_double;
		test_double.parse(test_istream);

		EXPECT_EQ(test_double.getValue(), expected_value);
	}

	TEST(ReadTest, ReadBMLdoubleTest3) {
		std::stringstream test_istream;
		unsigned char input_data[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x40 };
		float expected_value = 6.0;

		test_istream.write(reinterpret_cast<char*>(input_data), sizeof(input_data));

		BMLdouble test_double;
		test_double.parse(test_istream);

		EXPECT_EQ(test_double.getValue(), expected_value);
	}

	TEST(ReadTest, ReadBMLdoubleTest4) {
		std::stringstream test_istream;
		unsigned char input_data[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd0, 0x3f };
		float expected_value = 0.25;

		test_istream.write(reinterpret_cast<char*>(input_data), sizeof(input_data));

		BMLdouble test_double;
		test_double.parse(test_istream);

		EXPECT_EQ(test_double.getValue(), expected_value);
	}

	TEST(ReadTest, ReadBMLdoubleTest5) {
		std::stringstream test_istream;
		unsigned char input_data[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x7f };

		test_istream.write(reinterpret_cast<char*>(input_data), sizeof(input_data));

		BMLdouble test_double;
		test_double.parse(test_istream);

		EXPECT_TRUE(std::isnan(test_double.getValue()));
	}

	TEST(ReadTest, ReadBMLdoubleTest6) {
		std::stringstream test_istream;
		unsigned char input_data[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x7f };

		test_istream.write(reinterpret_cast<char*>(input_data), sizeof(input_data));

		BMLdouble test_double;
		test_double.parse(test_istream);

		EXPECT_TRUE(std::isinf(test_double.getValue()));
	}

	TEST(ReadTest, ReadBMLstringTest1) {
		std::stringstream test_istream;
		unsigned char length_vuie[] = { 0b00001111 };
		std::string text("Test BML String");

		test_istream.write(reinterpret_cast<char*>(length_vuie), sizeof(length_vuie));
		test_istream.write(&text[0], text.size());

		BMLstring test_string;
		test_string.parse(test_istream);

		EXPECT_EQ(test_string.getValue(), text);
	}

	TEST(ReadTest, ReadBMLstringTest2) {
		std::stringstream test_istream;
		unsigned char length_vuie[] = { 0b00010001 };
		std::string text("Test BML \0 String", 17);

		test_istream.write(reinterpret_cast<char*>(length_vuie), sizeof(length_vuie));
		test_istream.write(&text[0], text.size());

		BMLstring test_string;
		test_string.parse(test_istream);

		EXPECT_EQ(test_string.getValue(), text);
	}

	TEST(ReadTest, ReadBMLblobTest1) {
		std::stringstream test_istream;
		unsigned char length_vuie[] = { 0b00000001 };
		unsigned char data[] = { 0b00010001 };

		test_istream.write(reinterpret_cast<char*>(length_vuie), sizeof(length_vuie));
		test_istream.write(reinterpret_cast<char*>(data), sizeof(data));

		BMLblob test_blob;
		test_blob.parse(test_istream);

		std::shared_ptr<char> result = test_blob.getValue();

		EXPECT_EQ(test_blob.length, sizeof(data));
		for (size_t i = 0; i < sizeof(data); ++i) {
			EXPECT_EQ(result.get()[i], data[i]) << "The parsed blob differs from the test data at index " << i;
		}
	}

	TEST(ReadTest, ReadBMLblobTest2) {
		std::stringstream test_istream;
		unsigned char length_vuie[] = { 0b00000100 };
		unsigned char data[] = { 0b11111111, 0b00000000, 0b11111111, 0b00000000 };

		test_istream.write(reinterpret_cast<char*>(length_vuie), sizeof(length_vuie));
		test_istream.write(reinterpret_cast<char*>(data), sizeof(data));

		BMLblob test_blob;
		test_blob.parse(test_istream);

		std::shared_ptr<char> result = test_blob.getValue();

		char* expected_result = reinterpret_cast<char*>(data);
		EXPECT_EQ(test_blob.length, sizeof(data));
		for (size_t i = 0; i < sizeof(data); ++i) {
			EXPECT_EQ(result.get()[i], expected_result[i]) << "The parsed blob differs from the test data at index " << i;
		}
	}

	TEST(ReadTest, ParseElementTest1) {
		std::stringstream test_istream;
		unsigned char tag[] = { 0b00001010 };
		unsigned char int_data[] = { 0b00001111 };
		int expected_id = 1;
		int expected_value = 15;
		BMLint expected_int;

		test_istream.write(reinterpret_cast<char*>(tag), sizeof(tag));
		test_istream.write(reinterpret_cast<char*>(int_data), sizeof(int_data));

		// The element should be successfully parsed, so ParseElement should return true
		std::streampos start_position = test_istream.tellg();
		EXPECT_TRUE(ParseElement(test_istream, expected_id, expected_int));
		std::streampos end_position = test_istream.tellg();

		EXPECT_EQ(expected_int.getValue(), expected_value);

		// The stream should advance 
		std::streamoff stream_offset = end_position - start_position;
		EXPECT_EQ(stream_offset, sizeof(tag) + sizeof(int_data));
	}

	TEST(ReadTest, ParseElementTest2) {
		std::stringstream test_istream;
		unsigned char tag[] = { 0b00001010 };
		unsigned char int_data[] = { 0b00001111 };
		int expected_id = 2;
		int expected_value = 15;
		BMLint expected_int;

		test_istream.write(reinterpret_cast<char*>(tag), sizeof(tag));
		test_istream.write(reinterpret_cast<char*>(int_data), sizeof(int_data));

		// Expected ID does not match, so ParseElement should evaluate to false
		std::streampos start_position = test_istream.tellg();
		EXPECT_FALSE(ParseElement(test_istream, expected_id, expected_int));
		std::streampos end_position = test_istream.tellg();

		// The stream should not advance
		std::streamoff stream_offset = end_position - start_position;
		EXPECT_EQ(stream_offset, 0);
	}

	TEST(ReadTest, ParseElementTest3) {
		std::stringstream test_istream;
		unsigned char tag[] = { 0b00001010 };
		unsigned char long_data[] = { 0b00001111 };
		int expected_id = 1;
		int expected_value = 15;
		BMLlong expected_long;

		test_istream.write(reinterpret_cast<char*>(tag), sizeof(tag));
		test_istream.write(reinterpret_cast<char*>(long_data), sizeof(long_data));

		// Expected a long but the tag is for an int, so ParseElement should evaluate to false
		std::streampos start_position = test_istream.tellg();
		EXPECT_FALSE(ParseElement(test_istream, expected_id, expected_long));
		std::streampos end_position = test_istream.tellg();

		// The stream should not advance
		std::streamoff stream_offset = end_position - start_position;
		EXPECT_EQ(stream_offset, 0);
	}

// Constructor tests
	TEST(ConstructorTest, ConstructBMLint1) {
		int expected_id = 1;
		int32_t expected_value = 10000;
		BMLint test_int(expected_id, expected_value);
		EXPECT_EQ(test_int.id, expected_id);
		EXPECT_EQ(test_int.type_id, static_cast<int>(BML_TYPES::INT));
		EXPECT_EQ(test_int.getValue(), expected_value);
	}

	TEST(ConstructorTest, ConstructBMLlong1) {
		int expected_id = 1;
		int64_t expected_value = 10000;
		BMLlong test_long(expected_id, expected_value);
		EXPECT_EQ(test_long.id, expected_id);
		EXPECT_EQ(test_long.type_id, static_cast<int>(BML_TYPES::LONG));
		EXPECT_EQ(test_long.getValue(), expected_value);
	}

	TEST(ConstructorTest, ConstructBMLsingle1) {
		int expected_id = 1;
		float expected_value = 0.05;
		BMLsingle test_single(expected_id, expected_value);
		EXPECT_EQ(test_single.id, expected_id);
		EXPECT_EQ(test_single.type_id, static_cast<int>(BML_TYPES::SINGLE));
		EXPECT_EQ(test_single.getValue(), expected_value);
	}

	TEST(ConstructorTest, ConstructBMLdouble1) {
		int expected_id = 1;
		double expected_value = 0.05;
		BMLdouble test_double(expected_id, expected_value);
		EXPECT_EQ(test_double.id, expected_id);
		EXPECT_EQ(test_double.type_id, static_cast<int>(BML_TYPES::DOUBLE));
		EXPECT_EQ(test_double.getValue(), expected_value);
	}

	TEST(ConstructorTest, ConstructBMLstring1) {
		int expected_id = 1;
		std::string expected_value = "BMLstring test";
		BMLstring test_string(expected_id, expected_value);
		EXPECT_EQ(test_string.id, expected_id);
		EXPECT_EQ(test_string.type_id, static_cast<int>(BML_TYPES::STRING));
		EXPECT_EQ(test_string.getValue(), expected_value);
	}

	TEST(ConstructorTest, ConstructBMLblobTest1) {
		int expected_id = 1;
		char* blob = new char[13];
		strcpy(blob, "BMLblob test");
		std::shared_ptr<char> expected_data(blob, std::default_delete<char[]>());
		uint64_t expected_length = 12;
		BMLblob test_blob(expected_id, expected_length, expected_data);
		EXPECT_EQ(test_blob.id, expected_id);
		EXPECT_EQ(test_blob.type_id, static_cast<int>(BML_TYPES::BLOB));
		EXPECT_EQ(test_blob.length, expected_length);
		EXPECT_EQ(test_blob.getValue(), expected_data);
	}

// Operator tests
	TEST(OperatorTest, BMLIntAdditionTest1) {
		BMLint i(1, 0);
		i += 5;
		EXPECT_EQ(i.getValue(), 5);
	}

	TEST(OperatorTest, BMLIntAdditionTest2) {
		BMLint i(1, -5);
		i += -5;
		EXPECT_EQ(i.getValue(), -10);
	}

	TEST(OperatorTest, BMLIntAdditionTest3) {
		BMLint i(1, 0);
		i += INT32_MAX;
		EXPECT_EQ(i.getValue(), INT32_MAX);
	}

	TEST(OperatorTest, BMLIntAdditionTest4) {
		BMLint i(1, 0);
		i += INT32_MIN;
		EXPECT_EQ(i.getValue(), INT32_MIN);
	}

	TEST(OperatorTest, BMLLongAdditionTest1) {
		BMLlong l(1, 0);
		l += INT64_MAX;
		EXPECT_EQ(l.getValue(), INT64_MAX);
	}

	TEST(OperatorTest, BMLLongAdditionTest2) {
		BMLlong l(1, 0);
		l += INT64_MIN;
		EXPECT_EQ(l.getValue(), INT64_MIN);
	}

	TEST(OperatorTest, BMLLongAdditionTest3) {
		BMLlong l(1, 5);
		l += INT32_MAX;
		int64_t expected_value = static_cast<int64_t>(INT32_MAX) + 5;
		EXPECT_EQ(l.getValue(), expected_value);
	}

// Other tests
	TEST(OtherTest, CountLeadingOnesTest1) {
		unsigned char byte = 0b01010101;
		EXPECT_EQ(countLeadingOnes(byte), 0);
	}

	TEST(OtherTest, CountLeadingOnesTest2) {
		unsigned char byte = 0b10101010;
		EXPECT_EQ(countLeadingOnes(byte), 1);
	}

	TEST(OtherTest, CountLeadingOnesTest3) {
		unsigned char byte = 0b11110000;
		EXPECT_EQ(countLeadingOnes(byte), 4);
	}

	TEST(OtherTest, CountLeadingOnesTest4) {
		unsigned char byte = 0b11111111;
		EXPECT_EQ(countLeadingOnes(byte), 8);
	}

	TEST(OtherTest, CountLeadingOnesTest5) {
		unsigned char byte = 0b11111110;
		EXPECT_EQ(countLeadingOnes(byte), 7);
	}

	TEST(OtherTest, CountLeadingOnesTest6) {
		unsigned char byte = 0;
		EXPECT_EQ(countLeadingOnes(byte), 0);
	}
}