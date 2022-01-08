#include "elements.h"

#include "gtest/gtest.h"

namespace itmf {
    namespace scene {

        TEST(AttributeTest, GetUnknownAttribute) {
            Attribute::Unknown val = "hello";
            TypedAttribute<AT_UNKNOWN> attr(val);
            EXPECT_EQ(attr.getTypedData(), val);

            Attribute::Unknown data = boost::any_cast<Attribute::Unknown>(attr.getData());
            EXPECT_EQ(data, val);
        }

        TEST(AttributeTest, GetBoolAttribute) {
            Attribute::Bool val = false;
            TypedAttribute<AT_BOOL> attr(val);
            EXPECT_EQ(attr.getTypedData(), val);

            Attribute::Bool data = boost::any_cast<Attribute::Bool>(attr.getData());
            EXPECT_EQ(data, val);
        }

        TEST(AttributeTest, GetIntAttribute) {
            Attribute::Int val = 5;
            TypedAttribute<AT_INT> attr(val);
            EXPECT_EQ(attr.getTypedData(), val);

            Attribute::Int data = boost::any_cast<Attribute::Int>(attr.getData());
            EXPECT_EQ(data, val);
        }

        TEST(AttributeTest, GetInt2Attribute) {
            Attribute::Int2 val = {5, 10};
            TypedAttribute<AT_INT2> attr(val);
            EXPECT_EQ(attr.getTypedData(), val);

            Attribute::Int2 data = boost::any_cast<Attribute::Int2>(attr.getData());
            EXPECT_EQ(data, val);
        }

        TEST(AttributeTest, GetInt3Attribute) {
            Attribute::Int3 val = {5, 10, 15};
            TypedAttribute<AT_INT3> attr(val);
            EXPECT_EQ(attr.getTypedData(), val);

            Attribute::Int3 data = boost::any_cast<Attribute::Int3>(attr.getData());
            EXPECT_EQ(data, val);
        }

        TEST(AttributeTest, GetInt4Attribute) {
            Attribute::Int4 val = {5, 10, 15, 20};
            TypedAttribute<AT_INT4> attr(val);
            EXPECT_EQ(attr.getTypedData(), val);

            Attribute::Int4 data = boost::any_cast<Attribute::Int4>(attr.getData());
            EXPECT_EQ(data, val);
        }

        TEST(AttributeTest, GetFloatAttribute) {
            Attribute::Float val = 5.0f;
            TypedAttribute<AT_FLOAT> attr(val);
            EXPECT_EQ(attr.getTypedData(), val);

            Attribute::Float data = boost::any_cast<Attribute::Float>(attr.getData());
            EXPECT_EQ(data, val);
        }

        TEST(AttributeTest, GetFloat2Attribute) {
            Attribute::Float2 val = {5.0f, 10.0f};
            TypedAttribute<AT_FLOAT2> attr(val);
            EXPECT_EQ(attr.getTypedData(), val);

            Attribute::Float2 data = boost::any_cast<Attribute::Float2>(attr.getData());
            EXPECT_EQ(data, val);
        }

        TEST(AttributeTest, GetFloat3Attribute) {
            Attribute::Float3 val = {5.0f, 10.0f, 15.0f};
            TypedAttribute<AT_FLOAT3> attr(val);
            EXPECT_EQ(attr.getTypedData(), val);

            Attribute::Float3 data = boost::any_cast<Attribute::Float3>(attr.getData());
            EXPECT_EQ(data, val);
        }

        TEST(AttributeTest, GetFloat4Attribute) {
            Attribute::Float4 val = {5.0f, 10.0f, 15.0f, 20.0f};
            TypedAttribute<AT_FLOAT4> attr(val);
            EXPECT_EQ(attr.getTypedData(), val);

            Attribute::Float4 data = boost::any_cast<Attribute::Float4>(attr.getData());
            EXPECT_EQ(data, val);
        }

        TEST(AttributeTest, GetStringAttribute) {
            Attribute::String val = "string";
            TypedAttribute<AT_STRING> attr(val);
            EXPECT_EQ(attr.getTypedData(), val);

            Attribute::String data = boost::any_cast<Attribute::String>(attr.getData());
            EXPECT_EQ(data, val);
        }

        TEST(AttributeTest, GetFilenameAttribute) {
            Attribute::Filename val = "testfile";
            TypedAttribute<AT_FILENAME> attr(val);
            EXPECT_EQ(attr.getTypedData(), val);

            Attribute::Filename data = boost::any_cast<Attribute::Filename>(attr.getData());
            EXPECT_EQ(data, val);
        }

        TEST(AttributeTest, GetByteAttribute) {
            Attribute::Byte val = 0b01010101;
            TypedAttribute<AT_BYTE> attr(val);
            EXPECT_EQ(attr.getTypedData(), val);

            Attribute::Byte data = boost::any_cast<Attribute::Byte>(attr.getData());
            EXPECT_EQ(data, val);
        }

        TEST(AttributeTest, GetMatrixAttribute) {
            Attribute::Matrix val = {{{{ 0.0f, 1.0f, 2.0f, 3.0f}},
                                      {{ 4.0f, 5.0f, 6.0f, 7.0f}},
                                      {{ 8.0f, 9.0f, 10.0f, 11.0f}}}};
            TypedAttribute<AT_MATRIX> attr(val);
            EXPECT_EQ(attr.getTypedData(), val);

            Attribute::Matrix data = boost::any_cast<Attribute::Matrix>(attr.getData());
            EXPECT_EQ(data, val);
        }

        TEST(AttributeTest, GetLongAttribute) {
            Attribute::Long val = 5;
            TypedAttribute<AT_LONG> attr(val);
            EXPECT_EQ(attr.getTypedData(), val);

            Attribute::Long data = boost::any_cast<Attribute::Long>(attr.getData());
            EXPECT_EQ(data, val);
        }

        TEST(AttributeTest, GetLong2Attribute) {
            Attribute::Long2 val = {5, 10};
            TypedAttribute<AT_LONG2> attr(val);
            EXPECT_EQ(attr.getTypedData(), val);

            Attribute::Long2 data = boost::any_cast<Attribute::Long2>(attr.getData());
            EXPECT_EQ(data, val);
        }
    }
}
