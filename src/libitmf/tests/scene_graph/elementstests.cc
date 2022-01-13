#include "elements.h"

#include "gtest/gtest.h"

namespace itmf {
	namespace scene {

		TEST(AttributeTest, GetUnknownAttribute) {
			IAttribute::Unknown val = "hello";
			TypedAttribute<AT_UNKNOWN> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			IAttribute::Unknown data = boost::any_cast<IAttribute::Unknown>(attr.getData());
			EXPECT_EQ(data, val);
		}

		TEST(AttributeTest, GetBoolAttribute) {
			IAttribute::Bool val = false;
			TypedAttribute<AT_BOOL> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			IAttribute::Bool data = boost::any_cast<IAttribute::Bool>(attr.getData());
			EXPECT_EQ(data, val);
		}

		TEST(AttributeTest, GetIntAttribute) {
			IAttribute::Int val = 5;
			TypedAttribute<AT_INT> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			IAttribute::Int data = boost::any_cast<IAttribute::Int>(attr.getData());
			EXPECT_EQ(data, val);
		}

		TEST(AttributeTest, GetInt2Attribute) {
			IAttribute::Int2 val = {5, 10};
			TypedAttribute<AT_INT2> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			IAttribute::Int2 data = boost::any_cast<IAttribute::Int2>(attr.getData());
			EXPECT_EQ(data, val);
		}

		TEST(AttributeTest, GetInt3Attribute) {
			IAttribute::Int3 val = {5, 10, 15};
			TypedAttribute<AT_INT3> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			IAttribute::Int3 data = boost::any_cast<IAttribute::Int3>(attr.getData());
			EXPECT_EQ(data, val);
		}

		TEST(AttributeTest, GetInt4Attribute) {
			IAttribute::Int4 val = {5, 10, 15, 20};
			TypedAttribute<AT_INT4> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			IAttribute::Int4 data = boost::any_cast<IAttribute::Int4>(attr.getData());
			EXPECT_EQ(data, val);
		}

		TEST(AttributeTest, GetFloatAttribute) {
			IAttribute::Float val = 5.0f;
			TypedAttribute<AT_FLOAT> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			IAttribute::Float data = boost::any_cast<IAttribute::Float>(attr.getData());
			EXPECT_EQ(data, val);
		}

		TEST(AttributeTest, GetFloat2Attribute) {
			IAttribute::Float2 val = {5.0f, 10.0f};
			TypedAttribute<AT_FLOAT2> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			IAttribute::Float2 data = boost::any_cast<IAttribute::Float2>(attr.getData());
			EXPECT_EQ(data, val);
		}

		TEST(AttributeTest, GetFloat3Attribute) {
			IAttribute::Float3 val = {5.0f, 10.0f, 15.0f};
			TypedAttribute<AT_FLOAT3> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			IAttribute::Float3 data = boost::any_cast<IAttribute::Float3>(attr.getData());
			EXPECT_EQ(data, val);
		}

		TEST(AttributeTest, GetFloat4Attribute) {
			IAttribute::Float4 val = {5.0f, 10.0f, 15.0f, 20.0f};
			TypedAttribute<AT_FLOAT4> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			IAttribute::Float4 data = boost::any_cast<IAttribute::Float4>(attr.getData());
			EXPECT_EQ(data, val);
		}

		TEST(AttributeTest, GetStringAttribute) {
			IAttribute::String val = "string";
			TypedAttribute<AT_STRING> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			IAttribute::String data = boost::any_cast<IAttribute::String>(attr.getData());
			EXPECT_EQ(data, val);
		}

		TEST(AttributeTest, GetFilenameAttribute) {
			IAttribute::Filename val = "testfile";
			TypedAttribute<AT_FILENAME> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			IAttribute::Filename data = boost::any_cast<IAttribute::Filename>(attr.getData());
			EXPECT_EQ(data, val);
		}

		TEST(AttributeTest, GetByteAttribute) {
			IAttribute::Byte val = 0b01010101;
			TypedAttribute<AT_BYTE> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			IAttribute::Byte data = boost::any_cast<IAttribute::Byte>(attr.getData());
			EXPECT_EQ(data, val);
		}

		TEST(AttributeTest, GetMatrixAttribute) {
			IAttribute::Matrix val = {{{{ 0.0f, 1.0f, 2.0f, 3.0f}},
									  {{ 4.0f, 5.0f, 6.0f, 7.0f}},
									  {{ 8.0f, 9.0f, 10.0f, 11.0f}}}};
			TypedAttribute<AT_MATRIX> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			IAttribute::Matrix data = boost::any_cast<IAttribute::Matrix>(attr.getData());
			EXPECT_EQ(data, val);
		}

		TEST(AttributeTest, GetLongAttribute) {
			IAttribute::Long val = 5;
			TypedAttribute<AT_LONG> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			IAttribute::Long data = boost::any_cast<IAttribute::Long>(attr.getData());
			EXPECT_EQ(data, val);
		}

		TEST(AttributeTest, GetLong2Attribute) {
			IAttribute::Long2 val = {5, 10};
			TypedAttribute<AT_LONG2> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			IAttribute::Long2 data = boost::any_cast<IAttribute::Long2>(attr.getData());
			EXPECT_EQ(data, val);
		}
	}
}
