#include "input.hpp"
#include <string.h>

Input::Input() {
	filePointer = nullptr;
	fileSize = 0;
	outBufferSize = 0;
	outBuffer = nullptr;
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

	char header[32];
	if (fileSize >= 32) {
		fread(header, sizeof(char), 32, filePointer);
		if (memcmp(header, "JCLCTIRA", 8) == 0) {
			// Found a compressed file
			opmode = DECOMPRESS;
			memccpy(&originalSize, header + 8, 1, sizeof(unsigned long));
			memccpy(&dataSegmentLoc, header + 16, 1, sizeof(unsigned long));
			memccpy(&dictionaryLoc, header + 24, 1, sizeof(unsigned long));
		} else {
			opmode = COMPRESS;
		}
	} else {
		opmode = COMPRESS;
	}

	return true;
}

void Input::operate() {
	outBufferSize = 32;
	outBuffer = (char*) malloc(sizeof(char) * outBufferSize);
	/* Write header
	 * <Bytes>   <Content>
	 * 0-7       Magic numbers
	 * 8-15      Original size (unsigned long)
	 * 16-23     Data segment start location
	 * 24-31     Dictionary start location
	 */
	memcpy(outBuffer, "JCLCTIRA", 8);
	// Temporary
	unsigned long os = fileSize;
	unsigned long das = 512UL;
	unsigned long dis = 4096UL;
	memcpy(outBuffer + 8, &os, 8);
	memcpy(outBuffer + 16, &das, 8);
	memcpy(outBuffer + 24, &dis, 8);

}

bool Input::write(Output& out) {
	unsigned long wbSize = out.getWriteBufferSize();
	for (unsigned int i = 0; i < outBufferSize; i += wbSize) {
		out.write(outBuffer + i, std::min(wbSize, outBufferSize - i));
	}
}
