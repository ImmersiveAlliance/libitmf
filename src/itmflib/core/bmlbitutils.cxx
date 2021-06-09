#include "bmlbitutils.h"

// TODO - function comments

namespace itmflib {
	/**
		Takes in an integer and creates the BMLBitVector with the byte length indicator
		bits per the specification.
		@params
			int64_t num: number to encode
			Encoding E: VUIE (default) of VSIE
	*/
	BMLBitVector::BMLBitVector(int64_t num, Encoding E) : encoding(E) {
		bool is_neg = num < 0;
		
		// TODO - replace this with the sign bit and remove is_negative
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

		// Encode the byte length indicator bits
		encodeByteLengthIndicatorBits(&bitvector, is_neg);
	}

	BMLBitVector::BMLBitVector(unsigned char& v, Encoding E) : encoding(E), is_negative(false) {
		for (int i = 0; i < 8; ++i) {
			bool bit = (v >> i) & 1;
			bitvector.push_back(bit);
		}
	}

	/**
		Arithmetic left shift operator on the bit vector. The left shift begins after the byte length indicator bits
		to the end of the bit vector. 
		@params
			int amount: the amount to left shift. (TODO - exception if the amount is greater than length)
		@return
			A new BMLBitVector with the left shifted bit vector.

		TODO - assertion that amount is adequate to shift
	*/
	BMLBitVector BMLBitVector::operator<<(int amount) {
		std::vector<bool> result = this->getBitVector();
		// for VSIE the number of indicator bits (including sign bit)
		auto begin = result.begin() + getFirstNonLengthBitIndex();
		std::vector<bool> lost_info(begin, begin + amount);

		std::rotate(begin, begin + amount, result.end());
		for (std::reverse_iterator<std::vector<bool>::iterator> r = result.rbegin(); r < result.rbegin() + amount; r++) {
			*r = 0;
		}

		// erase length bits
		result.erase(result.begin(), begin);

		// insert any lost information
		if (lost_info != std::vector<bool>(amount, 0)) {
			result.insert(result.begin(), lost_info.begin(), lost_info.end());
		}

		// re-encode
		encodeByteLengthIndicatorBits(&result, is_negative);

		return BMLBitVector(result);
	}

	/**
		Right shift operator on the bit vector. The right shift begins after the byte length indicator bits
		to the end of the bit vector.
		@params
			int amount: the amount to right shift (TODO - assertion if this is larger than the bit vector size)
		@return
			A new BMLBitVector with the right shifted bit vector.
		TODO - revisit to comply with arithmetic right shift
	*/
	BMLBitVector BMLBitVector::operator>>(int amount) {
		std::vector<bool> result = this->getBitVector();

		// TODO - change MSB to the value after byte size indicator bits (and sign bit if VSIE)
		// rotate beginning with the first non-byte size indicator bit
		int first_non_length_bit_index = getFirstNonLengthBitIndex();
		bool msb = result[first_non_length_bit_index];
		auto rend = result.rend() - first_non_length_bit_index;
		std::rotate(result.rbegin(), result.rbegin() + amount, rend);
		auto begin = result.begin() + first_non_length_bit_index;
		for (auto r = begin; r < begin + amount; r++) {
			*r = 0; // need to discuss this
		}

		return BMLBitVector(result);
	}

	/**
		And operator for the BMLBitVector. First, compares the bit vector and extends one if they are 
		not the same size. This will have both the bit vectors the same length and with the same byte
		length indicator bits. The and operation will begin after the byte length bits.
		@params
			BMLBitVector& rhs: right hand side of the &.
		@return
			A new BMLBitVector containing the resulting bit vector of the same length of the bit vectors
			under going &.
	*/
	BMLBitVector BMLBitVector::operator&(BMLBitVector& rhs) {
		std::vector<bool> result;

		compareAndExtendBitVector(&rhs);
		int beginning_index = getFirstNonLengthBitIndex();
		for (int i = 0; i < beginning_index; i++)
			result.push_back(bitvector[i]);

		for (int i = beginning_index; i < rhs.getBitVectorSize(); i++)
			result.insert(result.end(), bitvector.at(i) && rhs.getBitVector().at(i));

		return BMLBitVector(result);
	}

