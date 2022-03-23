#ifndef SCENE_XML_H_
#define SCENE_XML_H_

#include <vector>
#include <map>
#include <unordered_map>
#include <utility>
#include <memory>
#include <string>
#include <iostream>

// Pugi Implementation
#include <pugixml.hpp>
// End Pugi Implementation

#include "elements.h"

namespace itmf {
namespace scene {

	class XML {
		public:
			// TODO: this is a serialization, maybe more general than XML. Consider for JSON.
			struct Element {
				std::vector<std::unique_ptr<Element>> children;
				std::vector<std::pair<std::string, std::string>> attributes;
				std::string label;
				std::string contents;
			};
		protected:
			XML() { }
	};

	class XMLReader : public XML {
		public:
			static Root ReadStream(std::istream& in);
		private:
			XMLReader() { }
			// Pugi Implementation
			static std::unique_ptr<Element> FromIStream_PugiImpl(std::istream& is);
			static std::unique_ptr<Element> PugiRecurseCreateElement(const pugi::xml_node& node);
			// End Pugi Implementation
	};

	class XMLWriter : public XML {
		public:
			static void WriteStream(const Root& root, std::ostream& out);

			// TODO: We should introduce a way for tracking arrays that we've seen before so that they can be marked with the same array ID
			struct IDState {
				int64_t current_item;
				int64_t current_anim;
				int64_t current_array;
				std::unordered_map<const Item*, int64_t> visited_items;
				std::unordered_map<const IAnimator*, int64_t> visited_anims;
			};

			static std::unique_ptr<Element> RootToXML(const Root& root, IDState& ids);
			static std::unique_ptr<Element> GraphToXML(const Graph& graph, IDState& ids);
			static std::unique_ptr<Element> NodeToXML(const Node& node, IDState& ids);
			static std::unique_ptr<Element> PinToXML(const PinId id, const Pin& pin, IDState& ids);

			template <AttributeType ATYPE, AttrContainerType ACONT>
			static std::unique_ptr<Element> AttrToXML(const AttributeId id, const Attribute<ATYPE, ACONT>& attr, boost::optional<uint64_t> anim_id, IDState& ids);
			template <AttributeType ATYPE, AttrContainerType ACONT>
			static std::unique_ptr<Element> AnimToXML(const Animator<typename IAttribute::Type<ATYPE, ACONT>>& animator, IDState& ids);
		private:
			XMLWriter() { }

			static void AppendItemData(const Item& item, Element& elem, IDState& ids);
			static void AppendAttributeData(const AttributeId& id, const IAttribute&& attr, Element& elem, IDState& ids);
			template <AttributeType ATYPE, AttrContainerType ACONT>
			static void AppendTypedAttributeData(const AttributeId& id, const IAttribute&& iattr, Element& elem, IDState& ids);
			// NOTE: Template specializations of AttrValueToXMLString can be found in xml.cxx
			template <AttributeType ATYPE>
			static std::string AttrValueToXMLString(const IAttribute::Type<ATYPE, ATTR_SCALAR>& attr);
			template <AttributeType ATYPE, AttributeType SUBTYPE>
			static std::string AttrValueSequenceToXMLString(const IAttribute::Type<ATYPE, ATTR_SCALAR>& attr);
			template <AttributeType ATYPE, AttrContainerType ACONT>
			static typename std::enable_if<ACONT==ATTR_SCALAR, std::string>::type AttrDataToXMLString(const IAttribute::Type<ATYPE, ACONT>& attr);
			template <AttributeType ATYPE, AttrContainerType ACONT>
			static typename std::enable_if<ACONT==ATTR_ARRAY, std::string>::type AttrDataToXMLString(const IAttribute::Type<ATYPE, ACONT>& attr);


			// Pugi Implementation
			static void ToOstream_PugiImpl(const Element& elem, std::ostream& out);
			static void PugiRecurseCreatePugi(const Element& elem, pugi::xml_node&& nodeOut);
			// End Pugi Implementation
	};

	template <AttributeType ATYPE, AttrContainerType ACONT>
	void XMLWriter::AppendTypedAttributeData(const AttributeId& id, const IAttribute&& iattr, Element& elem, IDState& ids) {
		auto maybeAttr = Attribute<ATYPE, ACONT>::From(std::move(iattr));

		if (!maybeAttr) return;
		Attribute<ATYPE, ACONT> attr = *maybeAttr;

		auto maybeAnim = attr.getAnimator();
		boost::optional<uint64_t> maybeAnimId = boost::none;
		if (maybeAnim) { // TODO: and if the anim hasn't already been seen
			auto animPtr = *maybeAnim;
			auto search = ids.visited_anims.find(animPtr.get());
			if (search != ids.visited_anims.end()) {
				maybeAnimId = search->second;
			} else {
				elem.children.push_back(AnimToXML<ATYPE, ACONT>(*animPtr, ids));
			}
		}

		elem.children.push_back(AttrToXML(id, attr, maybeAnimId, ids));
	}

