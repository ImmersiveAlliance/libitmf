#ifndef SCENE_XML_H_
#define SCENE_XML_H_

#include <vector>
#include <unordered_map>
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
			static XML FromRoot(const Root root);
			static XML FromIStream(std::istream& is);
			// TODO: Maybe split it out
			//XMLReader::ReadFile(instream);
			//XMLWriter::WriteFile(outstream);

			void toOStream(std::ostream& out) const;
			Root toRoot();
		private:
			// TODO: this is a serialization, maybe more general than XML. Consider for JSON.
			struct Element {
				std::vector<std::unique_ptr<Element>> children;
				std::unordered_map<std::string, std::string> attributes;
				std::string label;
				std::string contents;
			};

			XML(std::unique_ptr<Element> headIn = nullptr) : head(std::move(headIn)) { }

			std::unique_ptr<Element> head;

			// Scene Graph <-> XML conversion

			static std::unique_ptr<Element> RootToXML(const Root& root);
			static std::unique_ptr<Element> GraphToXML(const Graph& graph);
			static std::unique_ptr<Element> NodeToXML(const Node& node);
			static std::unique_ptr<Element> PinToXML(const PinId id, const Pin& pin);
			//static std::unique_ptr<Element> AttrToXML(const AttributeId id, const IAttribute& attr); // Might want to eliminate this?
			//template <class T>
			//static std::unique_ptr<Element> AnimToXML(const Animator<T>& animator);
			static void AppendItemData(const Item& item, Element& elem);
			static void AppendAttributeData(const AttributeId& id, const IAttribute&& attr, Element& elem);
			template <AttributeType ATYPE, AttrContainerType ACONT>
			static void AppendTypedAttributeData(const AttributeId& id, const IAttribute&& iattr, Element& elem) {
				auto attr = Attribute<ATYPE, ACONT>::From(std::move(iattr));
				// TODO
				//if attr.hasAnimator {
				//		animid = ...;
				//		elem.children.append(AnimToXML(anim, animId));
				//	}
				//elem.children.append(attr, animId)
			}

			// Pugi Implementation
			static XML FromIStream_PugiImpl(std::istream& is);
			void toOstream_PugiImpl(std::ostream& out) const;
			static std::unique_ptr<Element> PugiRecurseCreateElement(const pugi::xml_node& node);
			static void PugiRecurseCreatePugi(const Element& elem, pugi::xml_node&& nodeOut);
			// End Pugi Implementation

	};

}
}

#endif // SCENE_XML_H_
