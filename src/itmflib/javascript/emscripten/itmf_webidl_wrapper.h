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

typedef itmflib::ITMF_ENCODING_ORDER ITMFEncodingOrder;
typedef itmflib::ITMF_SIGNATURE ITMFSignature;
typedef itmflib::ITMF_COMPRESSION ITMFCompression;

class ITMFByteBuffer {
public:
	ITMFByteBuffer();
	void SetValues(const char* bytes, int count);
	int8_t GetValue(int index) const;
	size_t Size() { return vector_.size(); }

private:
	std::vector<int8_t> vector_;
};

class ITMFConfiguration {
public:
	ITMFConfiguration(ITMFEncodingOrder encodingOrder,
		bool includeProperties,
		bool includeIndex,
		ITMFSignature signature,
		ITMFCompression compression);

	itmflib::ITMFCONFIGURATION getConfiguration() { return config_; }

private:
	itmflib::ITMFCONFIGURATION config_;
};

class ITMFDecoder {

public:
	//ITMFDecoder();

private:
	itmflib::ITMFFILE file_;
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

	void Write(char* location, char* filename);

	void WriteToBuffer(ITMFByteBuffer* buffer);

private:
	itmflib::ITMFFILE file_;
};

#endif // ITMF_WEBIDL_WRAPPER_H_