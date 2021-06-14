#ifndef ITMF_UNITS_H_
#define ITMF_UNITS_H_

#include "bmltypes.h"
#include "itmfenums.h"
#include "boost/optional.hpp"
#include "boost/variant.hpp"

namespace itmflib {

#define CHECK_BOOST_OPTIONAL(x) (x != boost::none ? true : false)

#define MAX_CHUNK_SIZE 1048576

	class ITMF_HEADER;
	class PROPERTIES;
	class STREAM_PROPERTIES;
	class STREAM_HEADER;
	class DIRECTORY;
	class INDEX;
	class SIGNATURE;
	class CHUNK;
	class FOOTER;
	typedef std::vector<STREAM_HEADER> STREAMHEADERS;
	typedef std::vector<DIRECTORY> DIRECTORIES;
	typedef std::vector<INDEX> INDEXES;
	typedef std::vector<CHUNK> CHUNKS;

	class ITMF_HEADER {
		BMLstring ox;
		BMLint version;
		BMLint flags;
		boost::optional<boost::variant<BMLstring, BMLlong>> keygen_method;
		boost::optional<BMLint> nrounds;
		boost::optional<BMLblob> salt;

		ITMF_HEADER(BMLstring o, BMLint v, BMLint f) : ox(o), version(v), flags(f),
			keygen_method(boost::none), nrounds(boost::none), salt(boost::none) { }

	public:
		static const int ITMF_CONTAINER_VERSION = 1;
		static ITMF_HEADER CreateITMFHeader(int32_t flags);
		static ITMF_HEADER ReadITMFHeader(std::ifstream& infile);

		void addFlag(ITMF_HEADER_FLAGS flag) { flags += static_cast<int32_t>(flag); }
		bool hasFlag(ITMF_HEADER_FLAGS flag);

		size_t write(std::ofstream& outfile);

	};

	class PROPERTIES : public BMLobject {
		std::vector<std::pair<BMLstring, boost::variant<BMLstring, BMLlong>>> properties;

	public:
		PROPERTIES(std::vector<std::pair<BMLstring, boost::variant<BMLstring, BMLlong>>> props) : BMLobject(static_cast<int>(LOGICAL_UNIT_IDS::PROPERTIES)), properties(props) { }
		PROPERTIES() : BMLobject(static_cast<int>(LOGICAL_UNIT_IDS::PROPERTIES)), properties() { }
		void parseProperties(std::ifstream& infile);
		void addProperty(std::pair<BMLstring, boost::variant<BMLstring, BMLlong>> property) { properties.push_back(property); }

		size_t write(std::ofstream& outfile);
	};

	class STREAM_HEADER : public BMLobject {
		boost::variant<BMLint, BMLstring> type;
		boost::optional<BMLint> flags;
		boost::optional<boost::variant<BMLint, BMLstring>> codec;
		boost::optional<BMLblob> format;
		boost::optional<BMLlong> nchunks;
		boost::optional<BMLlong> nbytes;
		std::vector<std::pair<BMLstring, boost::variant<BMLstring, BMLlong>>> properties;
		boost::optional<boost::variant<BMLint, BMLstring>> cipher;
		boost::optional<BMLblob> salt;
		boost::optional<BMLblob> signature;

		STREAM_HEADER() : BMLobject(static_cast<int>(LOGICAL_UNIT_IDS::STREAM_HEADERS)) { }

	public:
		STREAM_HEADER(int32_t t, std::vector<std::pair<BMLstring, boost::variant<BMLstring, BMLlong>>> props = {}) : BMLobject(static_cast<int>(LOGICAL_UNIT_IDS::STREAM_HEADERS)), type(BMLint(static_cast<int>(STREAM_HEADER_IDS::TYPE), t)), properties(props) { }
		STREAM_HEADER(std::string t, std::vector<std::pair<BMLstring, boost::variant<BMLstring, BMLlong>>> props = {}) : BMLobject(static_cast<int>(LOGICAL_UNIT_IDS::STREAM_HEADERS)), type(BMLstring(static_cast<int>(STREAM_HEADER_IDS::TYPE), t)), properties(props) { }

