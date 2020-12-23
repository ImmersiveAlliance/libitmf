#ifndef BMLLIB_CORE_BML_TYPES_H_
#define BMLLIB_CORE_BML_TYPES_H_

#include <vector>
#include <fstream>
#include "bmlbitutils.h"

namespace bmllib {
	
template <typename T>
class BMLtype {
public:
	BMLtype() { }
	BMLtype(int i, T v) : id(i), value(v) { }

	int id;
	T value;

	virtual void read(std::ifstream* infile) { }
	virtual char encode() { return ' '; }
	virtual void write(std::ofstream* outfile) { }
};

typedef BMLtype<int32_t> BMLint;
typedef BMLtype<int64_t> BMLlong;
typedef BMLtype<float> BMLsingle;
typedef BMLtype<double> BMLdouble;

class BMLstring : public BMLtype<std::string> {
public:
	int32_t length;
};

class BMLblob : public BMLtype<char*> {
public:
	int32_t length;
};

class BMLobject : public BMLtype<char*> {
public:
	char encodeOpenTag();
	char encodeCloseTag();
};

}

#endif // BMLLIB_CORE_BML_TYPES_H_