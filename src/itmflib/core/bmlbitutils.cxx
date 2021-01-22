#include "bmlbitutils.h"

namespace itmflib {
	unsigned int countBits(int num) {
		if (num < 0)
			num *= -1;

		return (int)log2(num) + 1;
	}

	unsigned int countBytes(int num) {
		int bits = countBits(num);

		if ((bits % 8) != 0)
			return (bits / 8) + 1;

		return bits / 8;
	}
	/*
	BMLBitVector::BMLBitVector(int32_t num, Encoding E) {
		int total_bytes = countBytes(num);
		// Endianess?
		for (int i = 0; i < total_bytes; i++) {
			bitvector.push_back((num >> 8 * i) & 0xFF);
		}

		// Check bits
		int total_bits = countBits(num);

	}

	BMLBitVector::BMLBitVector(int64_t num, Encoding E) {

	}

	BMLBitVector BMLBitVector::operator<<(int amount) {
		return BMLBitVector();
	}

	BMLBitVector BMLBitVector::operator>>(int amount) {
		return BMLBitVector();
	}

	BMLBitVector& BMLBitVector::operator&(BMLBitVector& b) {
		return BMLBitVector();
	}

	BMLBitVector& BMLBitVector::operator^(BMLBitVector& b) {
		return BMLBitVector();
	}
	*/
}