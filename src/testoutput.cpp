/*
 * This is a testing utility. Do not include this in the main program.
 */
#include "testoutput.hpp"
#include <cstring>
#include <cstdio>

TestOutput::TestOutput() {
	bufferSize = 1024UL;
	buffer = (char*) malloc(sizeof(char) * bufferSize);
	size = 0UL;
}

TestOutput::~TestOutput() {
	if (buffer) {
		free(buffer);
		buffer = nullptr;
	}
}

void TestOutput::write(const char* data, unsigned long p_bufferSize) {
	while (bufferSize < size + p_bufferSize)
		enlargeBuffer();

	memcpy(buffer + size, data, p_bufferSize);
	size += p_bufferSize;

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
