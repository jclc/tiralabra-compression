#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <string>
#include <stdio.h>

const unsigned long WRITE_BUFFER_SIZE = 1024;

class Output {
public:
	virtual bool openFile(std::string& fileName) {}
	virtual void write(const char* data, unsigned long bufferSize) = 0;
};

class FileOutput: public Output {
public:
	FileOutput();
	~FileOutput();
	virtual bool openFile(std::string& fileName) override;
	virtual void write(const char* data, unsigned long bufferSize) override;
private:
	FILE* filePointer;
};

class StdOutput: public Output {
public:
	StdOutput() {}
	virtual void write(const char* data, unsigned long bufferSize) override;
};

#endif /* OUTPUT_HPP */
