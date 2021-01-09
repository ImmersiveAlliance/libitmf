#include "bmltypes.h"

namespace bmllib {
// int
	class BMLint {
	public:
		int id;
		int32_t value;

		BMLint() : id(0), value(0) { }

		BMLint(int i, int32_t v) : id(i), value(v) { }

		void read(std::ifstream* infile);
		char* encode();
		void write(std::ofstream* outfile);

		bool operator==(const BMLint& j) {
			if ((id == j.id) && (value == j.value))
				return true;

			return false;
		}
	};

// long
	class BMLlong {
	public:
		int id;
		int64_t value;

		BMLlong() : id(0), value(0) { }
		BMLlong(int i, int64_t v) : id(i), value(v) { }

		void read(std::ifstream* infile);
		char* encode();
		void write(std::ofstream* outfile);

		bool operator==(const BMLlong& j) {
			if ((id == j.id) && (value == j.value))
				return true;

			return false;
		}
	};

// single


// double


// string


// blob


// object

}