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

	template <class T>
	class Animator {
		public:
			Animator(const std::vector<T> sequenceIn,
					 const AnimationType animationIn,
					 const boost::optional<float> periodIn = boost::none,
					 const std::vector<float> patternIn = {},
					 const boost::optional<float> endIn = boost::none,
					 const boost::optional<std::string> nameIn = boost::none,
					 const AnimatorType animatorIn = REGULAR)
				: valueSequence(sequenceIn), animation(animationIn), period(periodIn), pattern(patternIn), endTime(endIn), name(nameIn), animator(animatorIn) { }

			std::vector<T> getValueSequence() { return this->valueSequence; }
			AnimatorType getAnimatorType() { return this->animator; }
			AnimationType getAnimationType() { return this->animation; }
			boost::optional<float> getPeriod() { return this->period; }
			std::vector<float> getPattern() { return this->pattern; }
			boost::optional<std::string> getName() { return this->name; }
			boost::optional<float> getEndTime() { return this->endTime; }

		private:
			boost::optional<std::string> name;
			AnimatorType animator;
			AnimationType animation;
			boost::optional<float> period;
			std::vector<float> pattern;
			boost::optional<float> endTime;
			std::vector<T> valueSequence;
	};

	template <class T>
	using AnimatorPtr = std::shared_ptr<Animator<T>>;


	class IAttribute {
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

			// Minimal class representing a pointer to an IAttribute.
			// Implemented using a unique_ptr for memory management
			// plus support for implicit deep copies to help Attributes
			// behave as a sort of polymorphic value.
			// Loosely based on https://stackoverflow.com/q/23726228
			class Ptr {
				private:
					std::unique_ptr<IAttribute> p;
				public:
					Ptr(std::unique_ptr<IAttribute>&& pIn = nullptr) : p(std::move(pIn)) { }
					Ptr(const Ptr& other) : p(other.p->clone()) {}

					Ptr& operator =(Ptr const& other) {
						this->p = other.p->clone();
						return *this;
					}

					IAttribute& operator *() const { return *p; }
					Ptr clone() const { return Ptr(p->clone()); }
					bool isNull() const { return p == nullptr; }
			};

			virtual std::unique_ptr<IAttribute> clone() const = 0;

			AttributeType getAttrType() const { return this->attrType; }
			AttrContainerType getContainerType() const { return this->conType; }

		private:
			template <AttributeType ATYPE>
			using BaseType = typename std::conditional<ATYPE == AT_UNKNOWN, IAttribute::Unknown,
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

		protected:
			IAttribute(AttributeType at, AttrContainerType ct) : attrType(at), conType(ct) { }

			virtual boost::any getAnyData() const = 0;

			template <AttributeType ATYPE, AttrContainerType ACONT>
			using Type = typename std::conditional<ACONT == ATTR_ARRAY, std::vector<BaseType<ATYPE>>, BaseType<ATYPE>>::type;

		public:
			// TODO: Replace boost::optional<T> with some form of expected<T>
			template <AttributeType ATYPE, AttrContainerType ACONT = ATTR_SCALAR>
			boost::optional<Type<ATYPE,ACONT>> get() const {
				try {
					return boost::any_cast<Type<ATYPE,ACONT>>(this->getAnyData());
				} catch (boost::bad_any_cast &e) {
					return boost::none;
				}
			}
			// TODO: ToString?

		private:
			const AttributeType attrType;
			const AttrContainerType conType;
	};


	template <AttributeType ATYPE, AttrContainerType ACONT = ATTR_SCALAR>
	class Attribute : public IAttribute {
		private:
			using T = Type<ATYPE,ACONT>;

		public:
			Attribute(const T dataIn) : data(dataIn), IAttribute(ATYPE, ACONT) { }

			static boost::optional<Attribute<ATYPE,ACONT>> From(const IAttribute&& attrIn) {
				if (attrIn.getAttrType() == ATYPE && attrIn.getContainerType() == ACONT) {
					return dynamic_cast<const Attribute<ATYPE,ACONT>&&>(attrIn);
				} else {
					return boost::none;
				}
			}

			T getTypedData() const { return data; }

			void setAnimator(const AnimatorPtr<T> animIn) { this->animator = animIn; }
			void removeAnimator() { this->animator = boost::none; }
			boost::optional<AnimatorPtr<T>> getAnimator() { return this->animator; }

			std::unique_ptr<IAttribute> clone() const override {
				return std::unique_ptr<Attribute<ATYPE,ACONT>>(new Attribute<ATYPE,ACONT>(*this));
			};
		protected:
			boost::any getAnyData() const override { return getTypedData(); }


		private:
			const T data;
			boost::optional<AnimatorPtr<T>> animator;

	};


	typedef IAttribute::Ptr AttributePtr;

}
}

#endif // ATTRIBUTES_H_
