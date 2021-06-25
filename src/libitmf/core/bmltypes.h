#ifndef BML_TYPES_H_
#define BML_TYPES_H_

#include <vector>
#include <fstream>
#include <cstring>
#include <memory>
#include "boost/variant/static_visitor.hpp"
#include "bmlbitutils.h"

namespace itmf {
	std::vector<char> encodeTag(int id, int type_id);
	void decodeTag(std::ifstream& infile, int& id, int& type_id);
	void peekTag(std::ifstream& infile, int& id, int& type_id);

	unsigned char countLeadingOnes(unsigned char byte);

	BMLBitVector readVUIE(std::ifstream& infile);
	BMLBitVector readVSIE(std::ifstream& infile);


class BMLtype {
public:
	BMLtype() : id(), type_id() { }
	BMLtype(int i, int type) : id(i), type_id(type) { }

	int id;
	int type_id;


	virtual std::vector<char> encode() {
		std::vector<char> encoded_vector;
		// encode tag
		std::vector<char> encoded_tag = encodeTag(id, type_id);

		encoded_vector.insert(encoded_vector.begin(), encoded_tag.begin(), encoded_tag.end());

		// encode value
		std::vector<char> encoded_value = encodeValue();
		encoded_vector.insert(encoded_vector.end(), encoded_value.begin(), encoded_value.end());

		return encoded_vector;
	}

	virtual std::vector<char> encodeValue() = 0;
	virtual void parse(std::ifstream& infile) = 0;

	virtual size_t save(std::ofstream& outfile) {
		std::vector<char> to_write = encode();
		std::copy(to_write.begin(), to_write.end(), std::ostream_iterator<char>(outfile));
	
		return to_write.size();
	}

	virtual size_t writeToBuffer(std::vector<char>* buffer) {
		std::vector<char> to_write = encode();
		buffer->insert(buffer->end(), to_write.begin(), to_write.end());

		return to_write.size();
	}
};

	// Returns true if the output BMLtype was filled, else returns false
	// Only consumes bytes if the tag from the input stream is what was expected
	bool ParseElement(std::ifstream& infile, int expected_id, BMLtype& output); 

class BMLint : public BMLtype {
	// TODO: Replace with BMLBitVector
	int32_t value;
public:
	BMLint(int i, int32_t v) : BMLtype(i, 2), value(v) { }
	BMLint() : BMLtype(0, 2), value() { }

	int32_t getValue() const { return value; }

	BMLint& operator+=(const int32_t& rhs) {
		this->value += rhs;

		return *this;
	}

	std::vector<char> encodeValue();
	void parse(std::ifstream& infile);
};

class BMLlong : public BMLtype {
	// TODO: Replace with BMLBitVector
	int64_t value;
public:
	BMLlong(int i, int64_t v) : BMLtype(i, 3), value(v) { }
	BMLlong() : BMLtype(0, 3), value() { }

	int64_t getValue() const { return value; }
	
	BMLlong& operator+=(const int64_t& rhs) {
		this->value += rhs;

		return *this;
	}

	std::vector<char> encodeValue();
	void parse(std::ifstream& infile);
};

class BMLsingle : public BMLtype {
	float value;
public:
	BMLsingle(int i, float v) : BMLtype(i, 4), value(v) { }
	BMLsingle() : BMLtype(0, 4), value() { }

	float getValue() const { return value; }

	std::vector<char> encodeValue();
	void parse(std::ifstream& infile);
};

class BMLdouble : public BMLtype {
	double value;
public:
	BMLdouble(int i, double v) : BMLtype(i, 5), value(v) {	}
	BMLdouble() : BMLtype(0, 5), value() { }
	
	double getValue() const { return value; }

	std::vector<char> encodeValue();
	void parse(std::ifstream& infile);
};

class BMLstring : public BMLtype {
private:
	std::string value;
public:
	BMLstring(int i, std::string v) : BMLtype(i, 6), value(v) {
		length = v.size();
	}

	BMLstring() : BMLtype(0, 6), value(""), length(0) { }

	//int32_t length; // TODO
	uint64_t length;

	std::string getValue() const { return value; }

	// Overloads
	//void load(std::ifstream& infile);
	std::vector<char> encode();
	std::vector<char> encodeLength();
	std::vector<char> encodeValue();
	void parse(std::ifstream& infile);
};

class BMLblob : public BMLtype {
	std::shared_ptr<char> value;
public:
	BMLblob() : length(0), value(), BMLtype(0, 7) { }
	BMLblob(int id, uint64_t l, std::shared_ptr<char> v) : length(l), value(v), BMLtype(id, 7) { }

	//char* getValue() const { return value; }
	std::shared_ptr<char> getValue() const { return value; }

	uint64_t length;

	// Overloads
	//void load(std::ifstream& infile);
	std::vector<char> encode();
	std::vector<char> encodeLength();
	std::vector<char> encodeValue() { return std::vector<char>({}); }
	void parse(std::ifstream& infile);
	size_t save(std::ofstream& outfile);
};

class BMLobject {
protected:
	int id;
public:
	BMLobject(int i) : id(i) { }

	std::vector<char> encodeOpenTag();
	size_t writeOpenTag(std::ofstream& outfile);
	//size_t writeOpenTagToBuffer(std::vector<char>* buffer);
	std::vector<char> encodeCloseTag();
	size_t writeCloseTag(std::ofstream& outfile);
	//size_t writeCloseTagToBuffer(std::vector<char>* buffer);
};

// Visitor class for boost::variant usage
class save_visitor : public boost::static_visitor<> {
	std::ofstream& save_file;
	size_t& bytes_written;
public:
	save_visitor(std::ofstream& outfile, size_t& bytes) : save_file(outfile), bytes_written(bytes) { }

	void operator()(BMLstring& s) const {
		bytes_written += s.save(save_file);
	}

	void operator()(BMLlong& l) const {
		bytes_written += l.save(save_file);
	}

	void operator()(BMLint& i) const {
		bytes_written += i.save(save_file);
	}

	void operator()(BMLblob& b) const {
		bytes_written += b.save(save_file);
	}
};

class buffer_save_visitor : public boost::static_visitor<> {
	std::vector<char>* buffer;
	size_t& bytes_written;
public:
	buffer_save_visitor(std::vector<char>* buf, size_t& bytes) : buffer(buf), bytes_written(bytes) { }

	void operator()(BMLstring& s) const {
		bytes_written += s.writeToBuffer(buffer);
	}

	void operator()(BMLlong& l) const {
		bytes_written += l.writeToBuffer(buffer);
	}

	void operator()(BMLint& i) const {
		bytes_written += i.writeToBuffer(buffer);
	}

	void operator()(BMLblob& b) const {
		bytes_written += b.writeToBuffer(buffer);
	}
};

class check_file_stream_header : public boost::static_visitor<> {
	bool& ret;
public:
	check_file_stream_header(bool& r) : ret(r) { }

	void operator()(BMLint& i) const {
		if (i.getValue() == 0) {
			ret = true;

			return;
		}

		ret = false;
	}

	void operator()(BMLstring& s) const {
		if (s.getValue() == "file") {
			ret = true;

			return;
		}

		ret = false;
	}
};

}

#endif // BML_TYPES_H_