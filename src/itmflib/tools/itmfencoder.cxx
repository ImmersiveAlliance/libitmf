#include "itmffile.h"

// itmfencoder -i <input files> -o <output file>

/*
-h
	help
-i
	input files
-o
	output file name
-eo
	encoding order
	start - STREAMS_AT_START
	end - STREAMS_AT_END
-p
	key then value
-index
	include index
later: compression/encryption
*/

void PrintUsage() {
	std::cout << "Usage: ITMFEncoder -i [input files] -o [output file] [options]" << std::endl;
	std::cout << "\n";
	std::cout << "Options:" << std::endl;
	std::cout << "-eo               Encoding Order" << std::endl;
	std::cout << "     start        Streams at start\n";
	std::cout << "     end          Streams at end\n";
	std::cout << "-p [key] [value]  Add a key value property\n";
	std::cout << "-index            Include an index to the file\n";
}

int main(int argc, char **argv) {
	std::vector<std::string> filenames;
	std::string outputfile;
	std::vector<std::pair<std::string, std::string>> properties;
	bool include_index = false;
	bool include_properties = false;
	itmflib::ITMF_ENCODING_ORDER encoding_order = itmflib::ITMF_ENCODING_ORDER::STREAMS_AT_START;

	for (int i = 0; i < argc; i++) {
		std::cout << argv[i] << std::endl;
		if (!strcmp("-h", argv[i])) {
			PrintUsage();

			return 0;
		}

		if (!strcmp("-i", argv[i])) {
			i++;
			do {
				std::cout << "Adding: " << argv[i] << std::endl;
				filenames.push_back(argv[i++]);
			} while(strcmp("-o", argv[i]));
		}

		if (!strcmp("-o", argv[i])) {
			std::cout << "here?" << std::endl;
			std::cout << "output filename: " << argv[i + 1] << std::endl;
			outputfile = argv[++i];
		}

		if (!strcmp("-eo", argv[i])) {
			if (!strcmp("start", argv[i + 1])) {
				encoding_order = itmflib::ITMF_ENCODING_ORDER::STREAMS_AT_START;
			}
			else if (!strcmp("end", argv[i + 1])) {
				encoding_order = itmflib::ITMF_ENCODING_ORDER::STREAMS_AT_END;
			}
			else {
				std::cout << "Not a valid encoding order" << std::endl;

				return -1;
			}
			i++;
		}

		if (!strcmp("-p", argv[i])) {
			if (!include_properties)
				include_properties = true;

			std::string key = std::string(argv[i + 1]);
			std::string value = std::string(argv[i + 2]);
			std::pair<std::string, std::string> prop(key, value);
			properties.push_back(prop);
		}
		
		if (!strcmp("-index", argv[i])) {
			include_index = true;
		}
	}

	itmflib::ITMFCONFIGURATION config(encoding_order, include_properties, include_index, itmflib::ITMF_SIGNATURE::NONE, itmflib::ITMF_COMPRESSION::NONE);
	itmflib::ITMFFILE file = itmflib::ITMFFILE::CreateFileFromConfig(config);
	for (auto it = properties.begin(); it != properties.end(); it++) {
		file.addProperty(it->first, it->second);
	}
	file.addFiles(filenames);
	file.write(outputfile);
}