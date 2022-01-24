#include "attributes.h"

#include <boost/optional/optional_io.hpp>

#include "gtest/gtest.h"

namespace itmf {
	namespace scene {

		TEST(AttributeTest, GetUnknownAttribute) {
			IAttribute::Unknown val = "hello";
			TypedAttribute<AT_UNKNOWN> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			boost::optional<IAttribute::Unknown> data = IAttribute::Cast<IAttribute::Unknown>(attr.getData());
			EXPECT_EQ(data.is_initialized(), true);
			EXPECT_EQ(*data, val);
		}

		TEST(AttributeTest, GetBoolAttribute) {
			IAttribute::Bool val = false;
			TypedAttribute<AT_BOOL> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			boost::optional<IAttribute::Bool> data = IAttribute::Cast<IAttribute::Bool>(attr.getData());
			EXPECT_EQ(data.is_initialized(), true);
			EXPECT_EQ(*data, val);
		}

		TEST(AttributeTest, GetIntAttribute) {
			IAttribute::Int val = 5;
			TypedAttribute<AT_INT> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			boost::optional<IAttribute::Int> data = IAttribute::Cast<IAttribute::Int>(attr.getData());
			EXPECT_EQ(data.is_initialized(), true);
			EXPECT_EQ(*data, val);
		}

		TEST(AttributeTest, GetInt2Attribute) {
			IAttribute::Int2 val = {5, 10};
			TypedAttribute<AT_INT2> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			boost::optional<IAttribute::Int2> data = IAttribute::Cast<IAttribute::Int2>(attr.getData());
			EXPECT_EQ(data.is_initialized(), true);
			EXPECT_EQ(*data, val);
		}

		TEST(AttributeTest, GetInt3Attribute) {
			IAttribute::Int3 val = {5, 10, 15};
			TypedAttribute<AT_INT3> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			boost::optional<IAttribute::Int3> data = IAttribute::Cast<IAttribute::Int3>(attr.getData());
			EXPECT_EQ(data.is_initialized(), true);
			EXPECT_EQ(*data, val);
		}

		TEST(AttributeTest, GetInt4Attribute) {
			IAttribute::Int4 val = {5, 10, 15, 20};
			TypedAttribute<AT_INT4> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			boost::optional<IAttribute::Int4> data = IAttribute::Cast<IAttribute::Int4>(attr.getData());
			EXPECT_EQ(data.is_initialized(), true);
			EXPECT_EQ(*data, val);
		}

		TEST(AttributeTest, GetFloatAttribute) {
			IAttribute::Float val = 5.0f;
			TypedAttribute<AT_FLOAT> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			boost::optional<IAttribute::Float> data = IAttribute::Cast<IAttribute::Float>(attr.getData());
			EXPECT_EQ(data.is_initialized(), true);
			EXPECT_EQ(*data, val);
		}

		TEST(AttributeTest, GetFloat2Attribute) {
			IAttribute::Float2 val = {5.0f, 10.0f};
			TypedAttribute<AT_FLOAT2> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			boost::optional<IAttribute::Float2> data = IAttribute::Cast<IAttribute::Float2>(attr.getData());
			EXPECT_EQ(data.is_initialized(), true);
			EXPECT_EQ(*data, val);
		}

		TEST(AttributeTest, GetFloat3Attribute) {
			IAttribute::Float3 val = {5.0f, 10.0f, 15.0f};
			TypedAttribute<AT_FLOAT3> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			boost::optional<IAttribute::Float3> data = IAttribute::Cast<IAttribute::Float3>(attr.getData());
			EXPECT_EQ(data.is_initialized(), true);
			EXPECT_EQ(*data, val);
		}

		TEST(AttributeTest, GetFloat4Attribute) {
			IAttribute::Float4 val = {5.0f, 10.0f, 15.0f, 20.0f};
			TypedAttribute<AT_FLOAT4> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			boost::optional<IAttribute::Float4> data = IAttribute::Cast<IAttribute::Float4>(attr.getData());
			EXPECT_EQ(data.is_initialized(), true);
			EXPECT_EQ(*data, val);
		}

		TEST(AttributeTest, GetStringAttribute) {
			IAttribute::String val = "string";
			TypedAttribute<AT_STRING> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			boost::optional<IAttribute::String> data = IAttribute::Cast<IAttribute::String>(attr.getData());
			EXPECT_EQ(data.is_initialized(), true);
			EXPECT_EQ(*data, val);
		}

