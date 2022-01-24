#ifndef ELEMENTS_H_
#define ELEMENTS_H_

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include <boost/optional.hpp>

#include "attributes.h"

#include "enums.h"

namespace itmf {
namespace scene {

	class Root;
	class Item;
	class Graph;
	class Node;
	class Pin;

	typedef std::shared_ptr<Graph> GraphPtr;
	typedef std::shared_ptr<Node> NodePtr;

	class Root {
		private:
			std::string version;
			std::vector<GraphPtr> graphs;
		public:
	};


	class Item {
		private:
			std::string name;
			std::unordered_map<AttributeId, AttributePtr> attributes;
		public:
			// NOTE: attrsIn is no longer owned by the caller after this operation.
			Item(std::string nameIn = "", std::unordered_map<AttributeId, AttributePtr>&& attrsIn = {})
				: name(nameIn), attributes(std::move(attrsIn)) { }
	};

	class Graph : public Item {
		private:
			std::vector<GraphPtr> graphs;
			std::vector<NodePtr> nodes;
			NodeGraphType type;
		public:
	};

	class Pin {
		private:
			NodePinType type;
			NodePtr node;
	};

	class Node : public Item {
		private:
			std::unordered_map<PinId, Pin> pins;
			NodeType type;
		public:
			Node(NodeType typeIn,
				 std::string name = "",
				 std::unordered_map<PinId, Pin> pinsIn = {},
				 std::unordered_map<AttributeId, AttributePtr>&& attrsIn = {})
				: type(typeIn), pins(pinsIn), Item(name, std::move(attrsIn)) { }

			inline NodeType getType() { return this->type; }
			boost::optional<Pin> getPin(PinId id);
			inline std::unordered_map<PinId, Pin> getPins() { return this->pins; }

			inline void setType(NodeType typeIn) { this->type = typeIn; }
			inline void setPin(PinId id, Pin pin) { this->pins[id] = pin; }
			inline void setPins(std::unordered_map<PinId, Pin> pinsIn) { this->pins = pinsIn; }
	};

}
}

#endif // ELEMENTS_H_
