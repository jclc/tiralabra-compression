#include "encoder.hpp"
#include <cstdint>
#include <cstring>
#include "stringtable.hpp"
#include <stdexcept>
#include "bitbuffer.hpp"

Encoder::Encoder(int p_bitSize) {
	if (p_bitSize != MIN_BIT_SIZE && p_bitSize != MAX_BIT_SIZE) {
		throw std::runtime_error("Invalid bit size");
	}
	bitSize = p_bitSize;
}

Encoder::~Encoder() {

}

const char* Encoder::operate(Input& input, Output& output) {

	/* Write start header
	 * <Bytes>   <Content>
	 * 0-7       Magic numbers ("JCLCTIRA" in ASCII)
	 */
	output.write("JCLCTIRA", 8);

	// TODO: COMPRESS AND WRITE

	StringTable strTable((1 << (bitSize-1)), MAX_STR_LEN);
	uint8_t inBuffer[BUFFER_SIZE];
	input.read(inBuffer, 1);
	int bytesRead = -1;
	while ((bytesRead = input.read(inBuffer, BUFFER_SIZE)) != 0) {

	}

	/*
	 * Write end header
	 * <Bytes>   <Content>
	 * 0-7       Original size (unsigned long)
	 * 8         Bit size of each dictionary entry
	 * 9-23      Reserved
	 */
	char tempArray[8];

	uint64_t originalSize = input.getOriginalSize();
	memcpy(tempArray, &originalSize, 8);
	output.write(tempArray, 8);

	memcpy(tempArray, &bitSize, 1);
	output.write(tempArray, 1);

	const char nullArray[15] = "";
	output.write(nullArray, 15);
	return nullptr;
}
