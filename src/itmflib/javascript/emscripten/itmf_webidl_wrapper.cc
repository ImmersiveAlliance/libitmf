#include "itmf_webidl_wrapper.h"

ITMFStringArray::ITMFStringArray() {}

const char* ITMFStringArray::GetValue(int index) const {
	const char* value = vector_[index].c_str();
	return value;
}

void ITMFStringArray::AddValue(std::string str) {
	vector_.push_back(str);
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
	outfile.close();

	return false;

}

void ITMFEncoder::Write(char* filename)
{
	file_.write(std::string(filename));
}

ITMFDecoder::ITMFDecoder() : file_(itmflib::ITMFFILE::CreateStreamsAtStartFile()) {
}

void ITMFDecoder::ReadFile(const char* buffer, unsigned long long size) {
	// Write the file to the virtual disk system
	std::ofstream outitmffile;
	outitmffile.open("temp.itmf", std::ios::out | std::ios::binary);
	if (outitmffile.is_open()) {
		outitmffile.write(buffer, size);
	}
	outitmffile.close();
	file_ = itmflib::ITMFFILE::ReadFile("temp.itmf");
}

void ITMFDecoder::PrintFileList() {
	std::vector<std::string> filelist = file_.getFilelist();
	for (std::string filename : filelist) {
		std::cout << filename << std::endl;
	}
}

void ITMFDecoder::GetFileList(ITMFStringArray* strarray) {
	std::vector<std::string> filelist = file_.getFilelist();
	for (std::string filename : filelist) {
		strarray->AddValue(filename);
	}
}

void ITMFDecoder::ExtractFile(char* filename, char* destination)
{
	file_.extractFile(std::string(filename), std::string(destination));
}

void ITMFDecoder::ExtractAllFiles(char* destination)
{
	file_.extractAllFiles(std::string(destination));
}