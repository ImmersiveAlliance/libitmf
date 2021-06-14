#ifndef ITMF_FILE_H_
#define ITMF_FILE_H_

#include "itmfunits.h"
#include "bmltypes.h"

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

	class ITMFCONFIGURATION {
		ITMF_ENCODING_ORDER encoding_order;
		bool properties_included;
		bool index_included;
		ITMF_SIGNATURE signature;
		ITMF_COMPRESSION compression;
	public:
		ITMFCONFIGURATION(
			ITMF_ENCODING_ORDER e = ITMF_ENCODING_ORDER::STREAMS_AT_START, 
			bool p = false, 
			bool i = false, 
			ITMF_SIGNATURE s = ITMF_SIGNATURE::NONE, 
			ITMF_COMPRESSION c = ITMF_COMPRESSION::NONE
		) : encoding_order(e), properties_included(p), index_included(i), signature(s), compression(c) { }

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
		//void writeStreamsAtStartToBuffer(std::vector<char>* buffer);
		void writeStreamsAtEnd(std::ofstream& outfile);
		void syncFilelist();
		
		ITMFFILE(ITMF_HEADER h, ITMF_FOOTER f, ITMFCONFIGURATION conf) : header(h), footer(f), config(conf) { }
		ITMFFILE() : header(ITMF_HEADER::CreateITMFHeader(0)), footer(), config() { }

	public:
		static ITMFFILE CreateStreamsAtStartFile();
		static ITMFFILE CreateStreamsAtEndFile();
		static ITMFFILE CreateFileFromConfig(ITMFCONFIGURATION configuration);
		static ITMFFILE ReadFile(std::string filepath);
		static ITMFFILE ReadFileFromMemory(void* mem);
		
		void addProperty(std::string key, std::string value);
		void addProperty(std::string key, int64_t value);
		void addFiles(std::vector<std::string> filepaths);
		void addFile(std::string filepath);
		void addFile(std::string filename, char* buffer);

		std::vector<std::string> getFilelist() const { return filelist; }
		void extractAllFiles(std::string destination_path);
		void extractFile(std::string filename, std::string destination_path);

		// Reading functions
		void read(std::string filepath);
		void readFileFromMemory();

		// Writing functions
		void write(std::string filename); // write file to disk

		// create file buffer?
		//void writeFileToBuffer(std::vector<char>* file_buffer);
	};

}

#endif // ITMF_FILE_H_