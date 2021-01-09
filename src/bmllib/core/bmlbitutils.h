#ifndef BMLLIB_CORE_BML_BIT_UTILS_H_
#define BMLLIB_CORE_BML_BIT_UTILS_H_

#include <vector>
#include <math.h>
//#include <boost/dynamic_bitset/dynamic_bitset.hpp>

namespace bmllib {
	/* This will have things like bit manip for bml bit sets*/
	// Helper functions
	unsigned int countBits(int number);

	// Cases where the BMLBitVector will be used per spec:
	/*
	> Decoding/encoding tags - id + type
	> Getting type
	> Decoding/encoding int32 and int64 with VSIE
	> Encoding length for string and blob
	*/
	class BMLBitVector { 
	public:
		// Constructors
		BMLBitVector();
		BMLBitVector(std::string bits);
		BMLBitVector(int32_t num);
		BMLBitVector(int64_t num);

		// Binary operators
		BMLBitVector& operator|(BMLBitVector& b);
		BMLBitVector& operator&(BMLBitVector& b);
		BMLBitVector& operator^(BMLBitVector& b);
		BMLBitVector operator<<(int amount);
		BMLBitVector operator>>(int amount);

		// Conversions
		int32_t vsie_to_int32();  // int conversion
		int32_t vuie_to_int32();
		int64_t vsie_to_int64();  // long conversion
		int64_t vuie_to_int64();  

	private:

	};
}

#endif // BMLLIB_CORE_BML_BIT_UTILS_H_