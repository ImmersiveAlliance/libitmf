#include "attributes.h"

#include <boost/optional/optional_io.hpp>

#include "gtest/gtest.h"

namespace itmf {
	namespace scene {

		TEST(AttributeTest, GetUnknownAttribute) {
			IAttribute::Unknown val = "hello";
			Attribute<AT_UNKNOWN> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			boost::optional<IAttribute::Unknown> data = attr.get<AT_UNKNOWN>();
			EXPECT_EQ(data.is_initialized(), true);
			EXPECT_EQ(*data, val);
		}

		TEST(AttributeTest, GetBoolAttribute) {
			IAttribute::Bool val = false;
			Attribute<AT_BOOL> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			boost::optional<IAttribute::Bool> data = attr.get<AT_BOOL>();
			EXPECT_EQ(data.is_initialized(), true);
			EXPECT_EQ(*data, val);
		}

		TEST(AttributeTest, GetIntAttribute) {
			IAttribute::Int val = 5;
			Attribute<AT_INT> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			boost::optional<IAttribute::Int> data = attr.get<AT_INT>();
			EXPECT_EQ(data.is_initialized(), true);
			EXPECT_EQ(*data, val);
		}

		TEST(AttributeTest, GetInt2Attribute) {
			IAttribute::Int2 val = {5, 10};
			Attribute<AT_INT2> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			boost::optional<IAttribute::Int2> data = attr.get<AT_INT2>();
			EXPECT_EQ(data.is_initialized(), true);
			EXPECT_EQ(*data, val);
		}

		TEST(AttributeTest, GetInt3Attribute) {
			IAttribute::Int3 val = {5, 10, 15};
			Attribute<AT_INT3> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			boost::optional<IAttribute::Int3> data = attr.get<AT_INT3>();
			EXPECT_EQ(data.is_initialized(), true);
			EXPECT_EQ(*data, val);
		}

		TEST(AttributeTest, GetInt4Attribute) {
			IAttribute::Int4 val = {5, 10, 15, 20};
			Attribute<AT_INT4> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			boost::optional<IAttribute::Int4> data = attr.get<AT_INT4>();
			EXPECT_EQ(data.is_initialized(), true);
			EXPECT_EQ(*data, val);
		}

		TEST(AttributeTest, GetFloatAttribute) {
			IAttribute::Float val = 5.0f;
			Attribute<AT_FLOAT> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			boost::optional<IAttribute::Float> data = attr.get<AT_FLOAT>();
			EXPECT_EQ(data.is_initialized(), true);
			EXPECT_EQ(*data, val);
		}

		TEST(AttributeTest, GetFloat2Attribute) {
			IAttribute::Float2 val = {5.0f, 10.0f};
			Attribute<AT_FLOAT2> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			boost::optional<IAttribute::Float2> data = attr.get<AT_FLOAT2>();
			EXPECT_EQ(data.is_initialized(), true);
			EXPECT_EQ(*data, val);
		}

		TEST(AttributeTest, GetFloat3Attribute) {
			IAttribute::Float3 val = {5.0f, 10.0f, 15.0f};
			Attribute<AT_FLOAT3> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			boost::optional<IAttribute::Float3> data = attr.get<AT_FLOAT3>();
			EXPECT_EQ(data.is_initialized(), true);
			EXPECT_EQ(*data, val);
		}

		TEST(AttributeTest, GetFloat4Attribute) {
			IAttribute::Float4 val = {5.0f, 10.0f, 15.0f, 20.0f};
			Attribute<AT_FLOAT4> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			boost::optional<IAttribute::Float4> data = attr.get<AT_FLOAT4>();
			EXPECT_EQ(data.is_initialized(), true);
			EXPECT_EQ(*data, val);
		}

		TEST(AttributeTest, GetStringAttribute) {
			IAttribute::String val = "string";
			Attribute<AT_STRING> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			boost::optional<IAttribute::String> data = attr.get<AT_STRING>();
			EXPECT_EQ(data.is_initialized(), true);
			EXPECT_EQ(*data, val);
		}