	template <AttributeType ATYPE, AttributeType SUBTYPE>
	std::string XMLWriter::AttrValueSequenceToXMLString(const IAttribute::Type<ATYPE, ATTR_SCALAR>& attr) {
     	std::stringstream s;
     	for (auto& val : attr) {
			if (&val != &attr[0])
				s << " ";
			s << AttrValueToXMLString<SUBTYPE>(val);
		}
     	return s.str();
	}

	template <AttributeType ATYPE, AttrContainerType ACONT>
	typename std::enable_if<ACONT==ATTR_SCALAR, std::string>::type XMLWriter::AttrDataToXMLString(const IAttribute::Type<ATYPE, ACONT>& attr) {
		return AttrValueToXMLString<ATYPE>(attr);
	}

	template <AttributeType ATYPE, AttrContainerType ACONT>
	typename std::enable_if<ACONT==ATTR_ARRAY, std::string>::type XMLWriter::AttrDataToXMLString(const IAttribute::Type<ATYPE, ACONT>& attr) {
     	std::ostringstream s;
     	for (auto val : attr) {
			if (&val != &attr[0])
				s << " ";
			s << AttrValueToXMLString<ATYPE>(val);
		}
     	return s.str();
	}

	template <AttributeType ATYPE, AttrContainerType ACONT>
	std::unique_ptr<XML::Element> XMLWriter::AttrToXML(const AttributeId id, const Attribute<ATYPE, ACONT>& attr, boost::optional<uint64_t> anim_id, IDState& ids) {
		std::string label = "attr";
		// TODO: add array id if it's an array
		std::vector<std::pair<std::string, std::string>> attributes = {
			{"id", ""}, // TODO: add id
			{"name", AttrIdBimap.left.at(id)}, // TODO: Add name
			{"type", std::to_string(static_cast<int>(attr.getAttrType()))}
		};

		if (ACONT == ATTR_ARRAY) {
			++ids.current_array;
			attributes.push_back({"arrayId", std::to_string(ids.current_array)});
		}

		std::string contents = AttrDataToXMLString<ATYPE, ACONT>(attr.getTypedData());
		// TODO: add animator id if it exists
		return std::unique_ptr<Element>(new Element{{}, attributes, label, contents});
	}

	template <AttributeType ATYPE, AttrContainerType ACONT>
	std::unique_ptr<XML::Element> XMLWriter::AnimToXML(const Animator<typename IAttribute::Type<ATYPE, ACONT>>& animator, IDState& ids) {
		std::string label = "anim";

		++ids.current_anim;
		ids.visited_anims[&animator] = ids.current_anim;
		std::vector<std::pair<std::string, std::string>> attributes = {
			{"id", std::to_string(ids.current_anim)}
		};

		std::string type;
		switch(animator.getAnimatorType()) {
			case REGULAR:
				type = "regular";
				break;
			default:
				// TODO: fatal error: missing enum case
				break;
		}
		attributes.push_back({"type", type});
		attributes.push_back({"dataType", std::to_string(static_cast<int>(ATYPE))});
		if (auto maybePeriod = animator.getPeriod())
			attributes.push_back({"period", std::to_string(*maybePeriod)});
		std::vector<float> pattern = animator.getPattern();
		if (!pattern.empty()) {
			std::ostringstream pat_str;
			for (auto& val : pattern) {
				if (&val != &pattern[0])
					pat_str << " ";
				// TODO: consider precision, rounding, etc.
				pat_str << val;
			}
			attributes.push_back({"pattern", pat_str.str()});
		}

		AnimationType animation_type = animator.getAnimationType();
		if (animation_type != ANIM_ONCE)
			attributes.push_back({"animationType", std::to_string(static_cast<int>(animation_type))});

		if (auto maybeEndTime = animator.getEndTime())
			// TODO: consider precision, rounding, etc.
			attributes.push_back({"endTime", std::to_string(*maybeEndTime)});

		auto seq = animator.getValueSequence();

		if (ACONT == ATTR_ARRAY)
			attributes.push_back({"numTimes", std::to_string(seq.size())});

	 	std::ostringstream contents;
	 	for (auto val : seq) {
			if (&val != &seq[0])
				contents << " ";
			contents << AttrDataToXMLString<ATYPE, ACONT>(val);
		}

		return std::unique_ptr<Element>(new Element{{}, attributes, label, contents.str()});
	}

}
}

#endif // SCENE_XML_H_
