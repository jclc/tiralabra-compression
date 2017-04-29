#ifndef DECODER_HPP
#define DECODER_HPP

#include <memory>
#include "input.hpp"
#include "output.hpp"
#include "progressbar.hpp"
#include "common.hpp"

class Decoder {
public:
	Decoder() {}

	void decode(Input& input, Output& output, std::shared_ptr<ProgressBar> progress);
};




#endif /* DECODER_HPP */
