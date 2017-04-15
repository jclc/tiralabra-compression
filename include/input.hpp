#ifndef INPUT_HPP
#define INPUT_HPP

#include "output.hpp"
#include <string>
#include <cstdio>

// This byte array is used to identify compressed files
const char magicNumbers[8] = {(char)0x19,(char)0x17,(char)0x12,(char)0x06,'J','C','L','C'};

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
	 * @brief Open a file for operation. Operation mode will be determined based on the file.
	 * @param fileName Name of the file to be opened.
	 * @return Returns true if file was opened successfully.
	 */
	bool openFile(const std::string& fileName);

	/**
	 * @brief Set boundaries where to start reading and where to end reading.
	 * @param start Starting location in bytes
	 * @param end Last byte to read
	 */
	void setBounds(unsigned long start, unsigned long end);

	/**
	 * @brief Read bytes from the file.
	 * @param dest Buffer to write in
	 * @param bufferSize Size of buffer to write in
	 * @return Amount of bytes read
	 */
	int read(uint8_t* dest, int bufferSize);

	/**
	 * @brief Get operation mode for opened file.
	 * @return UNKNOWN, COMPRESS or DECOMPRESS
	 */
	OpMode getOpMode() const {return opmode;}

	/**
	 * @brief Get total size of the file in bytes.
	 * @return File size in bytes.
	 */
	uint64_t getFileSize() const {return fileSize;}

	/**
	 * @brief If opened file is a compressed file, get the original size from header.
	 * @return Original size in bytes.
	 */
	uint64_t getOriginalSize() const {return originalSize;}

	/**
	 * @brief If opened file is a compressed file, get the bit size used for dictionary entries.
	 * @return Bit size for dictionary entries.
	 */
	uint8_t getBitSize() const {return bitSize;}

	uint64_t getCurrentPos() const;
	uint64_t getReadStart() const {return readStart;}
	uint64_t getReadEnd() const {return readEnd;}

private:
	FILE* filePointer;
	OpMode opmode;
	uint64_t fileSize;
	uint64_t originalSize;
	uint8_t bitSize;
	uint64_t readStart;
	uint64_t readEnd;
};

#endif /* INPUT_HPP */
