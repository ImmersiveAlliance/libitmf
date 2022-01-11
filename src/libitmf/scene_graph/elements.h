#ifndef ELEMENTS_H_
#define ELEMENTS_H_

#include <string>
#include <vector>
#include <memory>
#include <array>
#include <type_traits>
#include <unordered_map>

#include <boost/any.hpp>
#include <boost/optional.hpp>
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
	template <class T>
	class Animator;

	typedef std::shared_ptr<Graph> GraphPtr;
	typedef std::shared_ptr<Node> NodePtr;
	typedef std::unique_ptr<Attribute> AttributePtr;

	class AnimatorPtr;
	//template <class T>
	//using AnimatorPtr = std::shared_ptr<Animator<T>>;

	class Root {
		private:
			std::string version;
			std::vector<GraphPtr> graphs;
		public:
	};


	class Item {
		private:
			std::string name;
			std::unordered_map<AttributeId, std::vector<AttributePtr> > attributes;
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

	class Pin {
		private:
			// TODO: Verify
			PinId id;
			NodePinType type;
			NodePtr node;
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

			// TODO: Replace boost::optional<T> with some form of expected<T>
			template <class T>
			boost::optional<T> Cast(boost::any value) {
				try {
					return boost::any_cast<T>(value);
				} catch (boost::bad_any_cast &e) {
					return boost::none;
				}
			}

			inline virtual boost::any getData() const = 0;
			inline virtual boost::any getDataArray() const = 0;

			virtual boost::any getDataAtTime(float time) const = 0;
			virtual boost::any getDataArrayAtTime(float time) const = 0;
	};

	//template <AttributeType ATYPE>
	template <class T>
	class Animator {
		private:
			//boost::optional<std::string> name; // TODO: Determine if this is allowed
			AnimatorType animator;
			AnimationType animation;
			boost::optional<float> period;
			std::vector<float> pattern;
			boost::optional<float> endTime;
			boost::optional<uint32_t> numTimes; // Only required for animated array attributes
			std::vector<T> valueSequence;

		public:
			// TODO: Implement
			boost::optional<T> getValueAtTime(const float time) const { return boost::none; }
	};

	template <AttributeType ATYPE>
	class TypedAttribute : public Attribute {
		private:
			using Type = typename std::conditional<ATYPE == AT_UNKNOWN, Attribute::Unknown,
						 typename std::conditional<ATYPE == AT_BOOL, Attribute::Bool,
						 typename std::conditional<ATYPE == AT_INT, Attribute::Int,
						 typename std::conditional<ATYPE == AT_INT2, Attribute::Int2,
						 typename std::conditional<ATYPE == AT_INT3, Attribute::Int3,
						 typename std::conditional<ATYPE == AT_INT4, Attribute::Int4,
						 typename std::conditional<ATYPE == AT_FLOAT, Attribute::Float,
						 typename std::conditional<ATYPE == AT_FLOAT2, Attribute::Float2,
						 typename std::conditional<ATYPE == AT_FLOAT3, Attribute::Float3,
						 typename std::conditional<ATYPE == AT_FLOAT4, Attribute::Float4,
						 typename std::conditional<ATYPE == AT_STRING, Attribute::String,
						 typename std::conditional<ATYPE == AT_FILENAME, Attribute::Filename,
						 typename std::conditional<ATYPE == AT_BYTE, Attribute::Byte,
						 typename std::conditional<ATYPE == AT_MATRIX, Attribute::Matrix,
						 typename std::conditional<ATYPE == AT_LONG, Attribute::Long,
						 typename std::conditional<ATYPE == AT_LONG2, Attribute::Long2,
						 Attribute::Unknown >::type>::type>::type>::type>::type>::type>::type>::type>::type>::type>::type>::type>::type>::type>::type>::type;
			const std::vector<Type> data;

			boost::optional<Animator<std::vector<Type>>> animator;

		public:
			TypedAttribute(const Type in_data) : data(1, in_data), Attribute(ATYPE) { }
			TypedAttribute(const std::vector<Type> in_data) : data(in_data), Attribute(ATYPE) { }

			inline Type getTypedData() const { return data[0]; }
			inline std::vector<Type> getTypedDataArray() const { return data; }

			inline boost::any getData() const { return getTypedData(); }
			inline boost::any getDataArray() const { return getTypedDataArray(); }

			inline boost::any getDataAtTime(const float time) const { return getTypedDataAtTime(time); }
			inline boost::any getDataArrayAtTime(const float time) const { return getTypedDataArrayAtTime(time); }

			inline Type getTypedDataAtTime(const float time) const { return getTypedDataArrayAtTime(time)[0]; };
			// REVIEW: To separate the implementation, we might consider doing something like this:
			//         https://stackoverflow.com/a/8662580
			std::vector<Type> getTypedDataArrayAtTime(float time) const {
				boost::optional<std::vector<Type>> result = boost::none;
				if (animator.is_initialized())
					result = animator->getValueAtTime(time);
				return result.get_value_or(this->getTypedDataArray());
			}
	};

}
}

#endif // ELEMENTS_H_
