#include "xml.h"

namespace itmf {
namespace scene {

	// TODO: Implement
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
		if (this->root != nullptr)
			PugiRecurseCreatePugi(*this->root, doc.append_child());
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
