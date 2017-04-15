#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <chrono>
#include "input.hpp"
#include "output.hpp"
#include <thread>
#include <cmath>
#include "encoder.hpp"
#include "decoder.hpp"
#include "progressbar.hpp"

void printHelp() {
	std::cout << "tiralabra-compression" << std::endl
		<< "Usage: tiracomp [options] <input file> [output file]\n" << std::endl
		<< "If output file is not specified, output will be printed to stdout" << std::endl
		<< "Options:" << std::endl
		<< "    -h:             Print this help message" << std::endl
		<< "    -v:             Verbose output" << std::endl
		<< "    -b:             Benchmark mode" << std::endl
		<< "    -w <word size>: Define word size in bits when encoding (12 or 16)" << std::endl
		<< "    -i:             Only print file info" << std::endl
		<< "    -n:             Null output (disregard output, useful for benchmark)" << std::endl;
}

int main(int argc, char** argv) {
	// Initialise default values
	std::string inFileName = "";
	std::string outFileName = ""; // If unset, write output to stdout
	bool benchmark = false;
	bool verbose = false;
	bool nullOutput = false; // If true, throw away the output
	bool printInfo = false; // If true, print info and exit without operating
	int bitSize = 12;
	std::shared_ptr<ProgressBar> progress = nullptr;

	std::chrono::time_point<std::chrono::system_clock> timestampStart;
	std::chrono::time_point<std::chrono::system_clock> timestampEnd;

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
			int paramsToSkip = 0; // If an option takes a parameter, add to this
			int value_w; // Value for option -w
			while ((argv[i][j] != '\0')) {
				switch (argv[i][j]) {
				case 'h':
					printHelp();
					return EXIT_SUCCESS;
				case 'b':
					benchmark = true;
					break;
				case 'v':
					verbose = true;
					break;
				case 'n':
					nullOutput = true;
					break;
				case 'i':
					printInfo = true;
					break;
				case 'w':
					++paramsToSkip;
					if (i + paramsToSkip >= argc) {
						std::cerr << "No value given for word option -w" << std::endl;
						return EXIT_FAILURE;
					}
					value_w = std::atoi(argv[i + paramsToSkip]);
					if (value_w != MIN_BIT_SIZE && value_w != MAX_BIT_SIZE) {
						std::cerr << "Invalid value " << value_w
							<< " for option -w (must be either "
							<< MIN_BIT_SIZE << " or " << MAX_BIT_SIZE << ")" << std::endl;
						return EXIT_FAILURE;
					}
					bitSize = value_w;
					break;
				default:
					std::cerr << "Unknown option -" << argv[i][j] << std::endl;
					return EXIT_FAILURE;
				}
				++j;
			}
			i += paramsToSkip;
		}
	}

	if (inFileName == "") {
		std::cerr << "No input file given" << std::endl;
		return EXIT_FAILURE;
	}

	if (inFileName == outFileName) {
		std::cerr << "Input file and output file cannot be the same" << std::endl;
		return EXIT_FAILURE;
	}

	Input input;
	if (!input.openFile(inFileName) || input.getOpMode() == UNKNOWN) {
		std::cerr << "Error opening file " << inFileName << std::endl;
		return EXIT_FAILURE;
	} else if (input.getOpMode() == COMPRESS && input.getFileSize() == 0) {
		std::cerr << "File " << inFileName << " is empty" << std::endl;
		return EXIT_FAILURE;
	}

	if (verbose || printInfo) {
		OpMode opmode = input.getOpMode();
		if (!printInfo) {
			std::cout << (opmode == COMPRESS ? "Compressing" : "Decompressing")
				<< " file " << inFileName << std::endl;
			progress = std::shared_ptr<ProgressBar>(new ProgressBar(1));
		} else {
			std::cout << "File is "
				<< (opmode == COMPRESS ? "uncompressed" : "compressed") << std::endl;
		}
		if (opmode == DECOMPRESS) {
			std::cout << "Bit size: " << (int) input.getBitSize() << std::endl;
			std::cout << "Original size: " << input.getOriginalSize() << std::endl;
		}
		std::cout << "File size: " << input.getFileSize() << std::endl;
		if (opmode == DECOMPRESS && input.getOriginalSize() != 0) {
			float compressRatio = (float) input.getFileSize() / input.getOriginalSize();
			std::cout << "Compression ratio: "
				<< std::round(compressRatio * 1000) / 1000 << std::endl;
		}
		if (!printInfo) {
			std::cout << "Encoding with bit size: " << bitSize << std::endl;
			if (nullOutput)
				std::cout << "Discarding output" << std::endl;
			else if (outFileName != "")
				std::cout << "Writing output to " << outFileName << std::endl;
			else
				std::cout << "Writing output to stdout" << std::endl;
		}
	}

	if (printInfo)
		return EXIT_SUCCESS;

	std::shared_ptr<Output> output;

	if (nullOutput) {
		output = std::shared_ptr<Output>(new NullOutput());
	} else if (outFileName == "") {
		output = std::shared_ptr<Output>(new StreamOutput());
	} else {
		output = std::shared_ptr<Output>(new FileOutput());
		if (!(*output).openFile(outFileName)) {
			std::cerr << "Cannot write to file " << outFileName << std::endl;
			return EXIT_FAILURE;
		}
	}


	if (progress)
		progress->start();

	if (benchmark) {
		timestampStart = std::chrono::system_clock::now();
	}

	if (input.getOpMode() == COMPRESS) {
		try {
			encoder::encode(input, *output, bitSize, true, progress);
		} catch (std::exception e) {
			std::cerr << "Error encoding: " << e.what() << std::endl;
			return EXIT_FAILURE;
		}
	} else if (input.getOpMode() == DECOMPRESS) {
		try {
			decoder::decode(input, *output);
		} catch (std::exception e) {
			std::cerr << "Error decoding: " << e.what() << std::endl;
			return EXIT_FAILURE;
		}
	}

	if (benchmark)
		timestampEnd = std::chrono::system_clock::now();

	if (progress)
		progress->stop();

	if (benchmark)
		std::cout << "Time elapsed: "
			<< std::chrono::duration_cast<std::chrono::milliseconds>
			(timestampEnd - timestampStart).count() << " ms" << std::endl;

	return EXIT_SUCCESS;
}
