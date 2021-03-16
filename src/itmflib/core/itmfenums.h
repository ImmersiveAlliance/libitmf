#ifndef ITMF_ENUMS_H_
#define ITMF_ENUMS_H_

namespace itmflib {
	enum class ITMF_ENCODING_ORDER { STREAMS_AT_START = 1, STREAMS_AT_END = 2 };
	enum class ITMF_SIGNATURE { NONE = 0 };
	enum class ITMF_COMPRESSION { NONE = 0 };
	enum class ITMF_HEADER_FLAGS { STREAMS_AT_START = 1, STREAMS_AT_END = 2, INDEX = 4, DIRECTORY = 8, PROPERTIES = 16, SIGNED = 32 };
	enum class ITMF_STREAM_TYPES { FILE_DATA = 0 };
	enum class CHUNK_FLAGS { SEEKABLE = 1, UNCOMPRESSED = 2 };
	enum class FILE_FLAGS { FILEDELETED = 1 };
}

#endif // ITMF_ENUMS_H_