		TEST(AttributeTest, GetFilenameAttribute) {
			IAttribute::Filename val = "testfile";
			Attribute<AT_FILENAME> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			boost::optional<IAttribute::Filename> data = attr.get<AT_FILENAME>();
			EXPECT_EQ(data.is_initialized(), true);
			EXPECT_EQ(*data, val);
		}

		TEST(AttributeTest, GetByteAttribute) {
			IAttribute::Byte val = 0b01010101;
			Attribute<AT_BYTE> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			boost::optional<IAttribute::Byte> data = attr.get<AT_BYTE>();
			EXPECT_EQ(data.is_initialized(), true);
			EXPECT_EQ(*data, val);
		}

		TEST(AttributeTest, GetMatrixAttribute) {
			IAttribute::Matrix val = {{{{ 0.0f, 1.0f, 2.0f, 3.0f}},
									  {{ 4.0f, 5.0f, 6.0f, 7.0f}},
									  {{ 8.0f, 9.0f, 10.0f, 11.0f}}}};
			Attribute<AT_MATRIX> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			boost::optional<IAttribute::Matrix> data = attr.get<AT_MATRIX>();
			EXPECT_EQ(data.is_initialized(), true);
			EXPECT_EQ(*data, val);
		}

		TEST(AttributeTest, GetLongAttribute) {
			IAttribute::Long val = 5;
			Attribute<AT_LONG> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			boost::optional<IAttribute::Long> data = attr.get<AT_LONG>();
			EXPECT_EQ(data.is_initialized(), true);
			EXPECT_EQ(*data, val);
		}

		TEST(AttributeTest, GetLong2Attribute) {
			IAttribute::Long2 val = {5, 10};
			Attribute<AT_LONG2> attr(val);
			EXPECT_EQ(attr.getTypedData(), val);

			boost::optional<IAttribute::Long2> data = attr.get<AT_LONG2>();
			EXPECT_EQ(data.is_initialized(), true);
			EXPECT_EQ(*data, val);
		}

		TEST(AttributeTest, FailCast) {
			IAttribute::Long2 val = {5, 10};
			Attribute<AT_LONG2> attr(val);

			boost::optional<IAttribute::Long> data = attr.get<AT_LONG>();
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

			Attribute<AT_STRING> attr("test");
			EXPECT_EQ(attr.getAnimator().is_initialized(), false);
			attr.setAnimator(animPtr);
			EXPECT_EQ(attr.getAnimator().is_initialized(), true);
			EXPECT_EQ(*attr.getAnimator(), animPtr);
		}

		TEST(AttributeTest, PtrClone) {
			IAttribute::Long2 val = {5, 10};
			AttributePtr attr1(std::unique_ptr<IAttribute>(new Attribute<AT_LONG2>(val)));
			AttributePtr attr2 = attr1.clone();

			// Retrieve pointers to each typed attribute after the clone
			//auto typedAttr1 = dynamic_cast<Attribute<AT_LONG2>*>(*attr1);
			//auto typedAttr2 = dynamic_cast<Attribute<AT_LONG2>*>(*attr2);
			Attribute<AT_LONG2> typedAttr1 = *Attribute<AT_LONG2>::From(std::move(*attr1));
			Attribute<AT_LONG2> typedAttr2 = *Attribute<AT_LONG2>::From(std::move(*attr2));

			// Add an animator to the second typed attribute
			std::vector<IAttribute::Long2> seq = {{1, 2}, {3, 4}};
			auto animPtr = std::make_shared<Animator<IAttribute::Long2>>(seq, ANIM_LOOP);
			typedAttr2.setAnimator(animPtr);

			EXPECT_NE(&typedAttr1, &typedAttr2);

			EXPECT_EQ(typedAttr1.getAnimator(), boost::none);
			EXPECT_EQ(typedAttr2.getAnimator(), animPtr);
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
