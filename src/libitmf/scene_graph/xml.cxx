#include "xml.h"

namespace itmf {
namespace scene {

	// TODO: Implement
	// Convert Root and all children to XML::Elements
	XML XML::FromRoot(const Root root) {
		XML result;
		return result;
	}

	XML XML::FromIStream(std::istream& is) {
		// Pugi Implementation
		return FromIStream_PugiImpl(is);
		// End Pugi Implementation
	}


	// TODO: Implement
	Root XML::toRoot() {
		return Root();
	}

	void XML::toOStream(std::ostream& out) const {
		// Pugi Implementation
		toOstream_PugiImpl(out);
		// End Pugi Implementation
	}

	// Scene Graph <-> XML conversion

	std::unique_ptr<XML::Element> XML::RootToXML(const Root& root) {
		std::string label = "OCS2";
		std::string contents;

		std::unordered_map<std::string, std::string> attributes = {
			{"version", root.getVersion()}
		};

		std::vector<std::unique_ptr<Element>> children;
		for(GraphPtr& graph : root.getGraphs())
			children.push_back(GraphToXML(*graph));

		return std::unique_ptr<Element>(new Element{std::move(children), attributes, label, contents});
	}

	std::unique_ptr<XML::Element> XML::GraphToXML(const Graph& graph) {
		std::unique_ptr<XML::Element> elem(new XML::Element{{}, {}, "graph", ""});
		// Add data related to any scene graph Item
		AppendItemData(graph, *elem);

		// Populate element children
		for (GraphPtr& subgraph : graph.getGraphs())
			elem->children.push_back(GraphToXML(*subgraph));
		for (NodePtr& node : graph.getNodes())
			elem->children.push_back(NodeToXML(*node));

		// Assign attributes
		elem->attributes["type"] = std::to_string(graph.getType());

		return elem;
	}

	std::unique_ptr<XML::Element> XML::NodeToXML(const Node& node) {
		std::unique_ptr<XML::Element> elem(new XML::Element{{}, {}, "node", ""});
		// Add data related to any scene graph Item
		AppendItemData(node, *elem);

		// Populate element children
		for (std::pair<PinId, Pin>&& idAndPin : node.getPins())
			elem->children.push_back(PinToXML(idAndPin.first, idAndPin.second));

		// Assign attributes
		elem->attributes["type"] = std::to_string(node.getType());

		return elem;
	}

	std::unique_ptr<XML::Element> XML::PinToXML(const PinId id, const Pin& pin) {
		std::string label = "pin";
		std::string content = "";

		std::unordered_map<std::string, std::string> attributes = {
			{"name", std::to_string(id)}, // TODO: Convert PinId to a string
			{"type", std::to_string(pin.getType())} // TODO: investigate dynamicType
		};

		std::vector<std::unique_ptr<Element>> children;
		children.push_back(NodeToXML(*pin.getNode()));

		return std::unique_ptr<XML::Element>(new XML::Element{std::move(children), attributes, label, content});
	}

	//// TODO: Implement
	//std::unique_ptr<XML::Element> XML::AttrToXML(const AttributeId id, const IAttribute& attr) {
	//	return {};
	//}

	//// TODO: Implement
	//template <class T>
	//std::unique_ptr<XML::Element> XML::AnimToXML(const Animator<T>& animator) {
	//	return {};
	//}

	// TODO: Implement
	void XML::AppendItemData(const Item& item, Element& elem) {
		elem.attributes["name"] = item.getName();

		// TODO: Handle animators and attributes
		for (std::pair<AttributeId, AttributePtr> idAndAttr : item.getAttributes()) {
			if (idAndAttr.second.isNull()) continue;

			//AttributeId& id = idAndAttr.first;
			//IAttribute& iattr = *idAndAttr.second;
			AppendAttributeData(idAndAttr.first, std::move(*idAndAttr.second), elem);
		}
	}

