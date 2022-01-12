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
	class IAttribute;
	class Pin;
	template <class T>
	class Animator;

	typedef std::shared_ptr<Graph> GraphPtr;
	typedef std::shared_ptr<Node> NodePtr;
	typedef std::unique_ptr<IAttribute> AttributePtr;

	class AnimatorPtr;

	class Root {
		private:
			std::string version;
			std::vector<GraphPtr> graphs;
		public:
	};


	class Item {
		private:
			std::string name;
			std::unordered_map<AttributeId, AttributePtr> attributes;
		public:
	};

	class Graph : public Item {
		private:
			std::vector<GraphPtr> graphs;
			std::vector<NodePtr> nodes;
			NodeGraphType type;
		public:
	};

	class Pin {
		private:
			NodePinType type;
			NodePtr node;
	};

	class Node : public Item {
		private:
			//std::vector<Pin> pins;
			std::unordered_map<PinId, Pin> pins;
			NodeType type;
		public:
	};

	// TODO: it's an interface, preface it with I
	class IAttribute {
		protected:
			IAttribute(AttributeType t) : type(t) { }

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

			virtual boost::any getDataAtTime(float time) const = 0;
	};

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

	// TODO array enum
	template <AttributeType ATYPE, AttrContainerType ACONT = ATTR_SCALAR>
	class TypedAttribute : public IAttribute {
		private:
			using DataType = typename std::conditional<ATYPE == AT_UNKNOWN, IAttribute::Unknown,
							 typename std::conditional<ATYPE == AT_BOOL, IAttribute::Bool,
							 typename std::conditional<ATYPE == AT_INT, IAttribute::Int,
							 typename std::conditional<ATYPE == AT_INT2, IAttribute::Int2,
							 typename std::conditional<ATYPE == AT_INT3, IAttribute::Int3,
							 typename std::conditional<ATYPE == AT_INT4, IAttribute::Int4,
							 typename std::conditional<ATYPE == AT_FLOAT, IAttribute::Float,
							 typename std::conditional<ATYPE == AT_FLOAT2, IAttribute::Float2,
							 typename std::conditional<ATYPE == AT_FLOAT3, IAttribute::Float3,
							 typename std::conditional<ATYPE == AT_FLOAT4, IAttribute::Float4,
							 typename std::conditional<ATYPE == AT_STRING, IAttribute::String,
							 typename std::conditional<ATYPE == AT_FILENAME, IAttribute::Filename,
							 typename std::conditional<ATYPE == AT_BYTE, IAttribute::Byte,
							 typename std::conditional<ATYPE == AT_MATRIX, IAttribute::Matrix,
							 typename std::conditional<ATYPE == AT_LONG, IAttribute::Long,
							 typename std::conditional<ATYPE == AT_LONG2, IAttribute::Long2,
							 IAttribute::Unknown >::type>::type>::type>::type>::type>::type>::type>::type>::type>::type>::type>::type>::type>::type>::type>::type;
			using Type = typename std::conditional<ACONT == ATTR_ARRAY, std::vector<DataType>, DataType>::type;

			const Type data;

			boost::optional<Animator<Type>> animator;

		public:
			TypedAttribute(const Type in_data) : data(in_data), IAttribute(ATYPE) { }

			inline Type getTypedData() const { return data; }
			inline boost::any getData() const { return getTypedData(); }
			inline boost::any getDataAtTime(const float time) const { return getTypedDataAtTime(time); }
			Type getTypedDataAtTime(const float time) const {
				boost::optional<Type> result = boost::none;
				if (animator.is_initialized())
					result = animator->getValueAtTime(time);
				return result.get_value_or(this->getTypedData());
	        };

			// TODO: Add validation
			bool addAnimator(const Animator<Type> in_anim) { this->animator = in_anim; return true; }
			void removeAnimator() { this->animator = boost::none; }
	};

}
}

#endif // ELEMENTS_H_
