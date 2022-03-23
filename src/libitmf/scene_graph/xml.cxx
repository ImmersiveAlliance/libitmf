#include "xml.h"

#include <sstream>

namespace itmf {
namespace scene {

	Root XMLReader::ReadStream(std::istream& in) {
		// Pugi Implementation
		std::unique_ptr<Element> root = FromIStream_PugiImpl(in);
		// End Pugi Implementation

		// TODO: Implement
		// return ElementToRoot(root);
		return {};
	}

	void XMLWriter::WriteStream(const Root& root, std::ostream& out) {
		IDState ids = {0, 0, 0, {}, {}};
		//std::unique_ptr<XML::Element> xml_root = RootToXML(root, ids);
		//ToOstream_PugiImpl(*xml_root, out);
	}

	// Scene Graph <-> XML conversion

	std::unique_ptr<XML::Element> XMLWriter::RootToXML(const Root& root, IDState& ids) {
		std::string label = "OCS2";
		std::string contents;

		std::vector<std::pair<std::string, std::string>> attributes = {
			{"version", root.getVersion()}
		};

		std::vector<std::unique_ptr<Element>> children;
		for(GraphPtr& graph : root.getGraphs())
			children.push_back(GraphToXML(*graph, ids));

		return std::unique_ptr<Element>(new Element{std::move(children), attributes, label, contents});
	}

	// TODO: Potential bug: if a node is pointed to by a graph and a pin, and we visit the pin first,
	//       the node will be duplicated at the graph level. I think a BFS implementation instead of
	//       the current DFS will solve it because the node pointed to by the graph will always be
	//       found first. Note that a BFS implementation needs to decouple the traversal logic from
	//       the XML-writing logic.
	std::unique_ptr<XML::Element> XMLWriter::GraphToXML(const Graph& graph, IDState& ids) {
		std::unique_ptr<XML::Element> elem(new XML::Element{{}, {}, "graph", ""});
		// Add data related to any scene graph Item
		AppendItemData(graph, *elem, ids);

		// Populate element children
		for (GraphPtr& subgraph : graph.getGraphs())
			elem->children.push_back(GraphToXML(*subgraph, ids));
		for (NodePtr& node : graph.getNodes()) {
			elem->children.push_back(NodeToXML(*node, ids));
		}

		// Assign attributes
		//elem->attributes["type"] = std::to_string(graph.getType());
		elem->attributes.push_back({"type", std::to_string(graph.getType())});

		return elem;
	}

	std::unique_ptr<XML::Element> XMLWriter::NodeToXML(const Node& node, IDState& ids) {
		std::unique_ptr<XML::Element> elem(new XML::Element{{}, {}, "node", ""});
		// Add data related to any scene graph Item
		AppendItemData(node, *elem, ids);

		// Populate element children
		for (std::pair<PinId, Pin>&& idAndPin : node.getPins())
			elem->children.push_back(PinToXML(idAndPin.first, idAndPin.second, ids));

		// Assign attributes
		elem->attributes.push_back({"type", std::to_string(node.getType())});

		return elem;
	}

	std::unique_ptr<XML::Element> XMLWriter::PinToXML(const PinId id, const Pin& pin, IDState& ids) {
		std::string label = "pin";
		std::string content = "";

		std::vector<std::pair<std::string, std::string>> attributes = {
			{"name", PinIdBimap.left.at(id)}, // TODO: Convert PinId to a string
			{"type", std::to_string(pin.getType())} // TODO: investigate dynamicType
		};

		std::vector<std::unique_ptr<Element>> children;

		Node* node = pin.getNode().get();
		auto search = ids.visited_items.find(node);
		if (search != ids.visited_items.end()) {
			children.push_back(NodeToXML(*node, ids));
		} else {
			attributes.push_back({"connect", std::to_string(search->second)});
		}

		return std::unique_ptr<XML::Element>(new XML::Element{std::move(children), attributes, label, content});
	}

	void XMLWriter::AppendItemData(const Item& item, Element& elem, IDState& ids) {
		++ids.current_item;
		ids.visited_items[&item] = ids.current_item;
		elem.attributes.push_back({"name", item.getName()});
		elem.attributes.push_back({"id", std::to_string(ids.current_item)});

		for (std::pair<AttributeId, AttributePtr> idAndAttr : item.getAttributes()) {
			if (idAndAttr.second.isNull()) continue;

			AppendAttributeData(idAndAttr.first, std::move(*idAndAttr.second), elem, ids);
		}
	}

