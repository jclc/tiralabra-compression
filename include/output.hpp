#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <string>
#include <stdio.h>

const unsigned long WRITE_BUFFER_SIZE = 1024;

/**
 * @brief Virtual class that handles the program output
 */
class Output {
public:
	virtual bool openFile(std::string& fileName) {}
	virtual void write(const char* data, unsigned long bufferSize) = 0;
	virtual unsigned long getWriteBufferSize() {return WRITE_BUFFER_SIZE;}
};

/**
 * @brief Output class for writing into a file
 */
class FileOutput: public Output {
public:
	FileOutput();
	~FileOutput();

	/**
	 * @brief Open a file for writing. If exists, will be truncated to zero size.
	 * @param fileName Name of the file in which to write
	 * @return True if file was successfully opened
	 */
	virtual bool openFile(std::string& fileName) override;

	/**
	 * @brief Write data into file. Can be called consecutively to write in chunks.
	 * @param data Pointer to char array
	 * @param bufferSize Amount of bytes to write
	 */
	virtual void write(const char* data, unsigned long bufferSize) override;
private:
	FILE* filePointer;
};

/**
 * @brief Output class for writing into standard output stream
 */
class StreamOutput: public Output {
public:
	StreamOutput() {}

	/**
	 * @brief Write data into stdout. Can be called consecutively to write in chunks.
	 * @param data Pointer to char array
	 * @param bufferSize Amount of bytes to write
	 */
	virtual void write(const char* data, unsigned long bufferSize) override;
};

#endif /* OUTPUT_HPP */
