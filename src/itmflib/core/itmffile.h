#ifndef ITMF_FILE_H_
#define ITMF_FILE_H

#include <itmfunits.h>
#include <bmltypes.h>

/*
#if defined(_WIN32)
#if defined(ITMF_DLLEXPORT)
#define ITMFAPI __declspec(dllexport)
#else
#define ITMFAPI __declspec(dllimport)
#endif
#endif
*/
namespace itmflib {

	typedef std::vector<STREAM_HEADER> STREAMHEADERS;
	typedef std::vector<DIRECTORY> DIRECTORIES;
	typedef std::vector<INDEX> INDEXES;
	typedef std::vector<CHUNK> CHUNKS;

	class ITMFCONFIGURATION {
		ITMF_ENCODING_ORDER encoding_order;
		bool properties_included;
		bool index_included;
		ITMF_SIGNATURE signature;
		ITMF_COMPRESSION compression;
	public:
		ITMFCONFIGURATION(ITMF_ENCODING_ORDER e, bool p, bool i, ITMF_SIGNATURE s, ITMF_COMPRESSION c) : encoding_order(e), properties_included(p), index_included(i), signature(s), compression(c) { }

		ITMF_ENCODING_ORDER getEncodingOrder() const { return encoding_order; }

		bool isPropertiesIncluded() const { return properties_included; }
		bool isIndexIncluded() const { return index_included; }

		void setPropertiesIncluded(bool include) { properties_included = include; }
		void setIndexIncluded(bool include) { index_included = include; }
	};

	class ITMFFILE {
	private:
		ITMF_HEADER header;
		boost::optional<PROPERTIES> properties;
		STREAMHEADERS streamheaders;
		boost::optional<INDEXES> index;
		DIRECTORIES directory;
		boost::optional<SIGNATURE> signature;
		ITMF_FOOTER footer;
		CHUNKS stream; // files added with a buffer will be added here

		std::vector<std::string> filelist;
		ITMFCONFIGURATION config;

		STREAM_HEADER* getStreamHeader(ITMF_STREAM_TYPES stream_type);
		void writeFiles(std::ofstream& outfile);
		void writeStreamsAtStart(std::ofstream& outfile);
		void writeStreamsAtEnd(std::ofstream& outfile);
		
		ITMFFILE(ITMF_HEADER h, ITMF_FOOTER f, ITMFCONFIGURATION conf) : header(h), footer(f), config(conf) { }
	public:
		static ITMFFILE CreateStreamsAtStartFile();
		static ITMFFILE CreateStreamsAtEndFile();
		static ITMFFILE CreateFileFromConfig(ITMFCONFIGURATION configuration);
		
		void addProperty(std::string key, std::string value);
		void addProperty(std::string key, int64_t value);
		void addFile(std::string filepath);
		void addFile(std::string filename, char* buffer);
		void readFile(std::string filename, char* buffer);

		std::vector<std::string> getFilelist() const { return filelist; }

		void write(std::string location, std::string filename); // write file to disk
	};

}

#endif // ITMF_FILE_H_