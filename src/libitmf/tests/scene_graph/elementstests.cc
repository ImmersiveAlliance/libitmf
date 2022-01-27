#include "elements.h"

#include <boost/optional/optional_io.hpp>

#include "gtest/gtest.h"

namespace itmf {
	namespace scene {

		TEST(ItemTest, GetAttribute) {
			float expected_val = 0.5;
			std::unique_ptr<IAttribute> p(new Attribute<AT_FLOAT>(expected_val));

			Graph g("", GT_UNKNOWN, {}, {}, {{A_ASPECT_RATIO, AttributePtr(std::move(p))}});

			AttributePtr found_attr = *g.getAttribute(A_ASPECT_RATIO);
			ASSERT_FALSE(found_attr.isNull());

			boost::optional<AttributePtr> missing_attr = g.getAttribute(A_ACTION);
			EXPECT_TRUE(missing_attr == boost::none);

			EXPECT_EQ((*found_attr).get<AT_FLOAT>(), expected_val);
		}

		TEST(NodeTest, GetPin) {
			Pin pin(PT_KERNEL);

			Node n("", NT_UNKNOWN, {{P_UNKNOWN, pin}}, {});

			Pin found_pin = *n.getPin(P_UNKNOWN);
			ASSERT_EQ(found_pin.getType(), pin.getType());
			ASSERT_EQ(found_pin.getNode(), pin.getNode());

			boost::optional<Pin> missing_pin = n.getPin(P_ABSORPTION);
			ASSERT_TRUE(missing_pin == boost::none);
		}

	}
}
