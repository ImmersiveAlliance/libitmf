#ifndef ELEMENTS_H_
#define ELEMENTS_H_

#include <string>
#include <vector>
#include <memory>
#include <array>
#include <type_traits>

#include <boost/any.hpp>
#include <pugixml.hpp>

#include "enums.h"

namespace itmf {
namespace scene {

	class Root;
	class Item;
	class Graph;
	class Node;
	class Attribute;
	class Pin;
	class Animator;

	typedef std::shared_ptr<Graph> GraphPtr;
	typedef std::shared_ptr<Node> NodePtr;
	typedef std::unique_ptr<Animator> AttributePtr;
	typedef std::shared_ptr<Animator> AnimatorPtr;

	class Root {
		private:
			std::string version;
			std::vector<GraphPtr> graphs;
		public:
	};


	class Item {
		private:
			std::string name;
			std::vector<AttributePtr> attributes;
		public:
	};

	class Graph : public Item {
		private:
			std::vector<GraphPtr> graphs;
			std::vector<NodePtr> nodes;
			NodeGraphType type;
		public:
	};

	class Node : public Item {
		private:
			std::vector<Pin> pins;
			NodeType type;
		public:
	};

	class Attribute {
		protected:
			Attribute(AttributeType t) : type(t) { }
		public:
			typedef std::string Unknown;
			typedef bool Bool;
			typedef int32_t Int;
			typedef std::array<Int, 2> Int2;
			typedef std::array<Int, 3> Int3;
			typedef std::array<Int, 4> Int4;
			typedef float Float;
			typedef std::array<Float, 2> Float2;
			typedef std::array<Float, 3> Float3;
			typedef std::array<Float, 4> Float4;
			typedef std::string String;
			typedef String Filename;
			typedef uint8_t Byte;
			typedef std::array<Float4, 3> Matrix;
			typedef int64_t Long;
			typedef std::array<Long, 2> Long2;

			const AttributeType type;

			inline virtual boost::any getData() const = 0;
	};

	template <AttributeType ATYPE>
	class TypedAttribute : public Attribute {
		private:
			using Type = typename std::conditional<ATYPE == AT_UNKNOWN, Unknown,
						 typename std::conditional<ATYPE == AT_BOOL, Bool,
						 typename std::conditional<ATYPE == AT_INT, Int,
						 typename std::conditional<ATYPE == AT_INT2, Int2,
						 typename std::conditional<ATYPE == AT_INT3, Int3,
						 typename std::conditional<ATYPE == AT_INT4, Int4,
						 typename std::conditional<ATYPE == AT_FLOAT, Float,
						 typename std::conditional<ATYPE == AT_FLOAT2, Float2,
						 typename std::conditional<ATYPE == AT_FLOAT3, Float3,
						 typename std::conditional<ATYPE == AT_FLOAT4, Float4,
						 typename std::conditional<ATYPE == AT_STRING, String,
						 typename std::conditional<ATYPE == AT_FILENAME, Filename,
						 typename std::conditional<ATYPE == AT_BYTE, Byte,
						 typename std::conditional<ATYPE == AT_MATRIX, Matrix,
						 typename std::conditional<ATYPE == AT_LONG, Long,
						 typename std::conditional<ATYPE == AT_LONG2, Long2,
						 Unknown >::type>::type>::type>::type>::type>::type>::type>::type>::type>::type>::type>::type>::type>::type>::type>::type;

			Type data;

		public:
			TypedAttribute(Type in_data) : data(in_data), Attribute(ATYPE) { }

			inline boost::any getData() const { return getTypedData(); }
			inline Type getTypedData() const { return data; }
	};

	class Pin {

	};

	class Animator {

	};


}
}

#endif // ELEMENTS_H_