		TEST(AttributeTest, GetFilenameAttribute) {
			IAttribute::Filename val = "testfile";
			TypedAttribute<AT_FILENAME> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			boost::optional<IAttribute::Filename> data = IAttribute::Cast<IAttribute::Filename>(attr.getData());
			EXPECT_EQ(data.is_initialized(), true);
			EXPECT_EQ(*data, val);
		}

		TEST(AttributeTest, GetByteAttribute) {
			IAttribute::Byte val = 0b01010101;
			TypedAttribute<AT_BYTE> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			boost::optional<IAttribute::Byte> data = IAttribute::Cast<IAttribute::Byte>(attr.getData());
			EXPECT_EQ(data.is_initialized(), true);
			EXPECT_EQ(*data, val);
		}

		TEST(AttributeTest, GetMatrixAttribute) {
			IAttribute::Matrix val = {{{{ 0.0f, 1.0f, 2.0f, 3.0f}},
									  {{ 4.0f, 5.0f, 6.0f, 7.0f}},
									  {{ 8.0f, 9.0f, 10.0f, 11.0f}}}};
			TypedAttribute<AT_MATRIX> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			boost::optional<IAttribute::Matrix> data = IAttribute::Cast<IAttribute::Matrix>(attr.getData());
			EXPECT_EQ(data.is_initialized(), true);
			EXPECT_EQ(*data, val);
		}

		TEST(AttributeTest, GetLongAttribute) {
			IAttribute::Long val = 5;
			TypedAttribute<AT_LONG> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			boost::optional<IAttribute::Long> data = IAttribute::Cast<IAttribute::Long>(attr.getData());
			EXPECT_EQ(data.is_initialized(), true);
			EXPECT_EQ(*data, val);
		}

		TEST(AttributeTest, GetLong2Attribute) {
			IAttribute::Long2 val = {5, 10};
			TypedAttribute<AT_LONG2> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			boost::optional<IAttribute::Long2> data = IAttribute::Cast<IAttribute::Long2>(attr.getData());
			EXPECT_EQ(data.is_initialized(), true);
			EXPECT_EQ(*data, val);
		}

		TEST(AttributeTest, FailCast) {
			IAttribute::Long2 val = {5, 10};
			TypedAttribute<AT_LONG2> attr(val);

			boost::optional<IAttribute::Long> data = IAttribute::Cast<IAttribute::Long>(attr.getData());
			EXPECT_EQ(data.is_initialized(), false);
		}

		TEST(AttributeTest, SetAndRetrieveAnimator) {
			std::vector<IAttribute::String> dataSequence = {"val1", "val2", "val3"};
			AnimationType animationType = ANIM_LOOP;
			float period = 6.0;
			std::vector<float> pattern = {1.0, 3.0, 4.0, 5.0};
			float endTime = 30.0;
			std::string name = "name";
			AnimatorType animatorType = REGULAR;
			auto animPtr = std::make_shared<Animator<IAttribute::String>>(
				dataSequence,
				animationType,
				period,
				pattern,
				endTime,
				name,
				animatorType
			);

			TypedAttribute<AT_STRING> attr("test");
			EXPECT_EQ(attr.getAnimator().is_initialized(), false);
			attr.setAnimator(animPtr);
			EXPECT_EQ(attr.getAnimator().is_initialized(), true);
			EXPECT_EQ(*attr.getAnimator(), animPtr);
		}

		TEST(AnimatorTest, SetThenGet) {
			std::vector<IAttribute::String> dataSequence = {"val1", "val2", "val3"};
			AnimationType animationType = ANIM_LOOP;
			float period = 6.0;
			std::vector<float> pattern = {1.0, 3.0, 4.0, 5.0};
			float endTime = 30.0;
			std::string name = "name";
			AnimatorType animatorType = REGULAR;
			auto animPtr = std::make_shared<Animator<IAttribute::String>>(
				dataSequence,
				animationType,
				period,
				pattern,
				endTime,
				name,
				animatorType
			);

			EXPECT_EQ(dataSequence, animPtr->getValueSequence());
			EXPECT_EQ(animationType, animPtr->getAnimationType());
			EXPECT_EQ(period, animPtr->getPeriod());
			EXPECT_EQ(pattern, animPtr->getPattern());
			EXPECT_EQ(endTime, animPtr->getEndTime());
			EXPECT_EQ(name, animPtr->getName());
			EXPECT_EQ(animatorType, animPtr->getAnimatorType());
		}
	}
}