		static STREAMHEADERS ReadStreamHeaders(std::ifstream& infile);

		void setType(boost::variant<BMLint, BMLstring> t) { type = t; }
		void setFlags(BMLint f) { flags = f; }
		void setCodec(boost::variant<BMLint, BMLstring> c) { codec = c; }
		void setFormat(BMLblob f) { format = f; }
		void setNumChunks(int64_t n) { nchunks = BMLlong(static_cast<int>(STREAM_HEADER_IDS::NCHUNKS), n); }
		void addNumChunks(int64_t n) {
			if (nchunks != boost::none) {
				nchunks.get() += n;
			}
		}
		void setNumBytes(int64_t b) { nbytes = BMLlong(static_cast<int>(STREAM_HEADER_IDS::NBYTES), b); }
		void addNumBytes(int64_t b) {
			if (nbytes != boost::none) {
				nbytes.get() += b;
			}
		}
		void addProperty(std::pair<BMLstring, boost::variant<BMLstring, BMLlong>> prop) {
			properties.push_back(prop);
		}
		void setCipher(boost::variant<BMLint, BMLstring> c) { cipher = c; }
		void setSalt(BMLblob s) { salt = s; }
		void setSignature(BMLblob s) { signature = s; }

		boost::variant<BMLint, BMLstring> getType() const { return type; }

		size_t write(std::ofstream& outfile);
	};

	class INDEX : public BMLobject {
		boost::optional<BMLint> stream_index;
		std::vector<std::pair<BMLlong, boost::optional<BMLlong>>> nbytes;

	public:
		INDEX() : BMLobject(static_cast<int>(LOGICAL_UNIT_IDS::INDEX)) { }
		INDEX(std::vector<std::pair<BMLlong, boost::optional<BMLlong>>> nb) : BMLobject(static_cast<int>(LOGICAL_UNIT_IDS::INDEX)), nbytes(nb) { }

		static INDEXES ReadIndexes(std::ifstream& infile);

		void setStreamIndex(BMLint si) { stream_index = si; }
		void addNumBytes(std::pair<BMLlong, boost::optional<BMLlong>> n) { nbytes.push_back(n); }

		size_t write(std::ofstream& outfile);
	};

	class STREAM_PROPERTIES {
		boost::optional<BMLlong> chunk_index;
		boost::optional<BMLlong> offset;
		boost::optional<BMLlong> nbytes;
		BMLstring name;
		boost::optional<BMLblob> sha256;
		boost::optional<BMLint> flags;
		std::vector<std::pair<BMLstring, boost::variant<BMLstring, BMLlong>>> properties;

		static const int64_t default_chunk_index = 0;
		static const int64_t default_offset = 0;
		static const int64_t default_nbytes = 0;
		static const int32_t default_flags = 0;

	public:
		STREAM_PROPERTIES() : name(BMLstring(static_cast<int>(DIRECTORY_IDS::NAME), "file")) { }
		STREAM_PROPERTIES(BMLstring n, std::vector<std::pair<BMLstring, boost::variant<BMLstring, BMLlong>>> props = {}) : name(n), properties(props) { }

		BMLstring getName() { return name; }
		int64_t getChunkIndex() { return chunk_index ? chunk_index->getValue() : default_chunk_index; }
		int64_t getOffset() { return offset ? offset->getValue() : default_offset; }
		int64_t getNumBytes() { return nbytes ? nbytes->getValue() : default_nbytes; }
		int64_t getFlags() { return flags ? flags->getValue() : default_flags; }

		void setChunkIndex(int64_t ci) { chunk_index = BMLlong(static_cast<int>(DIRECTORY_IDS::CHUNK_INDEX), ci); }
		void setChunkIndex(BMLlong ci) { chunk_index = ci; }
		void setOffset(BMLlong off) { offset = off; }
		void setNumBytes(int64_t nb) { nbytes = BMLlong(static_cast<int>(DIRECTORY_IDS::NBYTES), nb); }
		void setNumBytes(BMLlong nb) { nbytes = nb; }
		void setName(std::string n) { name = BMLstring(static_cast<int>(DIRECTORY_IDS::NAME), n); }
		void setName(BMLstring n) { name = n; }
		void setSha256(BMLblob s) { sha256 = s; }
		void setFlags(BMLint f) { flags = f; }
		void addProperty(std::pair<BMLstring, boost::variant<BMLstring, BMLlong>> props) {
			properties.push_back(props);
		}

