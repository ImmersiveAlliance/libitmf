#include <bmltypes.h>

namespace itmflib {

	// interface


	// global functions
	std::vector<char> encodeTag(int id, int type_id) {
		BMLBitVector tag(id);
		tag = tag << 3;
		BMLBitVector typeBitVector(type_id);
		tag = tag | typeBitVector;
		return tag.to_charvector();
	}

// int
	std::vector<char> BMLint::encodeValue() {
		BMLBitVector b(value, Encoding::VSIE);

		return b.to_charvector();
	}

// long
	std::vector<char> BMLlong::encodeValue() {
		BMLBitVector b(value, Encoding::VSIE);

		return b.to_charvector();
	}

// single
	std::vector<char> BMLsingle::encodeValue() {
		std::vector<char> encoded_value;
		uint32_t bits = 0;
		memcpy(&bits, &value, sizeof value);
		encoded_value.push_back((bits) * 0xFF);
		encoded_value.push_back((bits >> 8) * 0xFF);
		encoded_value.push_back((bits >> 16) * 0xFF);
		encoded_value.push_back((bits >> 24) * 0xFF);

		return encoded_value;
	}

// double
	std::vector<char> BMLdouble::encodeValue() {
		std::vector<char> encoded_value;
		uint32_t bits = 0;
		memcpy(&bits, &value, sizeof value);
		encoded_value.push_back((bits) * 0xFF);
		encoded_value.push_back((bits >> 8) * 0xFF);
		encoded_value.push_back((bits >> 16) * 0xFF);
		encoded_value.push_back((bits >> 24) * 0xFF);
		encoded_value.push_back((bits >> 32) * 0xFF);
		encoded_value.push_back((bits >> 40) * 0xFF);
		encoded_value.push_back((bits >> 48) * 0xFF);
		encoded_value.push_back((bits >> 56) * 0xFF);

		return encoded_value;
	}

// string
	std::vector<char> BMLstring::encode() {
		std::vector<char> encoded_vector;
		// encode tag
		std::vector<char> encoded_tag = encodeTag(id, type_id);

		encoded_vector.insert(encoded_vector.begin(), encoded_tag.begin(), encoded_tag.end());

		// encode value
		std::vector<char> encoded_length = encodeLength();
		encoded_vector.insert(encoded_vector.end(), encoded_length.begin(), encoded_length.end());

		std::vector<char> encoded_value = encodeValue();
		encoded_vector.insert(encoded_vector.end(), encoded_value.begin(), encoded_value.end());

		return encoded_vector;
	}

	std::vector<char> BMLstring::encodeLength() {
		std::vector<char> encoded_value = BMLBitVector(length).to_charvector();

		return encoded_value;
	}

	std::vector<char> BMLstring::encodeValue() {
		std::vector<char> encoded_value;
		encoded_value.insert(encoded_value.end(), value.begin(), value.end());
		
		return encoded_value;
	}

	void BMLstring::load(std::ifstream& infile) {
		char firstByte; // read first byte to determine number of sub. bytes
		infile.read(&firstByte, 1);
		BMLBitVector tag(firstByte);
		// left of here
	}

// blob
	std::vector<char> BMLblob::encodeLength() {
		std::vector<char> encoded_value = BMLBitVector(length).to_charvector();

		return encoded_value;
	}

	std::vector<char> BMLblob::encode() {
		std::vector<char> encoded_vector;
		// encode tag
		std::vector<char> encoded_tag = encodeTag(id, type_id);

		encoded_vector.insert(encoded_vector.begin(), encoded_tag.begin(), encoded_tag.end());

		// encode value
		std::vector<char> encoded_length = encodeLength();
		encoded_vector.insert(encoded_vector.end(), encoded_length.begin(), encoded_length.end());

		return encoded_vector;
	}

	size_t BMLblob::save(std::ofstream& outfile)
	{
		std::vector<char> to_write = encode();
		std::copy(to_write.begin(), to_write.end(), std::ostream_iterator<char>(outfile));
		size_t bytes_written = to_write.size();
		outfile.write(value, length);
		bytes_written += length;

		return bytes_written;
	}

// object
	std::vector<char> BMLobject::encodeOpenTag()
	{
		return encodeTag(id, 1);
	}

	size_t BMLobject::writeOpenTag(std::ofstream& outfile)
	{
		size_t bytes_written = 0;
		std::vector<char> opentag = encodeOpenTag();
		std::copy(opentag.begin(), opentag.end(), std::ostream_iterator<char>(outfile));
		bytes_written += opentag.size();

		return bytes_written;
	}

	std::vector<char> BMLobject::encodeCloseTag()
	{
		return encodeTag(id, 0);
	}
	size_t BMLobject::writeCloseTag(std::ofstream& outfile)
	{
		size_t bytes_written = 0;
		std::vector<char> closetag = encodeCloseTag();
		std::copy(closetag.begin(), closetag.end(), std::ostream_iterator<char>(outfile));
		bytes_written += closetag.size();

		return bytes_written;
	}
}