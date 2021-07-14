#include "gtest/gtest.h"
#include "bmltypes.h"
#include "itmfenums.h"

namespace itmf {
	// Writing tests

	// Reading tests
	TEST(ReadTest, ReadVUIETest1) {
		std::stringstream test_istream;
		char input_data[] = { 0x3f };
		uint64_t expected_value = 63;

		test_istream.write(input_data, sizeof(input_data));

		std::streampos begin_streampos = test_istream.tellg();
		BMLBitVector result = readVUIE(test_istream);
		std::streampos end_streampos = test_istream.tellg();

		EXPECT_EQ(result.to_uint64(), expected_value);
		std::streamoff stream_offset = end_streampos - begin_streampos;
		EXPECT_EQ(stream_offset, sizeof(input_data));
	}

	TEST(ReadTest, ReadVUIETest2) {
		std::stringstream test_istream;
		char input_data[] = { 0x40 };
		uint64_t expected_value = 64;

		test_istream.write(input_data, sizeof(input_data));

		BMLBitVector result = readVUIE(test_istream);

		EXPECT_EQ(result.to_uint64(), expected_value);
	}

	TEST(ReadTest, ReadVUIETest3) {
		std::stringstream test_istream;
		char input_data[] = { 0x82, 0x19 };
		uint64_t expected_value = 537;

		test_istream.write(input_data, sizeof(input_data));

		BMLBitVector result = readVUIE(test_istream);

		EXPECT_EQ(result.to_uint64(), expected_value);
	}

	TEST(ReadTest, ReadVUIETest4) {
		std::stringstream test_istream;
		char input_data[] = { 0xc1, 0x86, 0xa0 };
		uint64_t expected_value = 100000;

		test_istream.write(input_data, sizeof(input_data));

		BMLBitVector result = readVUIE(test_istream);

		EXPECT_EQ(result.to_uint64(), expected_value);
	}

	TEST(ReadTest, ReadVSIETest1) {
		std::stringstream test_istream;
		char input_data[] = { 0x3f };
		int64_t expected_value = 63;

		test_istream.write(input_data, sizeof(input_data));

		BMLBitVector result = readVSIE(test_istream);

		EXPECT_EQ(result.to_int64(), expected_value);
	}

	TEST(ReadTest, ReadVSIETest2) {
		std::stringstream test_istream;
		char input_data[] = { 0xa0, 0x40 };
		int64_t expected_value = -64;

		test_istream.write(input_data, sizeof(input_data));

		BMLBitVector result = readVSIE(test_istream);

		EXPECT_EQ(result.to_int64(), expected_value);
	}

	TEST(ReadTest, ReadVSIETest3) {
		std::stringstream test_istream;
		char input_data[] = { 0x82, 0x19 };
		int64_t expected_value = 537;

		test_istream.write(input_data, sizeof(input_data));

		BMLBitVector result = readVSIE(test_istream);

		EXPECT_EQ(result.to_int64(), expected_value);
	}

	TEST(ReadTest, ReadVSIETest4) {
		std::stringstream test_istream;
		char input_data[] = { 0xd1, 0x86, 0xa0 };
		int64_t expected_value = -100000;

		test_istream.write(input_data, sizeof(input_data));

		BMLBitVector result = readVSIE(test_istream);

		EXPECT_EQ(result.to_int64(), expected_value);
	}

	TEST(ReadTest, DecodeTagTest1) {
		std::stringstream test_istream;
		char input_data[] = { 0b00010010 };
		int expected_id = 2;
		int expected_type = 2;
		int actual_id, actual_type;

		test_istream.write(input_data, sizeof(input_data));

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
		char input_data[] = { 0b10100000, 0b00000010};
		int expected_id = 1024;
		int expected_type = 2;
		int actual_id, actual_type;

		test_istream.write(input_data, sizeof(input_data));

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
		char input_data[] = { 0b10100000, 0b00000111};
		int expected_id = 1024;
		int expected_type = 7;
		int actual_id, actual_type;

		test_istream.write(input_data, sizeof(input_data));

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
		char input_data[] = { 0 };
		int expected_id = 0;
		int expected_type = 0;
		int actual_id, actual_type;

		test_istream.write(input_data, sizeof(input_data));

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
		char input_data[] = { 0b10100000, 0b00000111};
		int expected_id = 1024;
		int expected_type = 7;
		int actual_id, actual_type;

		test_istream.write(input_data, sizeof(input_data));

		std::streampos expected_streampos = test_istream.tellg();
		peekTag(test_istream, actual_id, actual_type);
		std::streampos actual_streampos = test_istream.tellg();

		EXPECT_EQ(actual_id, expected_id);
		EXPECT_EQ(actual_type, expected_type);
		EXPECT_EQ(actual_streampos, expected_streampos);
	}

