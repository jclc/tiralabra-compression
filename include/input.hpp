#ifndef INPUT_HPP
#define INPUT_HPP

#include <string>
#include "output.hpp"
#include <stdio.h>

class Input {
public:
	Input();
	bool openFile(std::string& fileName);
	void compress();
	bool write(Output& out);
private:
	FILE* filePointer;
	unsigned long fileSize;
	unsigned long outBufferSize;
	char* outBuffer;
};

#endif /* INPUT_HPP */
