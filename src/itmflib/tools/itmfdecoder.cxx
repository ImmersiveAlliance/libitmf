#include "itmffile.h"

int main() {
	itmflib::ITMFFILE file = itmflib::ITMFFILE::ReadFile("C:\\Users\\austin\\cablelabs\\development\\test_data\\octanetest.itmf");
	file.extractAllFiles("C:\\Users\\austin\\cablelabs\\development\\test_data\\output_files");
}