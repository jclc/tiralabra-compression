/*
 * This is a testing utility. Do not include this in the main program.
 */
#ifndef TESTOUTPUT_HPP
#define TESTOUTPUT_HPP

#include "output.hpp"

/**
 * @brief A derivative of the Output class for catching output for purposes of testing
 */
class TestOutput: public Output {
public:
	TestOutput();
	~TestOutput();
	virtual void write(const char* data, unsigned long i_bufferSize);

	/**
	 * @brief Get the number of bytes written to the buffer
	 * @return Number of bytes written to the buffer
	 */
	unsigned long getOutputCharCount();

	/**
	 * @brief Get a pointer to the beginning of the buffer. Note that you will need
	 * to get the buffer again after writing since writing data may cause the buffer to
	 * be reallocated and thus change in memory.
	 * @return Pointer to the beginning of the buffer
	 */
	const char* getOutput();

private:

	/**
	 * @brief Double the size of the buffer
	 */
	void enlargeBuffer();

	char* buffer;

	/**
	 * @brief Number of bytes written
	 */
	unsigned long size;

	/**
	 * @brief Allocated size of the buffer
	 */
	unsigned long bufferSize;
};

#endif /* TESTOUTPUT_HPP */
