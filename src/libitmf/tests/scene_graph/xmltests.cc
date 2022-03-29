#include "xml.h"

#include <sstream>

#include <pugixml.hpp>

#include "gtest/gtest.h"

namespace itmf {
namespace scene {

	TEST(XMLWriteTest, WriteStreamTest) {
		pugi::xml_document doc;
		//doc.load_string("<?xml version='1.0'?><OCS2 version='1'/>");
		doc.load_file("minimal.ocs");
		std::ostringstream expected;
		doc.save(expected);

		Root root({}, "1");
		std::ostringstream actual;
		// TODO: Revisit
		//XMLWriter::WriteStream(root, actual);

		//EXPECT_EQ(actual.str(), expected.str());
	}

	//TEST(XMLWriteTest, GraphTest) {
	//	pugi::xml_document doc;
	//	doc.load_string("<?xml version='1.0'?><OCS2 version='1'><graph name='testgraph' type='3' id='1'></graph></OCS2>");
	//	std::ostringstream expected;
	//	doc.save(expected);

	//	GraphPtr graph = GraphPtr(new Graph("testgraph", GT_APP_SETTINGS));
	//	Root root({}, "1");
	//	std::ostringstream actual;
	//	XMLWriter::WriteStream(root, actual);

	//	EXPECT_EQ(actual.str(), expected.str());
	//}

	// Checks for equality of values between two Elements. Child and attribute order must match.
	// TODO: should this be an operator overload?
	bool elementsAreEqual(const XML::Element& a, const XML::Element& b) {
		if (&a == &b) return true;

		if ((a.label != b.label) ||
			(a.contents != b.contents) ||
			(a.attributes.size() != b.attributes.size() ||
			(a.children.size() != b.children.size())))
			return false;

		for (size_t i = 0; i < a.attributes.size(); ++i)
			if (a.attributes[i] != b.attributes[i])
				return false;

		for (size_t i = 0; i < a.children.size(); ++i)
			if (a.children[i] != nullptr && b.children[i] != nullptr)
				if (!elementsAreEqual(*a.children[i], *b.children[i]))
					return false;

		return true;
	}

	// Quick and dirty function to print elements recursively.
	std::string elementToString(const XML::Element& e, unsigned int padCount = 0) {
		char pad = '\t';
		std::string basePads(padCount, pad);
		std::ostringstream oss;
		oss << basePads << "Element@" << &e << ": {" << std::endl;
		oss << basePads << pad << "label: '" << e.label << "'" << std::endl;
		oss << basePads << pad << "contents: '" << e.contents << "'" << std::endl;
		oss << basePads << pad << "attributes: {" << std::endl;
		for (auto& attr : e.attributes) {
			oss << basePads << pad << pad << "'" << attr.first << "': '" << attr.second << "'," << std::endl;
		}
		oss << basePads << pad << "}" << std::endl;

		oss << basePads << pad << "children: {" << std::endl;
		for (auto& child : e.children) {
			if (child != nullptr)
				oss << elementToString(*child, padCount+2) << ",";
			else
				oss << basePads << pad << pad << "nullptr";
			oss << std::endl;
		}
		oss << basePads << pad << "}" << std::endl;

		oss << basePads << "}";
		return oss.str();
	}

	TEST(XMLWriteTest, SimpleAnimTest) {
		constexpr AttributeType attrType = AT_INT;
		constexpr AttrContainerType attrConType = ATTR_SCALAR;
		using T = IAttribute::Type<attrType, attrConType>;

		std::vector<T> sequence = {1, 2, 10, 20, 300};
		Animator<T> anim(sequence, ANIM_LOOP);
		XMLWriter::IDState state = {};

		std::unique_ptr<XML::Element> result = XMLWriter::AnimToXML<attrType, attrConType>(anim, state);

		std::vector<std::unique_ptr<XML::Element>> expectedChildren = {};
		std::vector<std::pair<std::string, std::string>> expectedAttributes = {
			{"id", "1"},
			{"type", "regular"},
			{"dataType", "2"}
		};
		std::string expectedLabel = "anim";
		std::string expectedContents = "";

		XML::Element expected = {std::move(expectedChildren), expectedAttributes, expectedLabel, expectedContents};

		//ASSERT_NE(result, nullptr) << "AnimToXML should not return a null pointer.";
		//EXPECT_TRUE(elementsAreEqual(expected, *result))
		//	<< "Actual:" << std::endl
		//	<< elementToString(*result) << std::endl
		//	<< "Expected:" << std::endl
		//	<< elementToString(expected) << std::endl;
	}
}
}
