#ifndef ITMF_WEBIDL_WRAPPER_H_
#define ITMF_WEBIDL_WRAPPER_H_


// TODO - change this to non relative path w CMake (eventually)
#include "../../core/itmffile.h"
#include "../../core/itmfunits.h"
#include <vector>

/**
To provide an API to js using WebIDL, we need a wrapper class to handle
types that cannot be handled and expose functions we want. 
We ideally want ITMF encoder and decoder classes to wrap an interface
to the ITMFILE.
This will also need to be expanded for the scene graph in future versions.
*/

typedef itmf::ITMF_ENCODING_ORDER ITMFEncodingOrder;
typedef itmf::ITMF_SIGNATURE ITMFSignature;
typedef itmf::ITMF_COMPRESSION ITMFCompression;

class ITMFStringArray {
public:
	ITMFStringArray();
	void AddValue(std::string str);
	const char* GetValue(int index) const;
	size_t Size() { return vector_.size(); }

private:
	std::vector<std::string> vector_;
};

class ITMFConfiguration {
public:
	ITMFConfiguration(ITMFEncodingOrder encodingOrder,
		bool includeProperties,
		bool includeIndex,
		ITMFSignature signature,
		ITMFCompression compression);

	itmf::ITMFCONFIGURATION getConfiguration() { return config_; }

private:
	itmf::ITMFCONFIGURATION config_;
};

class ITMFDecoder {

public:
	ITMFDecoder();

	void ReadFile(const char* buffer, unsigned long long size);
	void PrintFileList();
	void GetFileList(ITMFStringArray* strarray);
	void ExtractFile(char* filename, char* destination);
	void ExtractAllFiles(char* destination);

private:
	itmf::ITMFFILE file_;
};

class ITMFEncoder {

public:
	ITMFEncoder();

	void InitStreamsAtStart();
	void InitStreamsAtEnd();
	void InitCustom(ITMFConfiguration* configuration); 

	void AddStringProperty(char* key, char* value);
	void AddLongProperty(char* key, long value);

	//void AddFile(char* filepath);
	bool AddFile(char* filename, const char* buffer, unsigned long long size);

	void Write(char* filename);

private:
	itmf::ITMFFILE file_;
};

#endif // ITMF_WEBIDL_WRAPPER_H_