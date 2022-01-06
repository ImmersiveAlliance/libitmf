#ifndef ELEMENTS_H_
#define ELEMENTS_H_

#include <pugixml.hpp>

class Test {
private:
	pugi::xml_node& node;
	pugi::xml_document doc;
};

#endif // ELEMENTS_H_