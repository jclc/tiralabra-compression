#ifndef INPUT_HPP
#define INPUT_HPP

#include <string>
#include "output.hpp"
#include <stdio.h>

typedef enum OpMode {
	UNKNOWN,
	COMPRESS,
	DECOMPRESS
} OpMode;

class Input {
public:
	Input();
	~Input();

	/**
	 * @brief Open a file for compression. Operation mode will be determined based on the file.
	 * @param fileName Name of the file to be opened.
	 * @return Returns true if file was opened successfully.
	 */
	bool openFile(const std::string& fileName);

	/**
	 * @brief Compress or decompress the opened file, depending on determined operation mode.
	 */
	void operate(Output& out);

	/**
	 * @brief Get operation mode for opened file.
	 * @return UNKNOWN, COMPRESS or DECOMPRESS
	 */
	OpMode getOpMode() const {return opmode;}

	/**
	 * @brief If opened file is a compressed file, get the original size from header.
	 * @return Original size in bytes.
	 */
	unsigned long getOriginalSize() const {return originalSize;}

	/**
	 * @brief If opened file is a compressed file, get the location of the data segment.
	 * @return Location of data segment in bytes from the beginning.
	 */
	unsigned long getDataSegmentLoc() const {return dataSegmentLoc;}

	/**
	 * @brief If opened file is a compressed file, get the location of the dictionary.
	 * @return Location of dictionary in bytes from the beginning.
	 */
	unsigned long getDictionaryLoc() const {return dictionaryLoc;}

private:

	/**
	 * @brief Double the size of the file buffer
	 */
	void enlargeBuffer();

	FILE* filePointer;
	uint64_t fileSize;
	uint64_t outBufferSize;
	char* outBuffer;
	OpMode opmode;
	uint64_t originalSize;
	uint64_t dataSegmentLoc;
	uint64_t dictionaryLoc;
};

#endif /* INPUT_HPP */
