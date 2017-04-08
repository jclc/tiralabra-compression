#ifndef ENCODER_HPP
#define ENCODER_HPP

#include <cstdint>
#include "input.hpp"
#include "output.hpp"

const int BUFFER_SIZE = 1024;
const int MIN_BIT_SIZE = 9;
const int MAX_BIT_SIZE = 16;
const int MAX_STR_LEN = 512;

static char encoderErrorMsg[256] = "";

class Encoder {
public:
	Encoder(int p_bitSize);
	~Encoder();

	/**
	 * @brief Read input from input object, encode and write into output
	 * @param input Input object from which to read
	 * @param output Output object to write in
	 * @return nullptr if successful, otherwise pointer to an error string
	 */
	const char* operate(Input& input, Output& output);

protected:
	int bitSize;
};

#endif /* ENCODER_HPP */