	void XMLWriter::AppendAttributeData(const AttributeId& id, const IAttribute&& attr, Element& elem, IDState& ids) {
		AttrContainerType contype = attr.getContainerType();

		switch(attr.getAttrType()) {
			case AT_BOOL:
				switch(contype) {
					case ATTR_SCALAR:
						AppendTypedAttributeData<AT_BOOL, ATTR_SCALAR>(id, std::move(attr), elem, ids);
						break;
					case ATTR_ARRAY:
						AppendTypedAttributeData<AT_BOOL, ATTR_ARRAY>(id, std::move(attr), elem, ids);
						break;
				}
				break;
			case AT_INT:
				switch(contype) {
					case ATTR_SCALAR:
						AppendTypedAttributeData<AT_INT, ATTR_SCALAR>(id, std::move(attr), elem, ids);
						break;
					case ATTR_ARRAY:
						AppendTypedAttributeData<AT_INT, ATTR_ARRAY>(id, std::move(attr), elem, ids);
						break;
				}
				break;
			case AT_INT2:
				switch(contype) {
					case ATTR_SCALAR:
						AppendTypedAttributeData<AT_INT2, ATTR_SCALAR>(id, std::move(attr), elem, ids);
						break;
					case ATTR_ARRAY:
						AppendTypedAttributeData<AT_INT2, ATTR_ARRAY>(id, std::move(attr), elem, ids);
						break;
				}
				break;
			case AT_INT3:
				switch(contype) {
					case ATTR_SCALAR:
						AppendTypedAttributeData<AT_INT3, ATTR_SCALAR>(id, std::move(attr), elem, ids);
						break;
					case ATTR_ARRAY:
						AppendTypedAttributeData<AT_INT3, ATTR_ARRAY>(id, std::move(attr), elem, ids);
						break;
				}
				break;
			case AT_INT4:
				switch(contype) {
					case ATTR_SCALAR:
						AppendTypedAttributeData<AT_INT4, ATTR_SCALAR>(id, std::move(attr), elem, ids);
						break;
					case ATTR_ARRAY:
						AppendTypedAttributeData<AT_INT4, ATTR_ARRAY>(id, std::move(attr), elem, ids);
						break;
				}
				break;
			case AT_FLOAT:
				switch(contype) {
					case ATTR_SCALAR:
						AppendTypedAttributeData<AT_FLOAT, ATTR_SCALAR>(id, std::move(attr), elem, ids);
						break;
					case ATTR_ARRAY:
						AppendTypedAttributeData<AT_FLOAT, ATTR_ARRAY>(id, std::move(attr), elem, ids);
						break;
				}
				break;
			case AT_FLOAT2:
				switch(contype) {
					case ATTR_SCALAR:
						AppendTypedAttributeData<AT_FLOAT2, ATTR_SCALAR>(id, std::move(attr), elem, ids);
						break;
					case ATTR_ARRAY:
						AppendTypedAttributeData<AT_FLOAT2, ATTR_ARRAY>(id, std::move(attr), elem, ids);
						break;
				}
				break;
			case AT_FLOAT3:
				switch(contype) {
					case ATTR_SCALAR:
						AppendTypedAttributeData<AT_FLOAT3, ATTR_SCALAR>(id, std::move(attr), elem, ids);
						break;
					case ATTR_ARRAY:
						AppendTypedAttributeData<AT_FLOAT3, ATTR_ARRAY>(id, std::move(attr), elem, ids);
						break;
				}
				break;
			case AT_FLOAT4:
				switch(contype) {
					case ATTR_SCALAR:
						AppendTypedAttributeData<AT_FLOAT4, ATTR_SCALAR>(id, std::move(attr), elem, ids);
						break;
					case ATTR_ARRAY:
						AppendTypedAttributeData<AT_FLOAT4, ATTR_ARRAY>(id, std::move(attr), elem, ids);
						break;
				}
				break;
			case AT_STRING:
				switch(contype) {
					case ATTR_SCALAR:
						AppendTypedAttributeData<AT_STRING, ATTR_SCALAR>(id, std::move(attr), elem, ids);
						break;
					case ATTR_ARRAY:
						AppendTypedAttributeData<AT_STRING, ATTR_ARRAY>(id, std::move(attr), elem, ids);
						break;
				}
				break;
			case AT_FILENAME:
				switch(contype) {
					case ATTR_SCALAR:
						AppendTypedAttributeData<AT_FILENAME, ATTR_SCALAR>(id, std::move(attr), elem, ids);
						break;
					case ATTR_ARRAY:
						AppendTypedAttributeData<AT_FILENAME, ATTR_ARRAY>(id, std::move(attr), elem, ids);
						break;
				}
				break;
			case AT_BYTE:
				switch(contype) {
					case ATTR_SCALAR:
						AppendTypedAttributeData<AT_BYTE, ATTR_SCALAR>(id, std::move(attr), elem, ids);
						break;
					case ATTR_ARRAY:
						AppendTypedAttributeData<AT_BYTE, ATTR_ARRAY>(id, std::move(attr), elem, ids);
						break;
				}
				break;
			case AT_MATRIX:
				switch(contype) {
					case ATTR_SCALAR:
						AppendTypedAttributeData<AT_MATRIX, ATTR_SCALAR>(id, std::move(attr), elem, ids);
						break;
					case ATTR_ARRAY:
						AppendTypedAttributeData<AT_MATRIX, ATTR_ARRAY>(id, std::move(attr), elem, ids);
						break;
				}
				break;
			case AT_LONG:
				switch(contype) {
					case ATTR_SCALAR:
						AppendTypedAttributeData<AT_LONG, ATTR_SCALAR>(id, std::move(attr), elem, ids);
						break;
					case ATTR_ARRAY:
						AppendTypedAttributeData<AT_LONG, ATTR_ARRAY>(id, std::move(attr), elem, ids);
						break;
				}
				break;
			case AT_LONG2:
				switch(contype) {
					case ATTR_SCALAR:
						AppendTypedAttributeData<AT_LONG2, ATTR_SCALAR>(id, std::move(attr), elem, ids);
						break;
					case ATTR_ARRAY:
						AppendTypedAttributeData<AT_LONG2, ATTR_ARRAY>(id, std::move(attr), elem, ids);
						break;
				}
				break;
			case AT_UNKNOWN: default:
				switch(contype) {
					case ATTR_SCALAR:
						AppendTypedAttributeData<AT_UNKNOWN, ATTR_SCALAR>(id, std::move(attr), elem, ids);
						break;
					case ATTR_ARRAY:
						AppendTypedAttributeData<AT_UNKNOWN, ATTR_ARRAY>(id, std::move(attr), elem, ids);
						break;
				}
				break;
		}
	}

