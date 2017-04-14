#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <string>
#include <cstdio>

/**
 * @brief Virtual class that handles the program output
 */
class Output {
public:
	virtual ~Output() {}

	virtual bool openFile(std::string& fileName) {return true;}
	virtual void write(const char* data, unsigned long bufferSize) = 0;
};

/**
 * @brief Output class for writing into a file
 */
class FileOutput: public Output {
public:
	FileOutput();
	virtual ~FileOutput() override;

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
	virtual ~StreamOutput() override {}

	/**
	 * @brief Write data into stdout. Can be called consecutively to write in chunks.
	 * @param data Pointer to char array
	 * @param bufferSize Amount of bytes to write
	 */
	virtual void write(const char* data, unsigned long bufferSize) override;
};

/**
 * @brief Output class that does nothing
 */
class NullOutput: public Output {
public:
	NullOutput() {}
	virtual ~NullOutput() override {}

	/**
	 * @brief Do nothing.
	 * @param data Doesn't matter
	 * @param bufferSize Doesn't matter
	 */
	virtual void write(const char* data, unsigned long bufferSize) override {}
};

#endif /* OUTPUT_HPP */
