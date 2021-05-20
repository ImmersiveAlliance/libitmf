#include "itmf_webidl_wrapper.h"

ITMFByteBuffer::ITMFByteBuffer() {}

int8_t ITMFByteBuffer::GetValue(int index) const {
	return vector_[index];
}

void ITMFByteBuffer::SetValues(const char* bytes, int count) {
	vector_.assign(bytes, bytes + count);
	return;
}

ITMFConfiguration::ITMFConfiguration(ITMFEncodingOrder encodingOrder, bool includeProperties, bool includeIndex, ITMFSignature signature, ITMFCompression compression) :
	config_(encodingOrder, includeProperties, includeIndex, signature, compression)
{ }

ITMFEncoder::ITMFEncoder() : file_(itmflib::ITMFFILE::CreateStreamsAtStartFile())
{ }

void ITMFEncoder::InitStreamsAtStart()
{
	file_ = itmflib::ITMFFILE::CreateStreamsAtStartFile();
}

void ITMFEncoder::InitStreamsAtEnd()
{
	file_ = itmflib::ITMFFILE::CreateStreamsAtEndFile();
}

void ITMFEncoder::InitCustom(ITMFConfiguration* configuration)
{
	itmflib::ITMFCONFIGURATION config = configuration->getConfiguration();
	file_ = itmflib::ITMFFILE::CreateFileFromConfig(config);
}

void ITMFEncoder::AddStringProperty(char* key, char* value)
{
	file_.addProperty(std::string(key), std::string(value));
}

void ITMFEncoder::AddLongProperty(char* key, long value)
{
	file_.addProperty(std::string(key), static_cast<int64_t>(value));
}

bool ITMFEncoder::AddFile(char* filename, const char* buffer, unsigned long long size)
{
	// Write file to virtual disk system to be added later?
	// Make the js application handle that?
	std::ofstream outfile;
	outfile.open(filename, std::ios::out | std::ios::binary);
	if (outfile.is_open()) {
		std::cout << std::strlen(buffer) << std::endl;
		outfile.write(buffer, size);
		file_.addFile(std::string(filename));
		outfile.close();

		return true;
	}

	return false;

}

void ITMFEncoder::Write(char* location, char* filename)
{
	file_.write(std::string(location), std::string(filename));
}