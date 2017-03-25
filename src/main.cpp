#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "input.hpp"
#include "output.hpp"

int main(int argc, char** argv) {
	std::string inFileName = "";
	std::string outFileName = ""; // If unset, write output to stdout
	bool benchmark = false;

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
		} else if (argv[i][1] != '\0') {
			switch (argv[i][1]) {
				case 'b':
					benchmark = true;
					break;
				default:
					std::cerr << "Unknown option -" << argv[i][1] << std::endl;
					return EXIT_FAILURE;
			}

		}
	}

	if (inFileName == "") {
		std::cerr << "No input file specified" << std::endl;
		return EXIT_FAILURE;
	}

	Input input;
	if (!input.openFile(inFileName)) {
		std::cerr << "Error opening file " << inFileName << std::endl;
		return EXIT_FAILURE;
	}

	std::unique_ptr<Output> output;

	if (outFileName == "") {
		output = std::unique_ptr<Output>(new StreamOutput());
	} else {
		output = std::unique_ptr<Output>(new FileOutput());
		if (!(*output).openFile(outFileName)) {
			std::cerr << "Cannot write to file " << outFileName << std::endl;
			return EXIT_FAILURE;
		}
	}

	input.compress();
	input.write(*output);

	return EXIT_SUCCESS;
}
