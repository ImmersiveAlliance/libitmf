#include "elements.h"

namespace itmf {
namespace scene {
    boost::optional<Pin> Node::getPin(PinId id) {
        if (this->pins.count(id) > 0)
            return this->pins[id];
        else
            return boost::none;
    }
}
}
