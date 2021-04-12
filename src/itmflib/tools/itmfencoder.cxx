#include "itmffile.h"

int main() {
	std::cout << "test" << std::endl;
	itmflib::ITMFFILE file = itmflib::ITMFFILE::CreateStreamsAtStartFile();

	file.addFile("F:\\art\\3D Models\\bunny.obj");

	file.write("F:\\Work\\OTOY\\Sample ITMF Files", "bunnycmake.itmf");

	itmflib::ITMFCONFIGURATION config(itmflib::ITMF_ENCODING_ORDER::STREAMS_AT_START, true, true,
		itmflib::ITMF_SIGNATURE::NONE, itmflib::ITMF_COMPRESSION::NONE);
	itmflib::ITMFFILE file2 = itmflib::ITMFFILE::CreateFileFromConfig(config);
	file2.addFile("F:\\art\\3D Models\\bunny.obj");
	file2.addFile("F:\\Work\\OTOY\\Sample ITMF Files\\project.ocs");
	file2.addProperty("octane_version", "4050000");
	file2.write("F:\\Work\\OTOY\\Sample ITMF Files", "octanetest.itmf");
}