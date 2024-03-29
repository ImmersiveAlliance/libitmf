#include <bmltypes.h>

namespace itmf {

	// interface


	// global functions

	std::vector<char> encodeTag(int id, int type_id) {
		// TODO: Ensure that the id is not larger than 6 or negative
		BMLBitVector tag(id);
		tag = tag << 3;
		BMLBitVector typeBitVector(type_id);
		tag = tag | typeBitVector;
		return tag.to_charvector();
	}

	// TODO: Refactor id and type_id to be VUIE BMLBitVector and the type enum, respectively
	// This function will need to be rewritten
	void decodeTag(std::istream& infile, int& id, int& type_id) {
		BMLBitVector type_as_vector;
		BMLBitVector tag = BMLBitVector::readVUIE(infile);
		id = tag.to_int32() >> 3;
		BMLBitVector type_mask(0b111, Encoding::VUIE);
		type_as_vector = tag & type_mask;
		type_id = type_as_vector.to_int32();
	}

	void peekTag(std::istream& infile, int& id, int& type_id) { 
		std::streampos startpos = infile.tellg();
		decodeTag(infile, id, type_id); 
		infile.seekg(startpos);
	}

	bool ParseElement(std::istream& infile, int expected_id, BMLtype& output) {
		int current_id, current_type;
        peekTag(infile, current_id, current_type);
        if (current_id == expected_id && current_type == output.type_id) {
			// Consume the byte that we peeked. TODO: Verify TODO: MOVE THIS above parse I think
			char c;
			infile.get(c);

			output.id = current_id;
			output.parse(infile);

			return true;
		}
		else {
			return false;
		}
	}

// int
	std::vector<char> BMLint::encodeValue() {
		BMLBitVector b(value, Encoding::VSIE);

		return b.to_charvector();
	}

	void BMLint::parse(std::istream& infile) {
		BMLBitVector parsed_value = BMLBitVector::readVSIE(infile);
		this->value = parsed_value.to_int32();
	}

// long
	std::vector<char> BMLlong::encodeValue() {
		BMLBitVector b(value, Encoding::VSIE);

		return b.to_charvector();
	}

	void BMLlong::parse(std::istream& infile) {
		BMLBitVector parsed_value = BMLBitVector::readVSIE(infile);
		this->value = parsed_value.to_int64();
	}

// single
	std::vector<char> BMLsingle::encodeValue() {
		std::vector<char> encoded_value;
		uint32_t bits = 0;
		memcpy(&bits, &value, sizeof value);
		encoded_value.push_back((bits) & 0xFF);
		encoded_value.push_back((bits >> 8) & 0xFF);
		encoded_value.push_back((bits >> 16) & 0xFF);
		encoded_value.push_back((bits >> 24) & 0xFF);

		return encoded_value;
	}

	void BMLsingle::parse(std::istream& infile) {
		char bytes[4];
		infile.read(bytes, 4);
		this->value = *reinterpret_cast<float*>(bytes);
	}

// double
	std::vector<char> BMLdouble::encodeValue() {
		std::vector<char> encoded_value;
		uint64_t bits = 0;
		memcpy(&bits, &value, sizeof value);
		encoded_value.push_back((bits) & 0xFF);
		encoded_value.push_back((bits >> 8) & 0xFF);
		encoded_value.push_back((bits >> 16) & 0xFF);
		encoded_value.push_back((bits >> 24) & 0xFF);
		encoded_value.push_back((bits >> 32) & 0xFF);
		encoded_value.push_back((bits >> 40) & 0xFF);
		encoded_value.push_back((bits >> 48) & 0xFF);
		encoded_value.push_back((bits >> 56) & 0xFF);

		return encoded_value;
	}

	void BMLdouble::parse(std::istream& infile) {
		char bytes[8];
		infile.read(bytes, 8);
		this->value = *reinterpret_cast<double*>(bytes);
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

	void BMLstring::parse(std::istream& infile) {
		uint64_t str_length = BMLBitVector::readVUIE(infile).to_uint64();
		std::string parsed_string(str_length, ' ');
		infile.read(&parsed_string[0], str_length);
		this->value = parsed_string;
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

	void BMLblob::parse(std::istream& infile) {
		this->length = BMLBitVector::readVUIE(infile).to_uint64();
		this->value.reset(new char[this->length], std::default_delete<char[]>());
		infile.read(value.get(), this->length);
	}

	size_t BMLblob::save(std::ostream& outfile) {
		std::vector<char> to_write = encode();
		std::copy(to_write.begin(), to_write.end(), std::ostream_iterator<char>(outfile));
		size_t bytes_written = to_write.size();
		if (value != nullptr) {
			outfile.write(value.get(), length);
			bytes_written += length;
		}

		return bytes_written;
	}

// object
	std::vector<char> BMLobject::encodeOpenTag()
	{
		return encodeTag(id, 1);
	}

	size_t BMLobject::writeOpenTag(std::ostream& outfile)
	{
		size_t bytes_written = 0;
		std::vector<char> opentag = encodeOpenTag();
		std::copy(opentag.begin(), opentag.end(), std::ostream_iterator<char>(outfile));
		bytes_written += opentag.size();

		return bytes_written;
	}

	/*size_t BMLobject::writeOpenTagToBuffer(std::vector<char>* buffer) {
		size_t bytes_written = 0;
		std::vector<char> opentag = encodeOpenTag();
		buffer->insert(buffer->end(), opentag.begin(), opentag.end());
		bytes_written += opentag.size();

		return bytes_written;
	}*/

	std::vector<char> BMLobject::encodeCloseTag()
	{
		return encodeTag(id, 0);
	}

	size_t BMLobject::writeCloseTag(std::ostream& outfile)
	{
		size_t bytes_written = 0;
		std::vector<char> closetag = encodeCloseTag();
		std::copy(closetag.begin(), closetag.end(), std::ostream_iterator<char>(outfile));
		bytes_written += closetag.size();

		return bytes_written;
	}

	/*size_t BMLobject::writeCloseTagToBuffer(std::vector<char>* buffer) {
		size_t bytes_written = 0;
		std::vector<char> closetag = encodeCloseTag();
		buffer->insert(buffer->end(), closetag.begin(), closetag.end());
		bytes_written += closetag.size();

		return bytes_written;
	}*/
}