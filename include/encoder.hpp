#ifndef ENCODER_HPP
#define ENCODER_HPP

#include <cstdint>
#include "input.hpp"
#include "output.hpp"

const int BUFFER_SIZE = 64;
const int MIN_BIT_SIZE = 12;
const int MAX_BIT_SIZE = 16;
const int MAX_STR_LEN = 4096;

static char encoderErrorMsg[256] = "";

namespace encoder {


/**
 * @brief Read input from input object, encode and write into output
 * @param input Input object from which to read
 * @param output Output object to write in
 * @return nullptr if successful, otherwise pointer to an error string
 */
const char* encode(Input& input, Output& output, unsigned int p_bitSize);

}

#endif /* ENCODER_HPP */
