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
	bool verbose = false;

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
			case 'v':
				verbose = true;
				break;
			default:
				std::cerr << "Unknown option -" << argv[i][1] << std::endl;
				return EXIT_FAILURE;
			}

		}
	}

	if (inFileName == "") {
		std::cerr << "No input file given" << std::endl;
		return EXIT_FAILURE;
	}

	Input input;
	if (!input.openFile(inFileName) || input.getOpMode() == UNKNOWN) {
		std::cerr << "Error opening file " << inFileName << std::endl;
		return EXIT_FAILURE;
	}

	if (verbose) {
		OpMode opmode = input.getOpMode();
		std::cout << (opmode == COMPRESS ? "Compressing" : "Decompressing")
			<< " file " << inFileName << std::endl;
		if (opmode == DECOMPRESS) {
			std::cout << "Original size: " << input.getOriginalSize() << std::endl;
			std::cout << "Data segment location: " << input.getDataSegmentLoc() << std::endl;
			std::cout << "Dictionary location: " << input.getDictionaryLoc() << std::endl;
		}
		std::cout << "Writing output to " << (outFileName == "" ? "stdout" : outFileName) << std::endl;
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

	input.operate();
	input.write(*output);

	return EXIT_SUCCESS;
}
