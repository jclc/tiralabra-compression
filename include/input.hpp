#ifndef INPUT_HPP
#define INPUT_HPP

#include <string>
#include "output.hpp"
#include <stdio.h>

typedef enum OpMode {
	UNKNOWN,
	COMPRESS,
	DECOMPRESS
} OpMode;

class Input {
public:
	Input();
	~Input();
	bool openFile(std::string& fileName);
	void operate();
	bool write(Output& out);

	OpMode getOpMode() const {return opmode;}
	unsigned long getOriginalSize() const {return originalSize;}
	unsigned long getDataSegmentLoc() const {return dataSegmentLoc;}
	unsigned long getDictionaryLoc() const {return dictionaryLoc;}

private:
	FILE* filePointer;
	unsigned long fileSize;
	unsigned long outBufferSize;
	char* outBuffer;
	OpMode opmode;
	unsigned long originalSize;
	unsigned long dataSegmentLoc;
	unsigned long dictionaryLoc;
};

#endif /* INPUT_HPP */
