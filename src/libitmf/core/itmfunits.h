#ifndef ITMF_UNITS_H_
#define ITMF_UNITS_H_

#include "bmltypes.h"
#include "itmfenums.h"
#include "boost/optional.hpp"
#include "boost/variant.hpp"

namespace itmf {

#define CHECK_BOOST_OPTIONAL(x) (x != boost::none ? true : false)

#define MAX_CHUNK_SIZE 1048576

	class ITMF_HEADER;
	class PROPERTIES;
	class FILE_PROPERTIES;
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
		static ITMF_HEADER ReadITMFHeader(std::istream& infile);

		void addFlag(ITMF_HEADER_FLAGS flag) { flags += static_cast<int32_t>(flag); }
		bool hasFlag(ITMF_HEADER_FLAGS flag);

		size_t write(std::ostream& outfile);
		//size_t writeToBuffer(std::vector<char>* buffer);
	};

	class PROPERTIES : public BMLobject {
		std::vector<std::pair<BMLstring, boost::variant<BMLstring, BMLlong>>> properties;

	public:
		PROPERTIES(std::vector<std::pair<BMLstring, boost::variant<BMLstring, BMLlong>>> props) : BMLobject(static_cast<int>(LOGICAL_UNIT_IDS::PROPERTIES)), properties(props) { }
		PROPERTIES() : BMLobject(static_cast<int>(LOGICAL_UNIT_IDS::PROPERTIES)), properties() { }
		//void addProperty(std::pair<BMLstring, boost::variant<BMLstring, BMLlong>> property) { properties.push_back(property); }
		void addProperty(std::string key, std::string value) {
			std::pair<BMLstring, boost::variant<BMLstring, BMLlong>> prop(BMLstring(static_cast<int>(STREAM_HEADER_IDS::KEY), key), BMLstring(static_cast<int>(STREAM_HEADER_IDS::VALUE), value));
			properties.push_back(prop);
		}
		void addProperty(std::string key, int64_t value) {
			std::pair<BMLstring, boost::variant<BMLstring, BMLlong>> prop(BMLstring(static_cast<int>(STREAM_HEADER_IDS::KEY), key), BMLlong(static_cast<int>(STREAM_HEADER_IDS::VALUE), value));
			properties.push_back(prop);
		}
		void parseProperties(std::istream& infile);

		size_t write(std::ostream& outfile);
		//size_t writeToBuffer(std::vector<char>* buffer);
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

		static STREAMHEADERS ReadStreamHeaders(std::istream& infile);

		void setType(int32_t t) { type = BMLint(static_cast<int>(STREAM_HEADER_IDS::TYPE), t); }
		void setType(std::string t) { type = BMLstring(static_cast<int>(STREAM_HEADER_IDS::TYPE), t); }
		void setFlags(int32_t f) { flags = BMLint(static_cast<int>(STREAM_HEADER_IDS::FLAGS), f); }
		void setCodec(int32_t c) { codec = BMLint(static_cast<int>(STREAM_HEADER_IDS::CODEC), c); }
		void setCodec(std::string c) { codec = BMLstring(static_cast<int>(STREAM_HEADER_IDS::CODEC), c); }
		void setFormat(std::shared_ptr<char> f, uint64_t length) { format = BMLblob(static_cast<int>(STREAM_HEADER_IDS::FORMAT), length, f); }
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
		/*void addProperty(std::pair<BMLstring, boost::variant<BMLstring, BMLlong>> prop) {
			properties.push_back(prop);
		}*/
		void addProperty(std::string key, std::string value) {
			std::pair<BMLstring, boost::variant<BMLstring, BMLlong>> prop(BMLstring(static_cast<int>(STREAM_HEADER_IDS::KEY), key), BMLstring(static_cast<int>(STREAM_HEADER_IDS::VALUE), value));
			properties.push_back(prop);
		}
		void addProperty(std::string key, int64_t value) {
			std::pair<BMLstring, boost::variant<BMLstring, BMLlong>> prop(BMLstring(static_cast<int>(STREAM_HEADER_IDS::KEY), key), BMLlong(static_cast<int>(STREAM_HEADER_IDS::VALUE), value));
			properties.push_back(prop);
		}
		void setCipher(int32_t c) { cipher = BMLint(static_cast<int>(STREAM_HEADER_IDS::CIPHER), c); }
		void setCipher(std::string c) { cipher = BMLstring(static_cast<int>(STREAM_HEADER_IDS::CIPHER), c); }
		void setSalt(std::shared_ptr<char> s, uint64_t length) { salt = BMLblob(static_cast<int>(STREAM_HEADER_IDS::SALT), length, s); }
		void setSignature(std::shared_ptr<char> s, uint64_t length) { signature = BMLblob(static_cast<int>(STREAM_HEADER_IDS::SIGNATURE), length, s); }

		// TODO: gets
		boost::variant<BMLint, BMLstring> getType() const { return type; }

		size_t write(std::ostream& outfile);
		//size_t writeToBuffer(std::vector<char>* buffer);
	};

	class INDEX : public BMLobject {
		boost::optional<BMLint> stream_index;
		std::vector<std::pair<BMLlong, boost::optional<BMLlong>>> nbytes;

	public:
		INDEX() : BMLobject(static_cast<int>(LOGICAL_UNIT_IDS::INDEX)) { }
		INDEX(std::vector<std::pair<BMLlong, boost::optional<BMLlong>>> nb) : BMLobject(static_cast<int>(LOGICAL_UNIT_IDS::INDEX)), nbytes(nb) { }

		static INDEXES ReadIndexes(std::istream& infile);

		void setStreamIndex(int32_t si) { stream_index = BMLint(static_cast<int>(INDEX_IDS::STREAM_INDEX), si); }
		void addNumBytes(std::pair<BMLlong, boost::optional<BMLlong>> n) { nbytes.push_back(n); }
		// TODO: addNumBytes
		void setPosDeltaNumBytes(int64_t pos_delta, boost::optional<int64_t> num_bytes) {
			if (CHECK_BOOST_OPTIONAL(num_bytes)) {
				boost::optional<BMLlong> nb(BMLlong(static_cast<int>(INDEX_IDS::NBYTES), num_bytes.get()));
				nbytes.push_back(std::pair<BMLlong, boost::optional<BMLlong>>(BMLlong(static_cast<int>(INDEX_IDS::POS_DELTA), pos_delta), nb));
			}
			else {
				nbytes.push_back(std::pair<BMLlong, boost::optional<BMLlong>>(BMLlong(static_cast<int>(INDEX_IDS::POS_DELTA), pos_delta), boost::none));
			}
		}
		size_t write(std::ostream& outfile);
		//size_t writeToBuffer(std::vector<char>* buffer);
	};

	class FILE_PROPERTIES {
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
		FILE_PROPERTIES() : name(BMLstring(static_cast<int>(DIRECTORY_IDS::NAME), "file")) { }
		FILE_PROPERTIES(BMLstring n, std::vector<std::pair<BMLstring, boost::variant<BMLstring, BMLlong>>> props = {}) : name(n), properties(props) { }

		BMLstring getName() { return name; }
		int64_t getChunkIndex() { return chunk_index ? chunk_index->getValue() : default_chunk_index; }
		int64_t getOffset() { return offset ? offset->getValue() : default_offset; }
		int64_t getNumBytes() { return nbytes ? nbytes->getValue() : default_nbytes; }
		int64_t getFlags() { return flags ? flags->getValue() : default_flags; }

		void setChunkIndex(int64_t ci) { chunk_index = BMLlong(static_cast<int>(DIRECTORY_IDS::CHUNK_INDEX), ci); }
		void setChunkIndex(BMLlong ci) { chunk_index = ci; }
		void setOffset(int64_t off) { offset = BMLlong(static_cast<int>(DIRECTORY_IDS::OFFSET), off); }
		void setOffset(BMLlong off) { offset = off; }
		void setNumBytes(int64_t nb) { nbytes = BMLlong(static_cast<int>(DIRECTORY_IDS::NBYTES), nb); }
		void setNumBytes(BMLlong nb) { nbytes = nb; }
		void setName(std::string n) { name = BMLstring(static_cast<int>(DIRECTORY_IDS::NAME), n); }
		void setName(BMLstring n) { name = n; }
		void setSha256(std::shared_ptr<char> s, uint64_t length) { sha256 = BMLblob(static_cast<int>(DIRECTORY_IDS::SHA256), length, s); }
		void setSha256(BMLblob s) { sha256 = s; }
		void setFlags(int32_t f) { flags = BMLint(static_cast<int>(DIRECTORY_IDS::FLAGS), f); }
		void setFlags(BMLint f) { flags = f; }
		void addProperty(std::string key, std::string value) {
			std::pair<BMLstring, boost::variant<BMLstring, BMLlong>> prop(BMLstring(static_cast<int>(STREAM_HEADER_IDS::KEY), key), BMLstring(static_cast<int>(STREAM_HEADER_IDS::VALUE), value));
			properties.push_back(prop);
		}
		void addProperty(std::string key, int64_t value) {
			std::pair<BMLstring, boost::variant<BMLstring, BMLlong>> prop(BMLstring(static_cast<int>(STREAM_HEADER_IDS::KEY), key), BMLlong(static_cast<int>(STREAM_HEADER_IDS::VALUE), value));
			properties.push_back(prop);
		}
		void addProperty(std::pair<BMLstring, boost::variant<BMLstring, BMLlong>> props) {
			properties.push_back(props);
		}

		size_t write(std::ostream& outfile);
		//size_t writeToBuffer(std::vector<char>* buffer);
	};

	class DIRECTORY : public BMLobject {
		boost::optional<BMLint> stream_index;
		std::vector<FILE_PROPERTIES> file_properties;

		static const int32_t default_stream_index = 0;

	public:
		DIRECTORY() : BMLobject(static_cast<int>(LOGICAL_UNIT_IDS::DIRECTORY)) { }
		DIRECTORY(std::vector<FILE_PROPERTIES> fp) : BMLobject(static_cast<int>(LOGICAL_UNIT_IDS::DIRECTORY)), file_properties(fp) { }

		static DIRECTORIES ReadDirectories(std::istream& infile);

		void setStreamIndex(int32_t si) { stream_index = BMLint(static_cast<int>(DIRECTORY_IDS::STREAM_INDEX), si); }
		void addFileProperty(FILE_PROPERTIES props) { file_properties.push_back(props); }

		std::vector<FILE_PROPERTIES> getFileProperties() { return file_properties; }
		int getStreamIndex() { return stream_index ? stream_index->getValue() : default_stream_index; }

		size_t write(std::ostream& outfile);
		//size_t writeToBuffer(std::vector<char>* buffer);
	};

	class SIGNATURE : public BMLobject {
		boost::variant<BMLint, BMLstring> algorithm;
		boost::optional<BMLblob> certificate;
		BMLblob signature;

	public:
		SIGNATURE(boost::variant<BMLint, BMLstring> alg, BMLblob s) : BMLobject(static_cast<int>(LOGICAL_UNIT_IDS::SIGNATURE)), algorithm(alg), signature(s) { }
		SIGNATURE() : BMLobject(static_cast<int>(LOGICAL_UNIT_IDS::SIGNATURE)), algorithm(), signature() { }

		void parseSignature(std::istream& infile);
		//void setAlgorithm(boost::variant<BMLint, BMLstring> alg) { algorithm = alg; }
		void setAlgorithm(int32_t alg) { algorithm = BMLint(static_cast<int>(SIGNATURE_IDS::ALGORITHM), alg); }
		void setAlgorithm(std::string alg) { algorithm = BMLstring(static_cast<int>(SIGNATURE_IDS::ALGORITHM), alg); }
		void setCertificate(std::shared_ptr<char> c, uint64_t length) { certificate = BMLblob(static_cast<int>(SIGNATURE_IDS::CERTIFICATE), length, c); }
		void setSignature(std::shared_ptr<char> s, uint64_t length) { signature = BMLblob(static_cast<int>(SIGNATURE_IDS::SIGNATURE), length, s); }

		size_t write(std::ostream& outfile);
		//size_t writeToBuffer(std::vector<char>* buffer);
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

		static CHUNKS ReadChunks(std::istream& infile);

		int32_t getStreamIndex() { return stream_index ? stream_index->getValue() : default_stream_index; }
		int32_t getFlags() { return flags ? flags->getValue() : default_flags; }
		BMLblob getData() { return data; }
		
		void setStreamIndex(int32_t si) { stream_index = BMLint(static_cast<int>(CHUNK_IDS::STREAM_INDEX), si); }
		void setFlags(int32_t f) { flags = BMLint(static_cast<int>(CHUNK_IDS::FLAGS), f); }
		void setUncompressBytes(int64_t ub) { uncompressed_bytes = BMLlong(static_cast<int>(CHUNK_IDS::UNCOMPRESSED_NBYTES), ub); }
		void setData(std::shared_ptr<char> d, uint64_t length) { data = BMLblob(static_cast<int>(CHUNK_IDS::DATA), length, d); }

		size_t write(std::ostream& outfile);
		//size_t writeToBuffer(std::vector<char>* buffer);
	};

	class ITMF_FOOTER {
		static const uint32_t EXPECTED_MAGIC = 0x9f5a1104;

		uint32_t offset_to_stream_end;
		uint32_t magic = EXPECTED_MAGIC;

	public:
		static ITMF_FOOTER CreateFooter(uint32_t offset);

		void parseFooter(std::istream& infile);

		void setOffset(uint32_t offset) { offset_to_stream_end = offset; }

		void write(std::ostream& outfile);
		//void writeToBuffer(std::vector<char>* buffer);
	};

}

#endif // ITMF_UNITS_H_