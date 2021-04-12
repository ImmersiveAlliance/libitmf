#include "itmf_webidl_wrapper.h"


void ITMFEncoder::InitStreamsAtStart()
{
	file_ = itmflib::ITMFFILE::CreateStreamsAtEndFile();
}

void ITMFEncoder::InitStreamsAtEnd()
{
	file_ = itmflib::ITMFFILE::CreateStreamsAtEndFile();
}

void ITMFEncoder::AddStringProperty(char* key, char* value)
{
	file_.addProperty(std::string(key), std::string(value));
}

void ITMFEncoder::AddLongProperty(char* key, long value)
{
	file_.addProperty(std::string(key), static_cast<int64_t>(value));
}

void ITMFEncoder::AddFile(char* filepath)
{
	file_.addFile(std::string(filepath));
}

void ITMFEncoder::Write(char* location, char* filename)
{
	file_.write(std::string(location), std::string(filename));
}
