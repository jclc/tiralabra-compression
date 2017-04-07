#ifndef DECODER_HPP
#define DECODER_HPP

#include "input.hpp"
#include "output.hpp"

static char decoderErrorMsg[256] = "";

class Decoder {
public:
	Decoder(int p_bitSize);
	~Decoder();

	const char* operate(Input& input, Output& output);

protected:
	int bitSize;
};

#endif /* DECODER_HPP */
