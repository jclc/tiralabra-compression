#ifndef DECODER_HPP
#define DECODER_HPP

#include "input.hpp"
#include "output.hpp"

static char decoderErrorMsg[256] = "";

namespace decoder {

const char* decode(Input& input, Output& output);

}

#endif /* DECODER_HPP */
