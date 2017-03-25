#include "output.hpp"
#include <stdio.h>

FileOutput::FileOutput() {
	filePointer = nullptr;
}

FileOutput::~FileOutput() {
	if (filePointer)
		fclose(filePointer);
}

bool FileOutput::openFile(std::string& fileName) {
	filePointer = fopen(fileName.c_str(), "w+");
	if (!filePointer)
		return false;
	return true;
}

void FileOutput::write(const char* data, unsigned long bufferSize) {
	fwrite(data, sizeof(char), bufferSize, filePointer);
}

void StreamOutput::write(const char* data, unsigned long bufferSize) {
	printf("%.*s", bufferSize, data);
}
