#ifndef BMLLIB_CORE_BML_BIT_UTILS_H_
#define BMLLIB_CORE_BML_BIT_UTILS_H_

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
	/* This will have things like bit manip for bml bit sets*/
	// Helper functions
	unsigned int countBits(int number); // counts how many bits an int will occupy (excluding sign bit)
	unsigned int countBytes(int number);

	// NOTES:
	// one function that changes behavior of other functions - leading to complicated, unforeseen bugs
	// prevent it from happening by mistake

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
		uint32_t to_uint32();  // unsigned int conversion (agnostic to whether or not the bitvector is encoded)
		uint64_t to_uint64();  // unsigned long conversion (agnostic to whether or not the bitvector is encoded)
		int32_t to_int32();  // int conversion (agnostic to whether or not the bitvector is encoded)
		int64_t to_int64();  // long conversions (agnostic to whether or not the bitvector is encoded)

		// TODO - determine better functionality/interface for these functions
		void prepareForEncoding(); // adds the number of significant 1 bits that signals subsequent bytes
		void encodeTag(uint32_t id, uint8_t type); // Better as output parameter? TBD

		// Function to shrink the vector if possible, for example one byte is all 0s.

		// Helper functions
		//bool is_valid(); // Checks to see if the encoding is valid (i.e. correct number of MSBs for length)
		void extend(int length); // Resizes by adding more significant bits equal to 0
		bool shrink(); // return 1 if shrink was successful, 0 if not

	private:
		std::vector<bool> bitvector;
		Encoding encoding;
		bool is_negative;

		int getFirstNonLengthBitIndex(); // Returns the index which is the first non-length bit
		void compareAndExtendBitVector(BMLBitVector* rhs); // Used in ^, |, &
	};

	inline bool operator==(const BMLBitVector& b1, const BMLBitVector& b2) {
		return b1.getBitVector() == b2.getBitVector();
	}
}

#endif // BMLLIB_CORE_BML_BIT_UTILS_H_