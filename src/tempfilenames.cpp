#include "tempfilenames.hpp"
#include <cstdio>
#include <random>

static std::default_random_engine rng;

std::string getTempFileName() {
#ifdef __unix__
	std::string tempNamePrefix = "/tmp/tiracomp-temp-";
#else
	// If not running on Unix, create temp files in current directory
	std::string tempNamePrefix = "tiracomp-temp-";
#endif
	std::string tempExtension = ".bin";
	std::string tempFileName = "";
	FILE* file = nullptr;
	do {
		if (file)
			fclose(file);
		tempFileName = tempNamePrefix;
		tempFileName += std::to_string(rng());
		tempFileName += tempExtension;
		file = std::fopen(tempFileName.c_str(), "r");
	} while (file != nullptr);

	return tempFileName;
}
