#include "input.hpp"
#include <string.h>
#include <cstdint>

Input::Input() {
	filePointer = nullptr;
	fileSize = 0;
	outBufferSize = 0;
	outBuffer = nullptr;
	dataSegmentLoc = 0UL;
	dictionaryLoc = 0UL;
	opmode = UNKNOWN;
}

Input::~Input() {
	if (filePointer)
		fclose(filePointer);
	free(outBuffer);
}

bool Input::openFile(std::string& fileName) {
	filePointer = fopen(fileName.c_str(), "r");
	if (!filePointer)
		return false;

	fseek(filePointer, 0, SEEK_END);
	fileSize = ftell(filePointer);
	fseek(filePointer, 0, SEEK_SET);

	if (fileSize >= 32) {
		char header[32];
		fread(header, sizeof(char), 32, filePointer);
		if (memcmp(header, "JCLCTIRA", 8) == 0) {
			// Found a compressed file
			opmode = DECOMPRESS;
			memcpy(&originalSize, header + 8, sizeof(uint64_t));
			memcpy(&dataSegmentLoc, header + 16, sizeof(uint64_t));
			memcpy(&dictionaryLoc, header + 24, sizeof(uint64_t));
		} else {
			opmode = COMPRESS;
		}
	} else {
		opmode = COMPRESS;
	}

	return true;
}

void Input::operate(Output& out) {
	if (opmode == COMPRESS) {
		outBufferSize = 8;
		outBuffer = (char*) malloc(sizeof(char) * outBufferSize);
		/* Write start header
		 * <Bytes>   <Content>
		 * 0-7       Magic numbers
		 */
		memcpy(outBuffer, "JCLCTIRA", 8);
		memcpy(outBuffer + 8, &fileSize, 8);
		dataSegmentLoc = 8UL;

		int i = 0;
		int n;
		char readBuffer[1024];

		// TODO: COMPRESS AND WRITE

//		uint64_t wbSize = out.getWriteBufferSize();
//		for (uint64_t i = 0; i < outBufferSize; i += wbSize) {
//			out.write(outBuffer + i, std::min(wbSize, outBufferSize - i));
//		}

		/*
		 * Write end header
		 * 0-7      Original size (unsigned long)
		 * 8-15     Data segment start location
		 * 16-23     Dictionary start location
		 */
		// Temporary
		char header[32];
		memcpy(outBuffer + 16, &dataSegmentLoc, 8);
//		memcpy(outBuffer + 24, &dis, 8);


	} else if (opmode == DECOMPRESS) {
		// TODO
		return;
	}
	return;
}

void Input::enlargeBuffer() {
	if (outBufferSize == 0)
		outBufferSize = 1;
	outBufferSize *= 2;
	outBuffer = (char*) realloc(outBuffer, sizeof(char) * outBufferSize);
}
