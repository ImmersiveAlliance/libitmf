#ifndef ITMF_ENUMS_H_
#define ITMF_ENUMS_H_

namespace itmf {
	enum class ITMF_ENCODING_ORDER { STREAMS_AT_START = 1, STREAMS_AT_END = 2 };
	enum class ITMF_SIGNATURE { NONE = 0 };
	enum class ITMF_COMPRESSION { NONE = 0 };
	enum class ITMF_HEADER_FLAGS { STREAMS_AT_START = 1, STREAMS_AT_END = 2, INDEX = 4, DIRECTORY = 8, PROPERTIES = 16, SIGNED = 32 };
	enum class ITMF_STREAM_TYPES { FILE_DATA = 0 };
	enum class CHUNK_FLAGS { SEEKABLE = 1, UNCOMPRESSED = 2 };
	enum class FILE_FLAGS { FILEDELETED = 1 };
	enum class BML_TYPES { CLOSE = 0, OBJECT = 1, INT = 2, LONG = 3, SINGLE = 4, DOUBLE = 5, STRING = 6, BLOB = 7};
	enum class LOGICAL_UNIT_IDS {
		PROPERTIES = 12,
		DIRECTORY = 13,
		INDEX = 14,
		STREAM_HEADERS = 15,
		SIGNATURE = 16
	};
	enum class ITMF_HEADER_IDS {
		OX = 1,
		VERSION = 2,
		FLAGS = 3,
		KEYGEN_METHOD = 9,
		NROUNDS = 10,
		SALT = 11
	};
	enum class COMPRESSED_UNIT_IDS {
		CODEC = 1,
		FORMAT = 99, // placeholder id
		UNCOMPRESSED_NBYTES = 2,
		COMPRESSED_DATA = 3
	};
	enum class ENCRYPTED_UNIT_IDS {
		CIPHER = 1,
		SALT = 12,
		ENCRYPTED_DATA = 3,
		SIGNATURE = 13
	};
	enum class PROPERTIES_IDS {
		KEY = 11,
		VALUE = 12
	};
	enum class STREAM_HEADER_IDS {
		TYPE = 3,
		FLAGS = 4,
		CODEC = 5,
		FORMAT = 6,
		NCHUNKS = 7,
		NBYTES = 8,
		KEY = 11,
		VALUE = 12,
		CIPHER = 2,
		SALT = 13,
		SIGNATURE = 14
	};
	enum class INDEX_IDS {
		STREAM_INDEX = 3,
		POS_DELTA = 6,
		NBYTES = 10
	};
	enum class DIRECTORY_IDS {
		STREAM_INDEX = 3,
		CHUNK_INDEX = 4,
		OFFSET = 5,
		NBYTES = 6,
		NAME = 7,
		SHA256 = 8,
		FLAGS = 9,
		KEY = 11,
		VALUE = 12
	};
	enum class SIGNATURE_IDS {
		ALGORITHM = 1,
		CERTIFICATE = 2,
		SIGNATURE = 3
	};
	enum class CHUNK_IDS {
		STREAM_INDEX = 3,
		FLAGS = 4,
		UNCOMPRESSED_NBYTES = 6,
		DATA = 7
	};
}

#endif // ITMF_ENUMS_H_