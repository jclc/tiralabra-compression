#ifndef ENCODER_HPP
#define ENCODER_HPP

#include <cstdint>
#include "input.hpp"
#include "output.hpp"
#include "progressbar.hpp"
#include "common.hpp"
#include <memory>

class Encoder {
public:
	Encoder() {}

/**
 * @brief Read input from input object, encode and write into output
 * @param input Input object from which to read
 * @param output Output object to write in
 * @param header False if header (both at the start and the end) should be omitted
 * @return nullptr if successful, otherwise pointer to an error string
 */
	void encode(Input& input, Output& output,
		unsigned int p_bitSize, bool startHeader, bool endHeader,
		std::shared_ptr<ProgressBar> progress);
};

#endif /* ENCODER_HPP */