	template <>
	std::string XMLWriter::AttrValueToXMLString<AT_UNKNOWN>(const IAttribute::Type<AT_UNKNOWN, ATTR_SCALAR>& attr) {
		return attr;
	}

	template <>
	std::string XMLWriter::AttrValueToXMLString<AT_BOOL>(const IAttribute::Type<AT_BOOL, ATTR_SCALAR>& attr) {
		return attr ? "true" : "false";
	}

	template <>
	std::string XMLWriter::AttrValueToXMLString<AT_INT>(const IAttribute::Type<AT_INT, ATTR_SCALAR>& attr) {
		return std::to_string(attr);
	}

	template <>
	std::string XMLWriter::AttrValueToXMLString<AT_FLOAT>(const IAttribute::Type<AT_FLOAT, ATTR_SCALAR>& attr) {
		// TODO: Consider precision, etc.
		return std::to_string(attr);
	}

	template <>
	std::string XMLWriter::AttrValueToXMLString<AT_STRING>(const IAttribute::Type<AT_STRING, ATTR_SCALAR>& attr) {
		return attr;
	}

	template <>
	std::string XMLWriter::AttrValueToXMLString<AT_FILENAME>(const IAttribute::Type<AT_FILENAME, ATTR_SCALAR>& attr) {
		return attr;
	}

	// TODO: Should this be written differently since it's a byte? Spec doesn't say
	template <>
	std::string XMLWriter::AttrValueToXMLString<AT_BYTE>(const IAttribute::Type<AT_BYTE, ATTR_SCALAR>& attr) {
		return std::to_string(attr);
	}

	template <>
	std::string XMLWriter::AttrValueToXMLString<AT_LONG>(const IAttribute::Type<AT_LONG, ATTR_SCALAR>& attr) {
		return std::to_string(attr);
	}