	void XML::AppendAttributeData(const AttributeId& id, const IAttribute&& attr, Element& elem) {
		AttrContainerType contype = attr.getContainerType();

		switch(attr.getAttrType()) {
			case AT_BOOL:
				switch(contype) {
					case ATTR_SCALAR:
						AppendTypedAttributeData<AT_BOOL, ATTR_SCALAR>(id, std::move(attr), elem);
						break;
					case ATTR_ARRAY:
						AppendTypedAttributeData<AT_BOOL, ATTR_ARRAY>(id, std::move(attr), elem);
						break;
				}
				break;
			case AT_INT:
				switch(contype) {
					case ATTR_SCALAR:
						AppendTypedAttributeData<AT_INT, ATTR_SCALAR>(id, std::move(attr), elem);
						break;
					case ATTR_ARRAY:
						AppendTypedAttributeData<AT_INT, ATTR_ARRAY>(id, std::move(attr), elem);
						break;
				}
				break;
			case AT_INT2:
				switch(contype) {
					case ATTR_SCALAR:
						AppendTypedAttributeData<AT_INT2, ATTR_SCALAR>(id, std::move(attr), elem);
						break;
					case ATTR_ARRAY:
						AppendTypedAttributeData<AT_INT2, ATTR_ARRAY>(id, std::move(attr), elem);
						break;
				}
				break;
			case AT_INT3:
				switch(contype) {
					case ATTR_SCALAR:
						AppendTypedAttributeData<AT_INT3, ATTR_SCALAR>(id, std::move(attr), elem);
						break;
					case ATTR_ARRAY:
						AppendTypedAttributeData<AT_INT3, ATTR_ARRAY>(id, std::move(attr), elem);
						break;
				}
				break;
			case AT_INT4:
				switch(contype) {
					case ATTR_SCALAR:
						AppendTypedAttributeData<AT_INT4, ATTR_SCALAR>(id, std::move(attr), elem);
						break;
					case ATTR_ARRAY:
						AppendTypedAttributeData<AT_INT4, ATTR_ARRAY>(id, std::move(attr), elem);
						break;
				}
				break;
			case AT_FLOAT:
				switch(contype) {
					case ATTR_SCALAR:
						AppendTypedAttributeData<AT_FLOAT, ATTR_SCALAR>(id, std::move(attr), elem);
						break;
					case ATTR_ARRAY:
						AppendTypedAttributeData<AT_FLOAT, ATTR_ARRAY>(id, std::move(attr), elem);
						break;
				}
				break;
			case AT_FLOAT2:
				switch(contype) {
					case ATTR_SCALAR:
						AppendTypedAttributeData<AT_FLOAT2, ATTR_SCALAR>(id, std::move(attr), elem);
						break;
					case ATTR_ARRAY:
						AppendTypedAttributeData<AT_FLOAT2, ATTR_ARRAY>(id, std::move(attr), elem);
						break;
				}
				break;
			case AT_FLOAT3:
				switch(contype) {
					case ATTR_SCALAR:
						AppendTypedAttributeData<AT_FLOAT3, ATTR_SCALAR>(id, std::move(attr), elem);
						break;
					case ATTR_ARRAY:
						AppendTypedAttributeData<AT_FLOAT3, ATTR_ARRAY>(id, std::move(attr), elem);
						break;
				}
				break;
			case AT_FLOAT4:
				switch(contype) {
					case ATTR_SCALAR:
						AppendTypedAttributeData<AT_FLOAT4, ATTR_SCALAR>(id, std::move(attr), elem);
						break;
					case ATTR_ARRAY:
						AppendTypedAttributeData<AT_FLOAT4, ATTR_ARRAY>(id, std::move(attr), elem);
						break;
				}
				break;
			case AT_STRING:
				switch(contype) {
					case ATTR_SCALAR:
						AppendTypedAttributeData<AT_STRING, ATTR_SCALAR>(id, std::move(attr), elem);
						break;
					case ATTR_ARRAY:
						AppendTypedAttributeData<AT_STRING, ATTR_ARRAY>(id, std::move(attr), elem);
						break;
				}
				break;
			case AT_FILENAME:
				switch(contype) {
					case ATTR_SCALAR:
						AppendTypedAttributeData<AT_FILENAME, ATTR_SCALAR>(id, std::move(attr), elem);
						break;
					case ATTR_ARRAY:
						AppendTypedAttributeData<AT_FILENAME, ATTR_ARRAY>(id, std::move(attr), elem);
						break;
				}
				break;
			case AT_BYTE:
				switch(contype) {
					case ATTR_SCALAR:
						AppendTypedAttributeData<AT_BYTE, ATTR_SCALAR>(id, std::move(attr), elem);
						break;
					case ATTR_ARRAY:
						AppendTypedAttributeData<AT_BYTE, ATTR_ARRAY>(id, std::move(attr), elem);
						break;
				}
				break;
			case AT_MATRIX:
				switch(contype) {
					case ATTR_SCALAR:
						AppendTypedAttributeData<AT_MATRIX, ATTR_SCALAR>(id, std::move(attr), elem);
						break;
					case ATTR_ARRAY:
						AppendTypedAttributeData<AT_MATRIX, ATTR_ARRAY>(id, std::move(attr), elem);
						break;
				}
				break;
			case AT_LONG:
				switch(contype) {
					case ATTR_SCALAR:
						AppendTypedAttributeData<AT_LONG, ATTR_SCALAR>(id, std::move(attr), elem);
						break;
					case ATTR_ARRAY:
						AppendTypedAttributeData<AT_LONG, ATTR_ARRAY>(id, std::move(attr), elem);
						break;
				}
				break;
			case AT_LONG2:
				switch(contype) {
					case ATTR_SCALAR:
						AppendTypedAttributeData<AT_LONG2, ATTR_SCALAR>(id, std::move(attr), elem);
						break;
					case ATTR_ARRAY:
						AppendTypedAttributeData<AT_LONG2, ATTR_ARRAY>(id, std::move(attr), elem);
						break;
				}
				break;
			case AT_UNKNOWN: default:
				switch(contype) {
					case ATTR_SCALAR:
						AppendTypedAttributeData<AT_UNKNOWN, ATTR_SCALAR>(id, std::move(attr), elem);
						break;
					case ATTR_ARRAY:
						AppendTypedAttributeData<AT_UNKNOWN, ATTR_ARRAY>(id, std::move(attr), elem);
						break;
				}
				break;
		}
	}


