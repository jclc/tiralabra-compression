#include "input.hpp"
#include <cstring>
#include <cstdint>
#include <iostream>

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
		char beginHeader[8];
		fread(beginHeader, sizeof(char), 8, filePointer);
		if (memcmp(beginHeader, "JCLCTIRA", 8) == 0) {
			// Found a compressed file
			char endHeader[24];
			opmode = DECOMPRESS;
			fseek(filePointer, -24, SEEK_END);
			fread(endHeader, sizeof(char), 24, filePointer);
			memcpy(&originalSize, endHeader, 8);
			memcpy(&dataSegmentLoc, endHeader + 8, 8);
			memcpy(&dictionaryLoc, endHeader + 16, 8);
		} else {
			// Found an uncompressed file under the size of 32 bytes
			opmode = COMPRESS;
			originalSize = fileSize;
		}
	} else {
		// Found an uncompressed file
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

		int i = 0;
		int n;
		char readBuffer[1024];

		// TODO: COMPRESS AND WRITE

//		uint64_t wbSize = out.getWriteBufferSize();
//		for (uint64_t i = 0; i < outBufferSize; i += wbSize) {
//			out.write(outBuffer + i, std::min(wbSize, outBufferSize - i));
//		}
		std::string tempContent = "\n\n***TEMPORARY***\n\n";
		out.write(tempContent.c_str(), tempContent.size());

		/*
		 * Write end header
		 * 0-7      Original size (unsigned long)
		 * 8-15     Data segment start location
		 * 16-23     Dictionary start location
		 */
		char tempArray[8];
		memcpy(tempArray, &fileSize, 8);
		out.write(tempArray, 8);
		memcpy(tempArray, &dataSegmentLoc, 8);
		out.write(tempArray, 8);
		memcpy(tempArray, &dictionaryLoc, 8);
		out.write(tempArray, 8);


	} else if (opmode == DECOMPRESS) {
		// TODO
		return;
	}
	return;
}
