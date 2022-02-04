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

			void toOStream(std::ostream& out) const;
			Root toRoot();
		private:
			struct Element {
				std::vector<std::unique_ptr<Element>> children;
				std::unordered_map<std::string, std::string> attributes;
				std::string label;
				std::string contents;
			};

			XML(std::unique_ptr<Element> rootIn = nullptr) : root(std::move(rootIn)) { }

			std::unique_ptr<Element> root;

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
