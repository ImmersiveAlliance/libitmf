#include "elements.h"

#include <boost/optional/optional_io.hpp>

#include "gtest/gtest.h"

namespace itmf {
	namespace scene {

		TEST(ItemTest, GetAttribute) {
			float expected_val = 0.5;
			std::unique_ptr<IAttribute> p(new TypedAttribute<AT_FLOAT>(expected_val));
			std::unordered_map<AttributeId, IAttribute::Ptr> map = {
				{A_ASPECT_RATIO, IAttribute::Ptr(std::move(p))}
			};

			Node n("", NT_UNKNOWN, {}, map);

			IAttribute::Ptr found_attr = *n.getAttribute(A_ASPECT_RATIO);
			ASSERT_NE((found_attr).get(), nullptr);

			boost::optional<IAttribute::Ptr> missing_attr = n.getAttribute(A_ACTION);
			EXPECT_TRUE(missing_attr == boost::none);

			EXPECT_EQ(IAttribute::Cast<IAttribute::Float>((found_attr).get()->getData()), expected_val);
		}

	}
}