	template <>
	std::string XMLWriter::AttrValueToXMLString<AT_INT2>(const IAttribute::Type<AT_INT2, ATTR_SCALAR>& attr) {
		return XMLWriter::AttrValueSequenceToXMLString<AT_INT2, AT_INT>(attr);
	}
	template <>
	std::string XMLWriter::AttrValueToXMLString<AT_INT3>(const IAttribute::Type<AT_INT3, ATTR_SCALAR>& attr) {
		return XMLWriter::AttrValueSequenceToXMLString<AT_INT3, AT_INT>(attr);
	}
	template <>
	std::string XMLWriter::AttrValueToXMLString<AT_INT4>(const IAttribute::Type<AT_INT4, ATTR_SCALAR>& attr) {
		return XMLWriter::AttrValueSequenceToXMLString<AT_INT4, AT_INT>(attr);
	}

	template <>
	std::string XMLWriter::AttrValueToXMLString<AT_FLOAT2>(const IAttribute::Type<AT_FLOAT2, ATTR_SCALAR>& attr) {
		return XMLWriter::AttrValueSequenceToXMLString<AT_FLOAT2, AT_FLOAT>(attr);
	}
	template <>
	std::string XMLWriter::AttrValueToXMLString<AT_FLOAT3>(const IAttribute::Type<AT_FLOAT3, ATTR_SCALAR>& attr) {
		return XMLWriter::AttrValueSequenceToXMLString<AT_FLOAT3, AT_FLOAT>(attr);
	}
	template <>
	std::string XMLWriter::AttrValueToXMLString<AT_FLOAT4>(const IAttribute::Type<AT_FLOAT4, ATTR_SCALAR>& attr) {
		return XMLWriter::AttrValueSequenceToXMLString<AT_FLOAT4, AT_FLOAT>(attr);
	}

	template <>
	std::string XMLWriter::AttrValueToXMLString<AT_MATRIX>(const IAttribute::Type<AT_MATRIX, ATTR_SCALAR>& attr) {
		return XMLWriter::AttrValueSequenceToXMLString<AT_MATRIX, AT_FLOAT4>(attr);
	}

	template <>
	std::string XMLWriter::AttrValueToXMLString<AT_LONG2>(const IAttribute::Type<AT_LONG2, ATTR_SCALAR>& attr) {
		return XMLWriter::AttrValueSequenceToXMLString<AT_LONG2, AT_LONG>(attr);
	}

	// End Scene Graph <-> XML conversion


	// Pugi Implementation

	std::unique_ptr<XML::Element> XMLReader::FromIStream_PugiImpl(std::istream& is) {
		pugi::xml_document doc;
		pugi::xml_parse_result parse = doc.load(is);
		if (parse.status != pugi::status_ok) // TODO: handle error
			return nullptr;

		size_t num_root_nodes = std::distance(doc.children().begin(), doc.children().end());
		if (num_root_nodes == 0)
			return nullptr; // TODO: handle error
		else if (num_root_nodes > 1)
			return nullptr; // TODO: handle error
		else
			return PugiRecurseCreateElement(doc.first_child());
	}

	std::unique_ptr<XML::Element> XMLReader::PugiRecurseCreateElement(const pugi::xml_node& node) {
		if (node.type() != pugi::xml_node_type::node_element) return nullptr;

		std::vector<std::unique_ptr<Element>> children;
		for (pugi::xml_node& child : node.children())
			if (child.type() == pugi::xml_node_type::node_element) {
				std::unique_ptr<Element> elem = PugiRecurseCreateElement(child);
				if (elem != nullptr)
					children.push_back(std::move(elem));
			}

		std::vector<std::pair<std::string, std::string>> attributes;
		for (pugi::xml_attribute& attr : node.attributes()) {
			attributes.push_back({attr.name(), attr.value()});
		}

		std::string label = node.name();

		std::string contents = node.text().empty() ? "" : node.text().get();

		return std::unique_ptr<Element>(new Element{std::move(children), attributes, label, contents});
	}

	void XMLWriter::ToOstream_PugiImpl(const Element& elem, std::ostream& out) {
		pugi::xml_document doc;
		PugiRecurseCreatePugi(elem, doc.append_child());
		doc.save(out);
	}

	void XMLWriter::PugiRecurseCreatePugi(const XML::Element& elem, pugi::xml_node&& nodeOut) {
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
