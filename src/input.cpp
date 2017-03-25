#include "input.hpp"
#include <string.h>

Input::Input() {
	filePointer = nullptr;
	fileSize = 0;
	outBufferSize = 0;
	outBuffer = nullptr;
}

Input::~Input() {
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

	return true;
}

void Input::compress() {
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
	unsigned long us = 1;
	unsigned long das = 512;
	unsigned long dis = 4096;
	memcpy(outBuffer + 8, &us, 8);
	memcpy(outBuffer + 16, &das, 8);
	memcpy(outBuffer + 24, &dis, 8);

}

bool Input::write(Output& out) {
	unsigned long wbSize = out.getWriteBufferSize();
	for (unsigned int i = 0; i < outBufferSize; i += wbSize) {
		out.write(outBuffer + i, std::min(wbSize, outBufferSize - i));
	}
}