	/**
		Or operator for the BMLBitVector. First, compares the bit vector and extends one if they are 
		not the same size. This will have both the bit vectors the same length and with the same byte
		length indicator bits. The or operation will begin after the byte length bits.
		@params
			BMLBitVector& rhs: right hand side of the |.
		@return
			A new BMLBitVector containing the resulting bit vector of the same length of the bit vectors
			under going |.
	*/
	BMLBitVector BMLBitVector::operator|(BMLBitVector& rhs) {
		std::vector<bool> result;

		compareAndExtendBitVector(&rhs);

		int beginning_index = getFirstNonLengthBitIndex();
		for (int i = 0; i < beginning_index; i++)
			result.push_back(bitvector[i]);

		for (int i = beginning_index; i < rhs.getBitVectorSize(); i++)
			result.insert(result.end(), bitvector.at(i) || rhs.getBitVector().at(i));
		
		return BMLBitVector(result);
	}

	/**
		Xor operator for the BMLBitVector. First, compares the bit vector and extends one if they are
		not the same size. This will have both the bit vectors the same length and with the same byte
		length indicator bits. The xor operation will begin after the byte length bits.
		@params
			BMLBitVector& rhs: right hand side of the ^.
		@return
			A new BMLBitVector containing the resulting bit vector of the same length of the bit vectors
			under going ^.
	*/
	BMLBitVector BMLBitVector::operator^(BMLBitVector& rhs) {
		std::vector<bool> result;

		compareAndExtendBitVector(&rhs);
		// The vectors will be the same size now
		// copy over the length bits
		int beginning_index = getFirstNonLengthBitIndex();
		for (int i = 0; i < beginning_index; i++)
			result.push_back(bitvector[i]);

		for (int i = beginning_index; i < rhs.getBitVectorSize(); i++)
			result.insert(result.end(), bitvector.at(i) ^ rhs.getBitVector().at(i));

		return BMLBitVector(result);
	}

	/**
		Extends the bit vector by filling in the MSBs with 0. Updates the byte length indicator
		bits. Throws exception if the byte_length is less than or equal to the current byte length.
		@params
			int byte_length: the new size of the bit vector in bytes.
	*/
	void BMLBitVector::extend(int byte_length) {
		if (byte_length <= (bitvector.size() / 8))
			throw "Byte length must be greater than the bit vector's current size!";

		int old_length_bit_index = getFirstNonLengthBitIndex();
		std::vector<bool> extension;
		for (int i = 0; i < old_length_bit_index; i++) {
			extension.push_back(bitvector[i]); // this didn't work with copy weirdly
		}
		
		for (int i = 0; i < old_length_bit_index; i++) {
			bitvector[i] = 0;
		}

		int bit_size_difference = (byte_length * BML_BYTE_SIZE) - bitvector.size();
		int byte_size_difference = bit_size_difference / BML_BYTE_SIZE;
		extension.insert(extension.begin(), byte_size_difference, 1);

		bitvector.insert(bitvector.begin(), bit_size_difference - extension.size(), 0);
		bitvector.insert(bitvector.begin(), extension.begin(), extension.end());
	}

	/**
		Compares two bit vectors and extends one if they are not the same size to the
		size of the greater length bit vector.
		@params
			BMLBitVector* rhs: pointer to the bit vector this bit vector is comparing to.
	*/
	void BMLBitVector::compareAndExtendBitVector(BMLBitVector* rhs) {
		if (getBitVectorSize() < rhs->getBitVectorSize())
			extend(rhs->getBitVectorSize() / BML_BYTE_SIZE);
		else if (getBitVectorSize() > rhs->getBitVectorSize())
			rhs->extend(getBitVectorSize() / BML_BYTE_SIZE);
	}

	/**
		Shrinks the bit vector if possible. Ignores the byte length indicator bits if it is found
		they are contained in their own byte without bits relating to the integer. Takes all the bits
		relating to the integer and creates a new std::vector<bool> to reencode the byte length.
		Replaces bitvector if it is found to be smaller.
		@return
			Boolean indicating if the shrink was successful or not.
		TODO - Iron out bugs
	*/
	bool BMLBitVector::shrink() {
		// Edge case with vector size = 8 return false
		if (bitvector.size() == 8)
			return false;

		// Get first byte
		std::vector<bool> length_bits(bitvector.begin(), bitvector.begin() + getFirstNonLengthBitIndex());
		auto it = std::find(bitvector.begin() + getFirstNonLengthBitIndex(), bitvector.end(), true);
		if (it != bitvector.end()) {
			int index = it - bitvector.begin();

			if (index < BML_BYTE_SIZE) // if means first byte contains a 1
				return false;

			it = std::find(bitvector.begin() + BML_BYTE_SIZE, bitvector.end(), true); // finds first 1 outside of first byte

			std::vector<bool> value_bits(it, bitvector.end());
			switch (encoding)
			{
			case VUIE:
				encodeByteLengthIndicatorBits(&value_bits, false);
				break;
			case VSIE:
			{
				bool sign_bit = length_bits.back();
				encodeByteLengthIndicatorBits(&value_bits, sign_bit);
				break;
			}
			default:
				break;
			}

			// TODO - this check could be more verbose
			if (bitvector.size() > value_bits.size()) {
				bitvector = value_bits;
				
				return true;
			}
			else {
				return false;
			}
		}
		else {
			// this means it is just an empty vector
			bitvector = { 0,0,0,0,0,0,0,0 };

			return true;
		}
		
		return false;
	}

