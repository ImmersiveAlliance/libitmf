#ifndef ITMF_UNITS_H_
#define ITMF_UNITS_H_

#include <bmltypes.h>
#include <itmfenums.h>
#include <boost/optional.hpp>
#include <boost/variant.hpp>

namespace itmflib {

#define CHECK_BOOST_OPTIONAL(x) (x != boost::none ? true : false)

#define MAX_CHUNK_SIZE 1048576

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
		static ITMF_HEADER CreateITMFHeader(int32_t flags);

		void addFlag(ITMF_HEADER_FLAGS flag) { flags += static_cast<int32_t>(flag); }

		size_t write(std::ofstream& outfile);
	};

	class PROPERTIES : public BMLobject {
		std::vector<std::pair<BMLstring, boost::variant<BMLstring, BMLlong>>> properties;

	public:
		PROPERTIES(std::vector<std::pair<BMLstring, boost::variant<BMLstring, BMLlong>>> props) : BMLobject(12), properties(props) { }
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

	public:
		STREAM_HEADER(int32_t t, std::vector<std::pair<BMLstring, boost::variant<BMLstring, BMLlong>>> props = {}) : BMLobject(15), type(BMLint(3, t)), properties(props) { }
		STREAM_HEADER(std::string t, std::vector<std::pair<BMLstring, boost::variant<BMLstring, BMLlong>>> props = {}) : BMLobject(15), type(BMLstring(3, t)), properties(props) { }

		void setType(boost::variant<BMLint, BMLstring> t) { type = t; }
		void setFlags(BMLint f) { flags = f; }
		void setCodec(boost::variant<BMLint, BMLstring> c) { codec = c; }
		void setFormat(BMLblob f) { format = f; }
		void setNumChunks(int64_t n) { nchunks = BMLlong(7, n); }
		void addNumChunks(int64_t n) {
			if (nchunks != boost::none) {
				nchunks.get() += n;
			}
		}
		void setNumBytes(int64_t b) { nbytes = BMLlong(8, b); }
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
		INDEX() : BMLobject(14) { }
		INDEX(std::vector<std::pair<BMLlong, boost::optional<BMLlong>>> nb) : BMLobject(14), nbytes(nb) { }

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

	public:
		STREAM_PROPERTIES() : name(BMLstring(3, "file")) { }
		STREAM_PROPERTIES(BMLstring n, std::vector<std::pair<BMLstring, boost::variant<BMLstring, BMLlong>>> props = {}) : name(n), properties(props) { }

		void setChunkIndex(int64_t ci) { chunk_index = BMLlong(4, ci); }
		void setOffset(BMLlong off) { offset = off; }
		void setNumBytes(int64_t nb) { nbytes = BMLlong(6, nb); }
		void setName(std::string n) { name = BMLstring(7, n); }
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

	public:
		DIRECTORY() : BMLobject(13) { }
		DIRECTORY(std::vector<STREAM_PROPERTIES> sp) : BMLobject(13), stream_properties(sp) { }

		void setStreamIndex(BMLint si) { stream_index = si; }
		void addStreamProperty(STREAM_PROPERTIES props) { stream_properties.push_back(props); }

		size_t write(std::ofstream& outfile);
	};

	class SIGNATURE : public BMLobject {
		boost::variant<BMLint, BMLstring> algorithm;
		boost::optional<BMLblob> certificate;
		BMLblob signature;

	public:
		SIGNATURE(boost::variant<BMLint, BMLstring> alg, BMLblob s) : BMLobject(16), algorithm(alg), signature(s) { }

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

	public:
		CHUNK(BMLblob d) : data(d) { }
		
		void setStreamIndex(BMLint si) { stream_index = si; }
		void setFlags(BMLint f) { flags = f; }
		void setUncompressBytes(BMLlong ub) { uncompressed_bytes = ub; }
		void setData(BMLblob d) { data = d; }

		size_t write(std::ofstream& outfile);
	};

	class ITMF_FOOTER {
		uint32_t offset_to_stream_end;
		uint32_t magic = 0x9f5a1104;

	public:
		static ITMF_FOOTER CreateFooter(uint32_t offset);

		void setOffset(uint32_t offset) { offset_to_stream_end = offset; }

		void write(std::ofstream& outfile);
	};

}

#endif // ITMF_UNITS_H_