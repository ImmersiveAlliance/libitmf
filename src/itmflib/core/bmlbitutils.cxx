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

	BMLBitVector::BMLBitVector(int64_t num, Encoding E) : encoding(E) {
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
		uint64_t quot = num;
		while (quot != 0) {
			bitvector.insert(bitvector.begin(), quot % 2);
			quot /= 2;
		}

		// Fill the rest of the byte with 0s
		int filler_bits = BML_BYTE_SIZE - (bitvector.size() % BML_BYTE_SIZE);
		if (filler_bits != BML_BYTE_SIZE)
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

	void BMLBitVector::prepareForEncoding() {
		// Check number of bytes
		int num_sig_1_bits = (bitvector.size() / 8) - 1; // bitvector should always be a multiple of 8

		// See if there is space to put it in existing vector
		auto it = std::find(bitvector.begin(), bitvector.end(), true);
		if (it != bitvector.end()) {
			int index = it - bitvector.begin();

			switch (encoding)
			{
			case VUIE:
				if (index >= num_sig_1_bits + 1) { // including 0
					for (int i = 0; i < num_sig_1_bits; i++) {
						bitvector[i] = 1;
					}
				}
				// Extend vector as needed
				else {
					num_sig_1_bits++;
					std::vector<bool> extra_byte;
					extra_byte.insert(extra_byte.begin(), 8 - num_sig_1_bits, 0);
					extra_byte.insert(extra_byte.begin(), num_sig_1_bits, 1);
					bitvector.insert(bitvector.begin(), extra_byte.begin(), extra_byte.end());
				}

				break;
			case VSIE:
				if (index >= num_sig_1_bits + 2) { // including 0 and sign bit
					for (int i = 0; i < num_sig_1_bits; i++) {
						bitvector[i] = 1;
					}

					bitvector[num_sig_1_bits + 1] = is_negative;
				}
				// Extend vector as needed
				else {
					std::vector<bool> extra_byte;

					// Vectors size of 7 bytes need to be extended to 9 bytes per spec
					if (num_sig_1_bits == 6) {
						bitvector.insert(bitvector.begin(), 8, 0);
						num_sig_1_bits++;
					}
					num_sig_1_bits++; // since we are extending the vector, need to take into account new byte

					int num_padding_bits = 8 - num_sig_1_bits - 2;

					if (num_padding_bits > 0)
						extra_byte.insert(extra_byte.begin(), num_padding_bits, 0);

					extra_byte.insert(extra_byte.begin(), is_negative);
					if (num_sig_1_bits != 8) {
						extra_byte.insert(extra_byte.begin(), 0);
					}
					else { // 64 subsequent bits
						num_sig_1_bits--; // 7 num_sig_1_bits indicate 64 bits rather than 8 per spec
					}
					extra_byte.insert(extra_byte.begin(), num_sig_1_bits, 1);
					bitvector.insert(bitvector.begin(), extra_byte.begin(), extra_byte.end());
				}

				break;
			default:
				break;
			}
		}
	}

	uint32_t BMLBitVector::to_uint32() {
		int num_bytes = bitvector.size() / 8;

		std::ostringstream oss;
		uint32_t r = 0;
		if (!bitvector.empty()) {
			if (num_bytes > 4) {
				int beginning_index = bitvector.size() - 31;
				try {
					std::copy(bitvector.begin() + beginning_index, bitvector.end(), std::ostream_iterator<bool>(oss));
				}
				catch (const std::invalid_argument&) {} // TBD
				catch (const std::out_of_range&) {}
			}
			else {
				try{
					std::copy(bitvector.begin(), bitvector.end(), std::ostream_iterator<bool>(oss));
				}
				catch (const std::invalid_argument&) {} // TBD
				catch (const std::out_of_range&) {}
			}
			r = std::stoul(oss.str(), 0, 2);
		}

		return r;
	}

	uint64_t BMLBitVector::to_uint64() {
		std::ostringstream oss;
		uint64_t r = 0;
		if (!bitvector.empty()) {
			try {
				std::copy(bitvector.begin(), bitvector.end(), std::ostream_iterator<bool>(oss));
			}
			catch (const std::invalid_argument&) {} // TBD
			catch (const std::out_of_range&) {}

			r = std::stoull(oss.str(), 0, 2);
		}

		return r;
	}

	int32_t BMLBitVector::to_int32() {
		int num_bytes = bitvector.size() / 8;

		std::ostringstream oss;
		int32_t r = 0;
		if (!bitvector.empty()) {
			if (num_bytes > 4) {
				int beginning_index = bitvector.size() - 31;
				try {
					std::copy(bitvector.begin() + beginning_index, bitvector.end(), std::ostream_iterator<bool>(oss));
				}
				catch (const std::invalid_argument&) {} // TBD
				catch (const std::out_of_range&) {}
			}
			else {
				try {
					std::copy(bitvector.begin(), bitvector.end(), std::ostream_iterator<bool>(oss));
				}
				catch (const std::invalid_argument&) {} // TBD
				catch (const std::out_of_range&) {}
			}
			
			r = std::stol(oss.str(), 0, 2);
			if (is_negative)
				return r * -1;
		}

		return r;
	}

	int64_t BMLBitVector::to_int64() {
		std::ostringstream oss;
		int64_t r = 0;
		if (!bitvector.empty()) {
			try {
				std::copy(bitvector.begin(), bitvector.end(), std::ostream_iterator<bool>(oss));
			}
			catch (const std::invalid_argument&) {} // TBD
			catch (const std::out_of_range&) {}

			r = std::stoull(oss.str(), 0, 2);
		}

		if (is_negative)
			r * -1;

		return r;
	}

	void BMLBitVector::encodeTag(uint32_t id, uint8_t type) {
		// TODO - eliminate code reuse?
		uint32_t quot = id;
		while (quot != 0) {
			bitvector.insert(bitvector.begin(), quot % 2);
			quot /= 2;
		}

		// Fill the rest of the byte with 0s
		int filler_bits = BML_BYTE_SIZE - (bitvector.size() % BML_BYTE_SIZE);
		if (filler_bits != BML_BYTE_SIZE)
			bitvector.insert(bitvector.begin(), filler_bits, 0);

		(*this) = (*this) << 3;
		BMLBitVector t(type);
		(*this) = (*this) | t;
	}
}