	// End Scene Graph <-> XML conversion


	// Pugi Implementation

	XML XML::FromIStream_PugiImpl(std::istream& is) {
		pugi::xml_document doc;
		pugi::xml_parse_result parse = doc.load(is);
		if (parse.status != pugi::status_ok) // TODO: handle error
			return XML();

		size_t num_root_nodes = std::distance(doc.children().begin(), doc.children().end());
		if (num_root_nodes == 0)
			return XML(); // TODO: handle error
		else if (num_root_nodes > 1)
			return XML(); // TODO: handle error
		else
			return XML(PugiRecurseCreateElement(doc.first_child()));
	}

	void XML::toOstream_PugiImpl(std::ostream& out) const {
		pugi::xml_document doc;
		if (this->head != nullptr)
			PugiRecurseCreatePugi(*this->head, doc.append_child());
		doc.save(out);
	}

	std::unique_ptr<XML::Element> XML::PugiRecurseCreateElement(const pugi::xml_node& node) {
		if (node.type() != pugi::xml_node_type::node_element) return nullptr;

		std::vector<std::unique_ptr<Element>> children;
		for (pugi::xml_node& child : node.children())
			if (child.type() == pugi::xml_node_type::node_element) {
				std::unique_ptr<Element> elem = PugiRecurseCreateElement(child);
				if (elem != nullptr)
					children.push_back(std::move(elem));
			}

		std::unordered_map<std::string, std::string> attributes;
		for (pugi::xml_attribute& attr : node.attributes()) {
			attributes[attr.name()] = attr.value();
		}

		std::string label = node.name();

		std::string contents = node.text().empty() ? "" : node.text().get();

		return std::unique_ptr<Element>(new Element{std::move(children), attributes, label, contents});
	}

	void XML::PugiRecurseCreatePugi(const XML::Element& elem, pugi::xml_node&& nodeOut) {
		nodeOut.set_name(elem.label.c_str());
		// set attribute values
		for (auto it = elem.attributes.begin(); it != elem.attributes.end(); ++it)
			nodeOut.append_attribute(it->first.c_str()) = it->second.c_str();

		// set contents if it isn't empty
		if (!elem.contents.empty())
			nodeOut.text().set(elem.contents.c_str());

		// recurse to children
		for (auto& childPtr : elem.children) {
			if (childPtr == nullptr) continue;
			PugiRecurseCreatePugi(*childPtr, nodeOut.append_child());
		}
	}

	// End Pugi Implementation

}
}