	TEST(ReadTest, ReadBMLintTest1) {
		std::stringstream test_istream;
		char input_data[] = { 0b00010000 };
		int expected_value = 16;

		test_istream.write(input_data, sizeof(input_data));

		BMLint test_int;
		test_int.parse(test_istream);

		EXPECT_EQ(test_int.getValue(), expected_value);
	}

	TEST(ReadTest, ReadBMLintTest2) {
		std::stringstream test_istream;
		char input_data[] = { 0b01010000 };
		int expected_value = -16;

		test_istream.write(input_data, sizeof(input_data));

		BMLint test_int;
		test_int.parse(test_istream);

		EXPECT_EQ(test_int.getValue(), expected_value);
	}

	TEST(ReadTest, ReadBMLlongTest1) {
		std::stringstream test_istream;
		char input_data[] = { 0b00010000 };
		long expected_value = 16;

		test_istream.write(input_data, sizeof(input_data));

		BMLlong test_long;
		test_long.parse(test_istream);

		EXPECT_EQ(test_long.getValue(), expected_value);
	}

	TEST(ReadTest, ReadBMLlongTest2) {
		std::stringstream test_istream;
		char input_data[] = { 0b01010000 };
		long expected_value = -16;

		test_istream.write(input_data, sizeof(input_data));

		BMLlong test_long;
		test_long.parse(test_istream);

		EXPECT_EQ(test_long.getValue(), expected_value);
	}

	TEST(ReadTest, ReadBMLsingleTest1) {
		std::stringstream test_istream;
		char input_data[] = { 0x00, 0x00, 0x00, 0x40 };
		float expected_value = 2.0f;
		
		test_istream.write(input_data, sizeof(input_data));

		BMLsingle test_single;
		test_single.parse(test_istream);

		EXPECT_EQ(test_single.getValue(), expected_value);
	}

	TEST(ReadTest, ReadBMLsingleTest2) {
		std::stringstream test_istream;
		char input_data[] = { 0x00, 0x00, 0x00, 0xC0 };
		float expected_value = -2.0f;
		
		test_istream.write(input_data, sizeof(input_data));

		BMLsingle test_single;
		test_single.parse(test_istream);

		EXPECT_EQ(test_single.getValue(), expected_value);
	}

	TEST(ReadTest, ReadBMLsingleTest3) {
		std::stringstream test_istream;
		char input_data[] = { 0x00, 0x00, 0xc0, 0x40 };
		float expected_value = 6.0f;
		
		test_istream.write(input_data, sizeof(input_data));

		BMLsingle test_single;
		test_single.parse(test_istream);

		EXPECT_EQ(test_single.getValue(), expected_value);
	}

	TEST(ReadTest, ReadBMLsingleTest4) {
		std::stringstream test_istream;
		char input_data[] = { 0x00, 0x00, 0x80, 0x3e };
		float expected_value = 0.25;
		
		test_istream.write(input_data, sizeof(input_data));

		BMLsingle test_single;
		test_single.parse(test_istream);

		EXPECT_EQ(test_single.getValue(), expected_value);
	}

	TEST(ReadTest, ReadBMLsingleTest5) {
		std::stringstream test_istream;
		char input_data[] = { 0x00, 0x00, 0xc0, 0x7f };
		
		test_istream.write(input_data, sizeof(input_data));

		BMLsingle test_single;
		test_single.parse(test_istream);

		EXPECT_TRUE(std::isnan(test_single.getValue()));
	}

	TEST(ReadTest, ReadBMLsingleTest6) {
		std::stringstream test_istream;
		char input_data[] = { 0x00, 0x00, 0x80, 0x7f };
		
		test_istream.write(input_data, sizeof(input_data));

		BMLsingle test_single;
		test_single.parse(test_istream);

		EXPECT_TRUE(std::isinf(test_single.getValue()));
	}

	TEST(ReadTest, ReadBMLdoubleTest1) {
		std::stringstream test_istream;
		char input_data[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40 };
		float expected_value = 2.0;
		
		test_istream.write(input_data, sizeof(input_data));

		BMLdouble test_double;
		test_double.parse(test_istream);

		EXPECT_EQ(test_double.getValue(), expected_value);
	}

