#ifndef BMLLIB_CORE_BML_BIT_UTILS_H_
#define BMLLIB_CORE_BML_BIT_UTILS_H_

#include <vector>
#include <boost/dynamic_bitset/dynamic_bitset.hpp>

namespace bmllib {
	/* This will have things like bit manip for bml bit sets*/
	typedef bool BMLbit;

	class BMLbitset : public boost::dynamic_bitset<> {
		int32_t vsie_to_int32();  // int conversion
		int32_t vuie_to_int32();
		int64_t vsie_to_int64();  // long conversion
		int64_t vuie_to_int64();  
	};
}

#endif // BMLLIB_CORE_BML_BIT_UTILS_H_