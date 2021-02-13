#ifndef BMLLIB_CORE_BML_BIT_UTILS_H_
#define BMLLIB_CORE_BML_BIT_UTILS_H_

#include <vector>
#include <string>
#include <math.h>
#include <iostream>
//#include <boost/dynamic_bitset/dynamic_bitset.hpp>

#define BML_BYTE_SIZE 8

/*
Implementation thoughts:

*  Do we want to encode the bits signaling number of bytes before encoding?
*  Is vector<uint8_t> best representation?
*  Should the Encoding (VSIE, VUIE) be specified?
*  BML Reader Class?

*/

namespace itmflib {
	enum Encoding
	{
		VUIE,
		VSIE
	};
	/* This will have things like bit manip for bml bit sets*/
	// Helper functions
	unsigned int countBits(int number); // counts how many bits an int will occupy (excluding sign bit)
	unsigned int countBytes(int number);

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
		BMLBitVector(int num, Encoding E = VUIE);
		// ifstream input constructor - logic for parsing mess in one place
		BMLBitVector(std::vector<bool> v, Encoding E = VUIE) : bitvector(v), encoding(E) { } // Mostly used for testing purposes
		BMLBitVector(int32_t id, int8_t type); // for tags

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

		// Conversions
		int32_t to_int32();  // int conversion
		int64_t to_int64();  // long conversions

		// Helper functions
		bool is_valid(); // Checks to see if the encoding is valid (i.e. correct number of MSBs for length)
		void resize(int length); // Resizes by adding more significant bits equal to 0
		void compareAndExtendBitVector(BMLBitVector* rhs);
	private:
		std::vector<bool> bitvector;
		Encoding encoding;
		bool is_negative;
	};

	inline bool operator==(const BMLBitVector& b1, const BMLBitVector& b2) {
		return b1.getBitVector() == b2.getBitVector();
	}
}

#endif // BMLLIB_CORE_BML_BIT_UTILS_H_