	TEST(ReadTest, ReadBMLdoubleTest2) {
		std::stringstream test_istream;
		char input_data[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0 };
		float expected_value = -2.0;
		
		test_istream.write(input_data, sizeof(input_data));

		BMLdouble test_double;
		test_double.parse(test_istream);

		EXPECT_EQ(test_double.getValue(), expected_value);
	}

	TEST(ReadTest, ReadBMLdoubleTest3) {
		std::stringstream test_istream;
		char input_data[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x40 };
		float expected_value = 6.0;
		
		test_istream.write(input_data, sizeof(input_data));

		BMLdouble test_double;
		test_double.parse(test_istream);

		EXPECT_EQ(test_double.getValue(), expected_value);
	}

	TEST(ReadTest, ReadBMLdoubleTest4) {
		std::stringstream test_istream;
		char input_data[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd0, 0x3f };
		float expected_value = 0.25;
		
		test_istream.write(input_data, sizeof(input_data));

		BMLdouble test_double;
		test_double.parse(test_istream);

		EXPECT_EQ(test_double.getValue(), expected_value);
	}

	TEST(ReadTest, ReadBMLdoubleTest5) {
		std::stringstream test_istream;
		char input_data[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x7f };
		
		test_istream.write(input_data, sizeof(input_data));

		BMLdouble test_double;
		test_double.parse(test_istream);

		EXPECT_TRUE(std::isnan(test_double.getValue()));
	}

	TEST(ReadTest, ReadBMLdoubleTest6) {
		std::stringstream test_istream;
		char input_data[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x7f };
		
		test_istream.write(input_data, sizeof(input_data));

		BMLdouble test_double;
		test_double.parse(test_istream);

		EXPECT_TRUE(std::isinf(test_double.getValue()));
	}

	TEST(ReadTest, ReadBMLstringTest1) {
		std::stringstream test_istream;
		char length_vuie[] = { 0b00001111 };
		std::string text("Test BML String");

		test_istream.write(length_vuie, sizeof(length_vuie));
		test_istream.write(&text[0], text.size());

		BMLstring test_string;
		test_string.parse(test_istream);

		EXPECT_EQ(test_string.getValue(), text);
	}

	TEST(ReadTest, ReadBMLstringTest2) {
		std::stringstream test_istream;
		char length_vuie[] = { 0b00010001 };
		std::string text("Test BML \0 String", 17);

		test_istream.write(length_vuie, sizeof(length_vuie));
		test_istream.write(&text[0], text.size());

		BMLstring test_string;
		test_string.parse(test_istream);

		EXPECT_EQ(test_string.getValue(), text);
	}

	TEST(ReadTest, ReadBMLblobTest1) {
		std::stringstream test_istream;
		char length_vuie[] = { 0b00000001 };
		char data[] = { 0b00010001 };

		test_istream.write(length_vuie, sizeof(length_vuie));
		test_istream.write(data, sizeof(data));

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
		char length_vuie[] = { 0b00000100 };
		char data[] = { 0b11111111, 0b00000000, 0b11111111, 0b00000000 };

		test_istream.write(length_vuie, sizeof(length_vuie));
		test_istream.write(data, sizeof(data));

		BMLblob test_blob;
		test_blob.parse(test_istream);

		std::shared_ptr<char> result = test_blob.getValue();

		EXPECT_EQ(test_blob.length, sizeof(data));
		for (size_t i = 0; i < sizeof(data); ++i) {
			EXPECT_EQ(result.get()[i], data[i]) << "The parsed blob differs from the test data at index " << i;
		}
	}

	TEST(ReadTest, ParseElementTest1) {
		std::stringstream test_istream;
		char tag[] = { 0b00001010 };
		char int_data[] = { 0b00001111 };
		int expected_id = 1;
		int expected_value = 15;
		BMLint expected_int;

		test_istream.write(tag, sizeof(tag));
		test_istream.write(int_data, sizeof(int_data));

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
		char tag[] = { 0b00001010 };
		char int_data[] = { 0b00001111 };
		int expected_id = 2;
		int expected_value = 15;
		BMLint expected_int;

		test_istream.write(tag, sizeof(tag));
		test_istream.write(int_data, sizeof(int_data));

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
		char tag[] = { 0b00001010 };
		char long_data[] = { 0b00001111 };
		int expected_id = 1;
		int expected_value = 15;
		BMLlong expected_long;

		test_istream.write(tag, sizeof(tag));
		test_istream.write(long_data, sizeof(long_data));

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

	TEST(ConstructorTest, ConstructBMLblob1) {
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

	// Conversion tests

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