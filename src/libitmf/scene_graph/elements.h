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
			// TODO: Constructor
			inline std::string getVersion() { return this->version; }
			inline std::vector<GraphPtr> getGraphs() { return this->graphs; }

			inline void setVersion(std::string versionIn) { this->version = versionIn; }
			inline void setGraphs(std::vector<GraphPtr> graphsIn) { this->graphs = graphs; }
			inline void addGraph(GraphPtr graphIn) { this->graphs.push_back(graphIn); }
	};


	class Item {
		private:
			std::string name;
			std::unordered_map<AttributeId, IAttribute::Ptr> attributes;
		public:
			// TODO: Constructor
			// NOTE: attrsIn is no longer owned by the caller after this operation.
			Item(std::string nameIn = "", std::unordered_map<AttributeId, IAttribute::Ptr>&& attrsIn = {})
				: name(nameIn), attributes(std::move(attrsIn)) { }
			inline std::string getName() { return this->name; }
			inline boost::optional<IAttribute::Ptr> getAttribute(AttributeId id);
			//inline std::unordered_map<AttributeId, AttributePtr> getAttributes() { return this->attributes; }

			inline void setName(std::string nameIn) { this->name = nameIn; }
			//inline void setAttribute(AttributeId id, AttributePtr attribute) { this->attributes[id] = std::move(attribute); }
			//inline void setAttribute(AttributeId id) { this->attributes[id] = nullptr; }
			//inline void setAttributes(std::unordered_map<AttributeId, AttributePtr> attrsIn) { this->attributes = attrsIn; }
	};

	class Graph : public Item {
		private:
			NodeGraphType type;
			std::vector<GraphPtr> graphs;
			std::vector<NodePtr> nodes;
		public:
			// TODO: Constructor
			inline NodeGraphType getType() { return this->type; }
			inline std::vector<GraphPtr> getGraphs() { return this->graphs; }
			inline std::vector<NodePtr> getNodes() { return this->nodes; }

			inline void setType(NodeGraphType typeIn) { this->type = typeIn; }
			inline void setGraphs(std::vector<GraphPtr> graphsIn) { this->graphs = graphsIn; }
			inline void setNodes(std::vector<NodePtr> nodesIn) { this->nodes = nodesIn; }

			inline void addGraph(GraphPtr graphIn) { this->graphs.push_back(graphIn); }
			inline void addNode(NodePtr nodeIn) { this->nodes.push_back(nodeIn); }
	};

	class Pin {
		private:
			NodePinType type;
			NodePtr node;
		public:
			// TODO: Constructor
			inline NodePinType getType() { return this->type; }
			inline NodePtr getNode() { return this-> node; }

			inline void setType(NodePinType typeIn) { this->type = typeIn; }
			inline void setNode(NodePtr nodeIn) { this->node = nodeIn; }
	};

	class Node : public Item {
		private:
			std::unordered_map<PinId, Pin> pins;
			NodeType type;
		public:
			Node(NodeType typeIn,
				 std::string name = "",
				 std::unordered_map<PinId, Pin> pinsIn = {},
				 std::unordered_map<AttributeId, IAttribute::Ptr>&& attrsIn = {})
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
