#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <chrono>
#include "input.hpp"
#include "output.hpp"
#include <thread>

void printHelp() {
	std::cout << "tiralabra-compression" << std::endl
		<< "Usage: `tl-compression [options] <input file> [output file]\n" << std::endl
		<< "If output file is not specified, output will be printed to stdout" << std::endl
		<< "Options:" << std::endl
		<< "    -h: Print this help message" << std::endl
		<< "    -v: Verbose output" << std::endl
		<< "    -b: Benchmark mode" << std::endl
		<< "    -n: Null output (disregard output, useful for benchmark)" << std::endl;
}

int main(int argc, char** argv) {
	std::string inFileName = "";
	std::string outFileName = ""; // If unset, write output to stdout
	bool benchmarkAlgorithm = false;
	bool benchmarkIo = false;
	bool verbose = false;
	bool nullOutput = false; // If true, throw away the output

	std::chrono::time_point<std::chrono::system_clock> timestamp;

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
		} else {
			// Iterate through all short opts in a single argument
			// eg. -vb -> use options v and b
			int j = 1;
			while ((argv[i][j] != '\0')) {
				switch (argv[i][j]) {
				case 'h':
					printHelp();
					return EXIT_SUCCESS;
				case 'b':
					benchmarkAlgorithm = true;
					break;
				case 'v':
					verbose = true;
					break;
				case 'n':
					nullOutput = true;
					break;
				default:
					std::cerr << "Unknown option -" << argv[i][j] << std::endl;
					return EXIT_FAILURE;
				}
				++j;
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
		if (nullOutput)
			std::cout << "Discarding output" << std::endl;
		else if (outFileName != "")
			std::cout << "" << std::endl;
	}

	std::unique_ptr<Output> output;

	if (nullOutput) {
		output = std::unique_ptr<Output>(new NullOutput());
	} else if (outFileName == "") {
		output = std::unique_ptr<Output>(new StreamOutput());
	} else {
		output = std::unique_ptr<Output>(new FileOutput());
		if (!(*output).openFile(outFileName)) {
			std::cerr << "Cannot write to file " << outFileName << std::endl;
			return EXIT_FAILURE;
		}
	}

	if (benchmarkAlgorithm) {
		timestamp = std::chrono::system_clock::now();
	}
	input.operate(*output);
	if (benchmarkAlgorithm) {
		std::chrono::duration<unsigned long, std::nano> elapsed(std::chrono::system_clock::now() - timestamp);
		std::cout << "Time elapsed: " << elapsed.count() << " ns" << std::endl;
	}

	return EXIT_SUCCESS;
}
