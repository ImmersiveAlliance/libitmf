#include "elements.h"

namespace itmf {
namespace scene {
	const std::string Root::LATEST_VERSION = "1";

	boost::optional<AttributePtr> Item::getAttribute(AttributeId id) {
		if (this->attributes.count(id) > 0)
			return this->attributes[id];
		else
			return boost::none;
	}

	boost::optional<Pin> Node::getPin(PinId id) {
		if (this->pins.count(id) > 0)
			return this->pins[id];
		else
			return boost::none;
	}
}
}
