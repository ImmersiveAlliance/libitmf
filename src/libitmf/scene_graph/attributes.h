#ifndef ATTRIBUTES_H_
#define ATTRIBUTES_H_

#include <array>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

#include <boost/any.hpp>
#include <boost/optional.hpp>

#include "enums.h"

namespace itmf {
namespace scene {

	class IAttribute;
	template <class T>
	class Animator;

	typedef std::unique_ptr<IAttribute> AttributePtr;
	template <class T>
	using AnimatorPtr = std::shared_ptr<Animator<T>>;

	class IAttribute {
		private:
			const AttributeType type;
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

			// TODO: Replace boost::optional<T> with some form of expected<T>
			template <class T>
			static boost::optional<T> Cast(boost::any value) {
				try {
					return boost::any_cast<T>(value);
				} catch (boost::bad_any_cast &e) {
					return boost::none;
				}
			}

			inline virtual boost::any getData() const = 0;
			inline AttributeType getType() { return this->type; }
	};

	template <class T>
	class Animator {
		private:
			boost::optional<std::string> name;
			AnimatorType animator;
			AnimationType animation;
			boost::optional<float> period;
			std::vector<float> pattern;
			boost::optional<float> endTime;
			std::vector<T> valueSequence;

		public:
			Animator(const std::vector<T> sequenceIn,
					 const AnimationType animationIn,
					 const boost::optional<float> periodIn = boost::none,
					 const std::vector<float> patternIn = {},
					 const boost::optional<float> endIn = boost::none,
					 const boost::optional<std::string> nameIn = boost::none,
					 const AnimatorType animatorIn = REGULAR)
				: valueSequence(sequenceIn), animation(animationIn), period(periodIn), pattern(patternIn), endTime(endIn), name(nameIn), animator(animatorIn) { }

			inline std::vector<T> getValueSequence() { return this->valueSequence; }
			inline AnimatorType getAnimatorType() { return this->animator; }
			inline AnimationType getAnimationType() { return this->animation; }
			inline boost::optional<float> getPeriod() { return this->period; }
			inline std::vector<float> getPattern() { return this->pattern; }
			inline boost::optional<std::string> getName() { return this->name; }
			inline boost::optional<float> getEndTime() { return this->endTime; }

	};

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
			boost::optional<AnimatorPtr<Type>> animator;

		public:
			TypedAttribute(const Type dataIn) : data(dataIn), IAttribute(ATYPE) { }

			inline Type getTypedData() const { return data; }
			inline boost::any getData() const { return getTypedData(); }

			inline void setAnimator(const AnimatorPtr<Type> animIn) { this->animator = animIn; }
			inline void removeAnimator() { this->animator = boost::none; }
			boost::optional<AnimatorPtr<Type>> getAnimator() { return this->animator; }
	};

}
}

#endif // ATTRIBUTES_H_