	/**
		Converts the bit vector to an unsigned 32 bit integer. Should only be applied to VUIE, but functionality
		still works for VSIE. If the bitvector is greater than 32 bits, it takes the last 32 bits and converts
		those to an integer. Bit vectors smaller than or equal to 32 bits will have the byte length indicator bits
		ignored when converting.
		@return
			uint32_t of the bitvector.
	*/
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
					std::copy(bitvector.begin() + getFirstNonLengthBitIndex(), bitvector.end(), std::ostream_iterator<bool>(oss));
				}
				catch (const std::invalid_argument&) {} // TBD
				catch (const std::out_of_range&) {}
			}
			r = std::stoul(oss.str(), 0, 2);
		}

		return r;
	}

	/**
		Converts the bit vector to an unsigned 64 bit integer. Should only be applied to VUIE, but functionality
		still works for VSIE. Will ignore the byte length indicator bits.
		@return
			uint64_t of the bitvector.
	*/
	uint64_t BMLBitVector::to_uint64() {
		std::ostringstream oss;
		uint64_t r = 0;
		int index = getFirstNonLengthBitIndex(); 
		if (!bitvector.empty()) {
			try {
				std::copy(bitvector.begin() + index, bitvector.end(), std::ostream_iterator<bool>(oss));
			}
			catch (const std::invalid_argument&) {} // TBD
			catch (const std::out_of_range&) {}

			r = std::stoull(oss.str(), 0, 2);
		}

		return r;
	}

	/**
		Converts the bit vector to an signed 32 bit integer. Should only be applied to VSIE, but functionality
		still works for VUIE. If the bitvector is greater than 32 bits, it takes the last 32 bits and converts
		those to an integer. Bit vectors smaller than or equal to 32 bits will have the byte length indicator bits
		ignored when converting.
		@return
			int32_t of the bitvector.
	*/
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
					std::copy(bitvector.begin() + getFirstNonLengthBitIndex(), bitvector.end(), std::ostream_iterator<bool>(oss));
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

	/**
		Converts the bit vector to an unsigned 64 bit integer. Should only be applied to VSIE, but functionality
		still works for VUIE. Will ignore the byte length indicator bits.
		@return
			int64_t of the bitvector.
	*/
	int64_t BMLBitVector::to_int64() {
		std::ostringstream oss;
		int64_t r = 0;
		if (!bitvector.empty()) {
			try {
				std::copy(bitvector.begin() + getFirstNonLengthBitIndex(), bitvector.end(), std::ostream_iterator<bool>(oss));
			}
			catch (const std::invalid_argument&) {} // TBD
			catch (const std::out_of_range&) {}

			r = std::stoull(oss.str(), 0, 2);
		}

		if (is_negative)
			r * -1;

		return r;
	}

	/**
	
	*/
	std::vector<char> BMLBitVector::to_charvector() {
		std::vector<char> ret;
		for (unsigned int it = 0; it < getBitVectorSize(); it += BML_BYTE_SIZE) {
			int leng = it + 8;
			std::vector<bool> chunk(bitvector.begin() + it, bitvector.begin() + leng);
			
			std::ostringstream oss;
			int i = 0;
			if (!chunk.empty()) {
				try {
					std::copy(chunk.begin(), chunk.end(), std::ostream_iterator<bool>(oss));
					i = std::stoi(oss.str(), 0, 2);
				}
				catch (const std::invalid_argument&) { std::cerr << "Invalid argument\n"; }
				catch (const std::out_of_range&) { std::cerr << "Out of range\n"; }
			}
			char r = i;
			ret.push_back(r);
		}

		return ret;
	}

	/**
		Gets the first bit index that is not a byte length indicator bit.
		@return
			The first non-byte length indicator index.
	*/
	int BMLBitVector::getFirstNonLengthBitIndex() {
		int num_bytes = bitvector.size() / 8;

		if (num_bytes == 9)
			return num_bytes - 1;

		switch (encoding) {
		case(VSIE):
			return num_bytes + 1;

		case(VUIE):
			return num_bytes;
		}
	}

	/**
		Encodes the byte length indicator bits per the Container specification. Functionality for both
		VUIE and VSIE.
		@params
			std::vector<bool>* bits: pointer to the bits that will have the byte length indicator bits
			added to them.
			bool sign_bit: 1 for negative, 0 for positive. Ignored for VUIE.
	*/
	void BMLBitVector::encodeByteLengthIndicatorBits(std::vector<bool>* bits, bool sign_bit) {
		int remainder = bits->size() % BML_BYTE_SIZE;
		int num_bytes = bits->size() / BML_BYTE_SIZE;
		if (remainder != 0) // when dividing by 8, it will take the floor of value so need to increment to reflect true num bytes
			num_bytes++;

		int num_byte_length_bits = 0;

		if (num_bytes != 0)
			num_byte_length_bits = num_bytes - 1;

		// Switch based on encoding (implementation is not very elegant)
		switch (encoding) {
		case(VSIE):
		{
			if (remainder != 0) {
				// The first byte is not full, maybe enough bits to encode length
				int num_empty_bits = BML_BYTE_SIZE - remainder;
				if (num_empty_bits >= (num_byte_length_bits + 2)) {
					// enough bits
					int num_filler_bits = num_empty_bits - num_byte_length_bits - 2; // bits that just need to be filled w 0
					bits->insert(bits->begin(), num_filler_bits, 0);
					bits->insert(bits->begin(), sign_bit);

					if (num_bytes > 1) {
						bits->insert(bits->begin(), 0);
						bits->insert(bits->begin(), num_byte_length_bits, 1);
					}
					else
						bits->insert(bits->begin(), 0);

					break;
				}
				else {
					// not enought bits in first byte
					bits->insert(bits->begin(), num_empty_bits, 0);
				}
			}

			// Not enough space in the first byte to encode length, so extend it
			num_bytes++; // includes the byte that is going to be added

			// Vectors of 7 bytes have to be expanded to 8 bytes per spec
			if (num_bytes == 8) {
				bits->insert(bits->begin(), BML_BYTE_SIZE, 0);
				num_bytes++;
			}

			num_byte_length_bits = num_bytes - 1; // reset

			if (num_byte_length_bits == 8)
				num_byte_length_bits--; // per spec, 9 byte length have 7 indicator bits plus sign bit
			std::vector<bool> extra_byte;

			extra_byte.insert(extra_byte.begin(), num_byte_length_bits, 1);
			if (num_bytes == 9)
				extra_byte.insert(extra_byte.end(), sign_bit);
			else {
				extra_byte.insert(extra_byte.end(), 0);
				extra_byte.insert(extra_byte.end(), sign_bit);
				extra_byte.insert(extra_byte.end(), BML_BYTE_SIZE - extra_byte.size(), 0);
			}

			bits->insert(bits->begin(), extra_byte.begin(), extra_byte.end());

			break;
		}
		case(VUIE):
		{
			if (remainder != 0) {
				// might be enough bits to encode length in first byte
				int num_empty_bits = BML_BYTE_SIZE - remainder;
				if (num_empty_bits >= num_bytes) {
					int filler_bits = num_empty_bits - num_byte_length_bits;
					bits->insert(bits->begin(), filler_bits, 0);
					bits->insert(bits->begin(), num_byte_length_bits, 1);

					break;
				}
				else {
					bits->insert(bits->begin(), num_empty_bits, 0);
				}
			}

			// no space so add extra byte
			num_bytes++;
			num_byte_length_bits++;
			std::vector<bool> extra_byte;
			int filler_bits = BML_BYTE_SIZE - num_byte_length_bits;
			extra_byte.insert(extra_byte.begin(), filler_bits, 0);
			extra_byte.insert(extra_byte.begin(), num_byte_length_bits, 1);
			bits->insert(bits->begin(), extra_byte.begin(), extra_byte.end());


			break;
		}
		default:
			break;
		}
	}

	/*
	// TODO - figure out a better interface for encoding tags - does a tag need to be its own class? static?
	// static or in another class/namespace?
	// return BMLBitVector
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
	*/
}