		size_t write(std::ofstream& outfile);
	};

	class DIRECTORY : public BMLobject {
		boost::optional<BMLint> stream_index;
		std::vector<STREAM_PROPERTIES> stream_properties;

		static const int32_t default_stream_index = 0;

	public:
		DIRECTORY() : BMLobject(static_cast<int>(LOGICAL_UNIT_IDS::DIRECTORY)) { }
		DIRECTORY(std::vector<STREAM_PROPERTIES> sp) : BMLobject(static_cast<int>(LOGICAL_UNIT_IDS::DIRECTORY)), stream_properties(sp) { }

		static DIRECTORIES ReadDirectories(std::ifstream& infile);

		void setStreamIndex(BMLint si) { stream_index = si; }
		void addStreamProperty(STREAM_PROPERTIES props) { stream_properties.push_back(props); }

		std::vector<STREAM_PROPERTIES> getStreamProperties() { return stream_properties; }
		int getStreamIndex() { return stream_index ? stream_index->getValue() : default_stream_index; }

		size_t write(std::ofstream& outfile);
	};

	class SIGNATURE : public BMLobject {
		boost::variant<BMLint, BMLstring> algorithm;
		boost::optional<BMLblob> certificate;
		BMLblob signature;

	public:
		SIGNATURE(boost::variant<BMLint, BMLstring> alg, BMLblob s) : BMLobject(static_cast<int>(LOGICAL_UNIT_IDS::SIGNATURE)), algorithm(alg), signature(s) { }
		SIGNATURE() : BMLobject(static_cast<int>(LOGICAL_UNIT_IDS::SIGNATURE)), algorithm(), signature() { }

		void parseSignature(std::ifstream& infile);
		void setAlgorithm(boost::variant<BMLint, BMLstring> alg) { algorithm = alg; }
		void setCertificate(BMLblob c) { certificate = c; }
		void setSignature(BMLblob s) { signature = s; }

		size_t write(std::ofstream& outfile);
	};

	class CHUNK {
		boost::optional<BMLint> stream_index;
		boost::optional<BMLint> flags;
		boost::optional<BMLlong> uncompressed_bytes;
		BMLblob data;

		static const int32_t default_stream_index = 0;
		static const int32_t default_flags = 0;

	public:
		CHUNK(BMLblob d) : data(d) { }
		CHUNK(BMLblob d, boost::optional<BMLint> si, boost::optional<BMLint> f, boost::optional<BMLlong> ub) : data(d), stream_index(si), flags(f), uncompressed_bytes(ub) { }

		static CHUNKS ReadChunks(std::ifstream& infile);

		int32_t getStreamIndex() { return stream_index ? stream_index->getValue() : default_stream_index; }
		int32_t getFlags() { return flags ? flags->getValue() : default_flags; }
		BMLblob getData() { return data; }
		
		void setStreamIndex(BMLint si) { stream_index = si; }
		void setFlags(BMLint f) { flags = f; }
		void setUncompressBytes(BMLlong ub) { uncompressed_bytes = ub; }
		void setData(BMLblob d) { data = d; }

		size_t write(std::ofstream& outfile);
	};

	class ITMF_FOOTER {
		static const uint32_t EXPECTED_MAGIC = 0x9f5a1104;

		uint32_t offset_to_stream_end;
		uint32_t magic = EXPECTED_MAGIC;

	public:
		static ITMF_FOOTER CreateFooter(uint32_t offset);

		void parseFooter(std::ifstream& infile);

		void setOffset(uint32_t offset) { offset_to_stream_end = offset; }

		void write(std::ofstream& outfile);
	};

}

#endif // ITMF_UNITS_H_