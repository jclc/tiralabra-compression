#include "input.hpp"
#include <cstring>
#include <cstdint>
#include <cstdio>
#include <iostream>

const uint64_t BUFFER_SIZE = 1024UL;
const int MIN_BIT_SIZE = 9;
const int MAX_BIT_SIZE = 16;

Input::Input() {
	filePointer = nullptr;
	fileSize = 0UL;
	dataSegmentLoc = 0UL;
	dictionaryLoc = 0UL;
	opmode = UNKNOWN;
}

Input::~Input() {
	if (filePointer)
		fclose(filePointer);
}

bool Input::openFile(const std::string& fileName) {
	filePointer = fopen(fileName.c_str(), "r");
	if (!filePointer)
		return false;

	fseek(filePointer, 0, SEEK_END);
	fileSize = ftell(filePointer);
	fseek(filePointer, 0, SEEK_SET);

	if (fileSize >= 32) {
		char startHeader[8];
		fread(startHeader, sizeof(char), 8, filePointer);
		if (memcmp(startHeader, "JCLCTIRA", 8) == 0) {
			// Found a compressed file
			char endHeader[24];
			opmode = DECOMPRESS;
			fseek(filePointer, -24, SEEK_END);
			fread(endHeader, sizeof(char), 24, filePointer);
			memcpy(&originalSize, endHeader, 8);
//			memcpy(&dataSegmentLoc, endHeader + 8, 8);
			dataSegmentLoc = 8UL; // data segment always starts after magic numbers
			memcpy(&dictionaryLoc, endHeader + 16, 8);
		} else {
			// Found an uncompressed file under the size of 32 bytes
			opmode = COMPRESS;
			originalSize = fileSize;
		}
	} else {
		// Found an uncompressed file
		originalSize = fileSize;
		opmode = COMPRESS;
	}

	return true;
}

void Input::operate(Output& out) {
	if (opmode == COMPRESS) {
		/* Write start header
		 * <Bytes>   <Content>
		 * 0-7       Magic numbers ("JCLCTIRA" in ASCII)
		 */
		out.write("JCLCTIRA", 8);
		dataSegmentLoc = 8UL;

		// TODO: COMPRESS AND WRITE

		// For now, just use MAX_BIT_SIZE
		int bits = MAX_BIT_SIZE;
		char* readBuffer = (char*) malloc(sizeof(char) * (1 << (MAX_BIT_SIZE - 1)));
		uint16_t dictionary[(1 << (MAX_BIT_SIZE - 1)) - 256];

		size_t bytesRead = -1;
		uint64_t index = 0;
		int i;
		while ((bytesRead = fread(readBuffer, sizeof(char), BUFFER_SIZE, filePointer)) != 0) {
			i = 0;
			out.write(readBuffer, bytesRead);
			index += bytesRead;
		}

		std::string tempContent = "\n\n***TEMPORARY***\n\n";
		out.write(tempContent.c_str(), tempContent.size());

		/*
		 * Write end header
		 * <Bytes>   <Content>
		 * 0-7       Original size (unsigned long)
		 * 8-15      Reserved
		 * 16-23     Dictionary start location
		 */
		char tempArray[8];
		memcpy(tempArray, &fileSize, 8);
		out.write(tempArray, 8);
//		memcpy(tempArray, &dataSegmentLoc, 8);
//		out.write(tempArray, 8);
		const char nullArray[8] = {0, 0, 0, 0, 0, 0, 0, 0};
		out.write(nullArray, 8);
		memcpy(tempArray, &dictionaryLoc, 8);
		out.write(tempArray, 8);


	} else if (opmode == DECOMPRESS) {
		// TODO
		return;
	}
	return;
}
