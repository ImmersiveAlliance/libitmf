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

	BMLBitVector::BMLBitVector(int num, Encoding E) : encoding(E) {
		bool is_neg = num < 0;
		// The following sets metadata to prevent having to store the bit vector as VUIE/VSIE
		// so they can be used when encoding happens
		// Design choice made to ignore the number sig '1' bits until encoding for ease in left/right
		// shifts and binary operations
		if (encoding == Encoding::VSIE) {
			if (is_neg) {
				num *= -1;
				is_negative = true;
			}
			else
				is_negative = false;
		}
		else
			is_negative = false;

		// 0 edge case
		if (num == 0) {
			bitvector.insert(bitvector.begin(), BML_BYTE_SIZE, 0);
			return;
		}
		
		// int to bits
		unsigned int quot = num;
		while (quot != 0) {
			bitvector.insert(bitvector.begin(), quot % 2);
			quot /= 2;
		}

		// Fill the rest of the byte with 0s
		int filler_bits = BML_BYTE_SIZE - (bitvector.size() % BML_BYTE_SIZE);
		if(filler_bits != BML_BYTE_SIZE)
			bitvector.insert(bitvector.begin(), filler_bits, 0);
	}

	BMLBitVector BMLBitVector::operator<<(int amount) {
		std::vector<bool> result = this->getBitVector();
		std::rotate(result.begin(), result.begin() + amount, result.end());
		for (std::reverse_iterator<std::vector<bool>::iterator> r = result.rbegin(); r < result.rbegin() + amount; r++) {
			*r = 0;
		}

		return BMLBitVector(result);
	}

	BMLBitVector BMLBitVector::operator>>(int amount) {
		std::vector<bool> result = this->getBitVector();

		bool msb = result[0];
		std::rotate(result.begin(), result.begin() + result.size() - amount, result.end());
		for (std::vector<bool>::iterator r = result.begin(); r < result.begin() + amount; r++) {
			*r = msb;
		}

		return BMLBitVector(result);
	}

	BMLBitVector BMLBitVector::operator&(BMLBitVector& rhs) {
		std::vector<bool> result;

		compareAndExtendBitVector(&rhs);

		for (int i = 0; i < rhs.getBitVectorSize(); i++)
			result.insert(result.end(), bitvector.at(i) && rhs.getBitVector().at(i));

		return BMLBitVector(result);
	}

	BMLBitVector BMLBitVector::operator|(BMLBitVector& rhs) {
		std::vector<bool> result;

		compareAndExtendBitVector(&rhs);

		for (int i = 0; i < rhs.getBitVectorSize(); i++)
			result.insert(result.end(), bitvector.at(i) || rhs.getBitVector().at(i));

		return BMLBitVector(result);
	}

	BMLBitVector BMLBitVector::operator^(BMLBitVector& rhs) {
		std::vector<bool> result;
		
		compareAndExtendBitVector(&rhs);

		for (int i = 0; i < rhs.getBitVectorSize(); i++)
			result.insert(result.end(), bitvector.at(i) ^ rhs.getBitVector().at(i));
		
		return BMLBitVector(result);
	}

	void BMLBitVector::resize(int length) {
		bitvector.insert(bitvector.begin(), length - bitvector.size(), 0);
	}

	void BMLBitVector::compareAndExtendBitVector(BMLBitVector* rhs) {
		if (getBitVectorSize() < rhs->getBitVectorSize())
			resize(rhs->getBitVectorSize());
		else if (getBitVectorSize() > rhs->getBitVectorSize())
			rhs->resize(getBitVectorSize());
	}
}