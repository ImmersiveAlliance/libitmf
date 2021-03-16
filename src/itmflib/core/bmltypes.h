#ifndef BML_TYPES_H_
#define BML_TYPES_H_

#include <defines.h>
#include <vector>
#include <fstream>
#include <boost/variant/static_visitor.hpp>
#include <bmlbitutils.h>

namespace itmflib {
	std::vector<char> encodeTag(int id, int type_id);
	
class BMLtype {
public:
	BMLtype() { }
	BMLtype(int i) : id(i) { }

	int id;
	int type_id;

	void load(std::ifstream& infile);
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

	virtual size_t save(std::ofstream& outfile) {
		std::vector<char> to_write = encode();
		std::copy(to_write.begin(), to_write.end(), std::ostream_iterator<char>(outfile));
	
		return to_write.size();
	}
};

class BMLint : public BMLtype {
	int32_t value;
public:
	BMLint(int i, int32_t v) : BMLtype(i), value(v) {
		type_id = 2;
	}

	int32_t getValue() const { return value; }

	BMLint& operator+=(const int32_t& rhs) {
		this->value += rhs;

		return *this;
	}

	std::vector<char> encodeValue();
};

class BMLlong : public BMLtype {
	int64_t value;
public:
	BMLlong(int i, int64_t v) : BMLtype(i), value(v) {
		type_id = 3;
	}

	int64_t getValue() const { return value; }
	
	BMLlong& operator+=(const int64_t& rhs) {
		this->value += rhs;

		return *this;
	}

	std::vector<char> encodeValue();
};

class BMLsingle : public BMLtype {
	float value;
public:
	BMLsingle(int i, float v) : BMLtype(i), value(v) {
		type_id = 4;
	}

	float getValue() const { return value; }

	std::vector<char> encodeValue();
};

class BMLdouble : public BMLtype {
	double value;
public:
	BMLdouble(int i, double v) : BMLtype(i), value(v) {
		type_id = 5;
	}
	
	double getValue() const { return value; }

	std::vector<char> encodeValue();
};

class BMLstring : public BMLtype {
private:
	std::string value;
public:
	BMLstring(int i, std::string v) : BMLtype(i), value(v) { 
		type_id = 6;
		length = v.size();
	}

	int32_t length;

	std::string getValue() const { return value; }

	// Overloads
	void load(std::ifstream& infile);
	std::vector<char> encode();
	std::vector<char> encodeLength();
	std::vector<char> encodeValue();
};

class BMLblob : public BMLtype {
	char* value;
public:
	BMLblob(int i, int32_t l, char* v) : BMLtype(i), value(v), length(l) {
		type_id = 7;
	}

	char* getValue() const { return value; }

	int32_t length;

	// Overloads
	void load(std::ifstream& infile);
	std::vector<char> encode();
	std::vector<char> encodeLength();
	std::vector<char> encodeValue() { return std::vector<char>({}); }
	size_t save(std::ofstream& outfile);
};

class BMLobject {
private:
	int id;
public:
	BMLobject(int i) : id(i) { }

	std::vector<char> encodeOpenTag();
	size_t writeOpenTag(std::ofstream& outfile);
	std::vector<char> encodeCloseTag();
	size_t writeCloseTag(std::ofstream& outfile);
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

class check_file_stream_header : public boost::static_visitor<bool> {
public:
	bool operator()(BMLint& i) const {
		if (i.getValue() == 0) {
			return true;
		}

		return false;
	}

	bool operator()(BMLstring& s) const {
		if (s.getValue() == "file") {
			return true;
		}

		return false;
	}
};

}

#endif // BML_TYPES_H_