#include "input.hpp"
#include "encoder.hpp"
#include <cstring>
#include <cstdint>
#include <cstdio>
#include <iostream>


Input::Input() {
	filePointer = nullptr;
	fileSize = 0UL;
	originalSize = 0UL;
	bitSize = 0;
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
			memcpy(&bitSize, endHeader + 8, 1);
		} else {
			// Found an uncompressed file under the size of 32 bytes
			opmode = COMPRESS;
		}
	} else {
		// Found an uncompressed file
		opmode = COMPRESS;
	}

	if (opmode == COMPRESS) {
		bitSize = 16;
	}

	return true;
}

int Input::read(uint8_t *dest, int bufferSize) {
	return fread(dest, sizeof(uint8_t), bufferSize, filePointer);
}


