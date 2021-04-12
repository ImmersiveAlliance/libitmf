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

template <typename T>
class ITMFVector {
	T GetValue(int index) const;


private:
	std::vector<T> vector_;
};

class ITMFCONFIGURATION {

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
	//ITMFEncoder();

	void InitStreamsAtStart();
	void InitStreamsAtEnd();
	//void InitCustom(); // what do function params look like?

	void AddStringProperty(char* key, char* value);
	void AddLongProperty(char* key, long value);

	void AddFile(char* filepath);
	//void AddFile(char* filename, char* buffer);

	void Write(char* location, char* filename);

private:
	itmflib::ITMFFILE file_;
};

#endif // ITMF_WEBIDL_WRAPPER_H_