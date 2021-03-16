#ifndef BMLLIB_CORE_BML_BIT_UTILS_H_
#define BMLLIB_CORE_BML_BIT_UTILS_H_

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>
#include <sstream>
#include <iterator>
//#include <boost/dynamic_bitset/dynamic_bitset.hpp>

#define BML_BYTE_SIZE 8

namespace itmflib {
	enum Encoding
	{
		VUIE,
		VSIE
	};

	// Cases where the BMLBitVector will be used per spec:
	/*
	> Decoding/encoding tags - id + type
	> Getting type
	> Decoding/encoding int32 and int64 with VSIE
	> Encoding length for string and blob
	*/
	class BMLBitVector {
	public:
		// Constructors - will convert to bitvector based on encoding method (default is VUIE)
		BMLBitVector() : encoding(Encoding::VUIE), is_negative(false), bitvector(std::vector<bool>{}) { }
		BMLBitVector(std::string bits, Encoding E = VUIE);
		BMLBitVector(int64_t num, Encoding E = VUIE);
		BMLBitVector(std::vector<bool> v, Encoding E = VUIE) : bitvector(v), encoding(E) { } // Mostly used for testing purposes

		// Operators
		BMLBitVector operator|(BMLBitVector& rhs);
		BMLBitVector operator&(BMLBitVector& rhs);
		BMLBitVector operator^(BMLBitVector& rhs);
		BMLBitVector operator<<(int amount);
		BMLBitVector operator>>(int amount);

		// Getters/Setters
		std::vector<bool> getBitVector() const { return bitvector; }
		bool getIsNegative() const { return is_negative; }
		int getBitVectorSize() const { return bitvector.size(); }

		// Conversions - Encode/decode
		uint32_t to_uint32();  // unsigned int conversion
		uint64_t to_uint64();  // unsigned long conversion 
		int32_t to_int32();  // int conversion 
		int64_t to_int64();  // long conversions
		std::vector<char> to_charvector(); // to char vector for writing

		/*// TODO - determine better functionality/interface for this function
		void encodeTag(uint32_t id, uint8_t type); // Better as output parameter? TBD*/

		// Helper functions
		void extend(int byte_length); // Resizes by adding more significant bits equal to 0
		bool shrink(); // Shrinks the vector returning if successful

	private:
		std::vector<bool> bitvector;
		Encoding encoding;
		bool is_negative;

		int getFirstNonLengthBitIndex(); // Returns the index which is the first non-length bit
		void compareAndExtendBitVector(BMLBitVector* rhs); // Used in ^, |, &
		void encodeByteLengthIndicatorBits(std::vector<bool>* bits, bool sign_bit); // Used for bitvectors that are missing the byte length bits (used in shrinking and constructor)
	};

	inline bool operator==(const BMLBitVector& b1, const BMLBitVector& b2) {
		return b1.getBitVector() == b2.getBitVector();
	}

}

#endif // BMLLIB_CORE_BML_BIT_UTILS_H_