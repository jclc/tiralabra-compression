#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <string>
#include <stdio.h>

const unsigned long WRITE_BUFFER_SIZE = 1024;

class Output {
public:
	virtual bool openFile(std::string& fileName) {}
	virtual void write(const char* data, unsigned long bufferSize) = 0;
	virtual unsigned long getWriteBufferSize() {return WRITE_BUFFER_SIZE;}
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

class StreamOutput: public Output {
public:
	StreamOutput() {}
	virtual void write(const char* data, unsigned long bufferSize) override;
};

#endif /* OUTPUT_HPP */
