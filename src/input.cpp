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
	outBufferSize = 8;
	outBuffer = (char*) malloc(sizeof(char) * 8);
	strcpy(outBuffer, "JCLCTIRA");
}

bool Input::write(Output& out) {
	out.write(outBuffer, outBufferSize);
}
