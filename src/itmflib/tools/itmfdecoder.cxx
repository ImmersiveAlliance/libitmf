#include "itmffile.h"

int main(int argc, char** argv) {
	
	std::string filelocation = argv[1];
	std::string destination = argv[2];
	
	itmflib::ITMFFILE file = itmflib::ITMFFILE::ReadFile(filelocation);
	file.extractAllFiles(destination);
}