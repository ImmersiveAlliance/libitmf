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
		public:
			static const std::string LATEST_VERSION;

			Root(std::vector<GraphPtr> graphsIn = {}, std::string verIn = LATEST_VERSION)
				: graphs(graphsIn), version(verIn) { }

			std::string getVersion() { return this->version; }
			std::vector<GraphPtr> getGraphs() { return this->graphs; }

			void setVersion(std::string versionIn) { this->version = versionIn; }
			void setGraphs(std::vector<GraphPtr> graphsIn) { this->graphs = graphsIn; }
			void addGraph(GraphPtr graphIn) { this->graphs.push_back(graphIn); }

		private:
			std::string version;
			std::vector<GraphPtr> graphs;
	};


	class Pin {
		public:
			Pin(NodePinType typeIn = PT_UNKNOWN, NodePtr nodeIn = nullptr) : type(typeIn), node(nodeIn) { }
			NodePinType getType() { return this->type; }
			NodePtr getNode() { return this-> node; }

			void setType(NodePinType typeIn) { this->type = typeIn; }
			void setNode(NodePtr nodeIn) { this->node = nodeIn; }

		private:
			NodePinType type;
			NodePtr node;
	};


	class Item {
		public:
			typedef std::unordered_map<AttributeId, AttributePtr, std::hash<int>> AttrMap;
			std::string getName() { return this->name; }
			boost::optional<AttributePtr> getAttribute(AttributeId id);
			AttrMap getAttributes() { return this->attributes; }

			void setName(std::string nameIn) { this->name = nameIn; }
			void setAttribute(AttributeId id, AttributePtr attribute) { this->attributes[id] = std::move(attribute); }
			void setAttributes(AttrMap attrsIn) { this->attributes = attrsIn; }
			void removeAttribute(AttributeId id) { this->attributes.erase(id); }

		protected:
			Item(std::string nameIn = "", AttrMap attrsIn = {})
				: name(nameIn), attributes(attrsIn) { }

		private:
			std::string name;
			AttrMap attributes;
	};

	class Graph : public Item {
		public:
			Graph(std::string nameIn = "",
				  NodeGraphType typeIn = GT_UNKNOWN,
				  std::vector<GraphPtr> graphsIn = {},
				  std::vector<NodePtr> nodesIn = {},
				  AttrMap attrsIn = {})
				: graphs(graphsIn), nodes(nodesIn), type(typeIn), Item(nameIn, attrsIn) { }

			NodeGraphType getType() { return this->type; }
			std::vector<GraphPtr> getGraphs() { return this->graphs; }
			std::vector<NodePtr> getNodes() { return this->nodes; }

			void setType(NodeGraphType typeIn) { this->type = typeIn; }
			void setGraphs(std::vector<GraphPtr> graphsIn) { this->graphs = graphsIn; }
			void setNodes(std::vector<NodePtr> nodesIn) { this->nodes = nodesIn; }

			void addGraph(GraphPtr graphIn) { this->graphs.push_back(graphIn); }
			void addNode(NodePtr nodeIn) { this->nodes.push_back(nodeIn); }

		private:
			NodeGraphType type;
			std::vector<GraphPtr> graphs;
			std::vector<NodePtr> nodes;
	};

	class Node : public Item {
		public:
			typedef std::unordered_map<PinId, Pin, std::hash<int>> PinMap;

			Node(std::string name = "",
				 NodeType typeIn = NT_UNKNOWN,
				 PinMap pinsIn = {},
				 AttrMap attrsIn = {})
				: type(typeIn), pins(pinsIn), Item(name, attrsIn) { }

			NodeType getType() { return this->type; }
			boost::optional<Pin> getPin(PinId id);
			PinMap getPins() { return this->pins; }

			void setType(NodeType typeIn) { this->type = typeIn; }
			void setPin(PinId id, Pin pin) { this->pins[id] = pin; }
			void setPins(PinMap pinsIn) { this->pins = pinsIn; }
		private:
			PinMap pins;
			NodeType type;
	};

}
}

#endif // ELEMENTS_H_
