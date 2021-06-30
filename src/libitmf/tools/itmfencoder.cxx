#include "itmffile.h"

void PrintUsage() {
	std::cout << "A command line application to encode files into an ITMF Container" << std::endl;
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
	itmf::ITMF_ENCODING_ORDER encoding_order = itmf::ITMF_ENCODING_ORDER::STREAMS_AT_START;

	for (int i = 0; i < argc; i++) {
		if (!strcmp("-h", argv[i])) {
			PrintUsage();

			return 0;
		}

		if (!strcmp("-i", argv[i])) {
			i++;
			do {
				filenames.push_back(argv[i++]);
			} while(strcmp("-o", argv[i]));
		}

		if (!strcmp("-o", argv[i])) {
			outputfile = argv[++i];
		}

		if (!strcmp("-eo", argv[i])) {
			if (!strcmp("start", argv[i + 1])) {
				encoding_order = itmf::ITMF_ENCODING_ORDER::STREAMS_AT_START;
			}
			else if (!strcmp("end", argv[i + 1])) {
				encoding_order = itmf::ITMF_ENCODING_ORDER::STREAMS_AT_END;
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

	itmf::ITMFCONFIGURATION config(encoding_order, include_properties, include_index, itmf::ITMF_SIGNATURE::NONE, itmf::ITMF_COMPRESSION::NONE);
	itmf::ITMFFILE file = itmf::ITMFFILE::CreateFileFromConfig(config);
	for (auto it = properties.begin(); it != properties.end(); it++) {
		file.addProperty(it->first, it->second);
	}
	file.addFiles(filenames);
	file.write(outputfile);
}