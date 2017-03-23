#include <iostream>
#include <fstream>
#include <string>

const int BUFFER_SIZE = 256;

int main(int argc, char** argv) {
	std::string inFileName = "";
	std::string outFileName = ""; // If unset, write output to stdout

	for (int i = 1; i < argc; ++i) {
		if (argv[i][0] != '-') {
			if (inFileName == "") {
				inFileName = argv[i];
			} else if (outFileName == "") {
				outFileName = argv[i];
			} else {
				std::cerr << "Too many arguments: " << argv[i] << std::endl;
				return EXIT_FAILURE;
			}
		}
	}

	if (inFileName == "") {
		std::cerr << "No input file specified" << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
