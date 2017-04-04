/*
 * This is a testing utility. Do not include this in the main program.
 */
#include "testoutput.hpp"
#include <cstring>

TestOutput::TestOutput() {
	bufferSize = 1024UL;
	buffer = (char*) malloc(sizeof(char) * size);
	size = 0UL;
}

TestOutput::~TestOutput() {
	free(buffer);
}

void TestOutput::write(const char* data, unsigned long i_bufferSize) {
	while (bufferSize < size + i_bufferSize)
		enlargeBuffer();

	memcpy(buffer + size, data, i_bufferSize);
	size += i_bufferSize;

}

void TestOutput::enlargeBuffer() {
	bufferSize *= 2;
	buffer = (char*) realloc(buffer, sizeof(char) * bufferSize);
}

unsigned long TestOutput::getOutputCharCount() {
	return size;
}

const char* TestOutput::getOutput() {
	return buffer;
}
