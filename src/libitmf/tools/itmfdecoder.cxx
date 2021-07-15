#include "itmffile.h"

void PrintUsage() {
	std::cout << "A command line application to decode and extract all files in an ITMF Container" << std::endl;
	std::cout << "Usage: ITMFDecoder -i [input file] -o [extracted files destination directory]" << std::endl;
}

int main(int argc, char** argv) {
	std::string filelocation;
	std::string destination;

	if (argc <= 1) {
		PrintUsage();

		return 0;
	}
	
	for (int i = 0; i < argc; i++) {
		if (!strcmp("-h", argv[i])) {
			PrintUsage();

			return 0;
		}

		if (!strcmp("-i", argv[i])) {
			filelocation = argv[++i];
		}

		if (!strcmp("-o", argv[i])) {
			destination = argv[++i];
		}
	}
	
	itmf::ITMFFILE file = itmf::ITMFFILE::ReadFile(filelocation);
	file.extractAllFiles(destination);
}