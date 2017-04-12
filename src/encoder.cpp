#include "encoder.hpp"
#include <cstdint>
#include <cstring>
#include "stringtable.hpp"
#include <stdexcept>
#include "bitbuffer.hpp"
#include <cmath>

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
	 * 0-7       Magic numbers (defined in input.hpp)
	 */
	output.write(magicNumbers, 8);

	// TODO: COMPRESS AND WRITE

	unsigned int maxEntries = std::pow(2, bitSize) - 1;
	StringTable strTable(maxEntries, MAX_STR_LEN);
	uint8_t inBuffer[BUFFER_SIZE];
	BitBuffer bb(bitSize, BUFFER_SIZE, true);
	int bytesRead = input.read(inBuffer, 1);


	if (bytesRead == 0)
		throw std::runtime_error("Could not read from input file or file is empty");

	strTable.insert(inBuffer[0]);

	while ((bytesRead = input.read(inBuffer, BUFFER_SIZE)) != 0) {
		for (int i = 0; i < bytesRead; ++i) {
			bb.insert(inBuffer[i]);
		}
		output.write((char*) bb.buffer, bb.getFullBytes());
		bb.shift(bb.getFullWords());
	}
	// Write the remaining bytes
	output.write((char*) bb.buffer, bb.getTotalBytes());

	/*
	 * Write end header
	 * <Bytes>   <Content>
	 * 0-7       Original size (unsigned long)
	 * 8         Bit size of each dictionary entry
	 * 9-23      Reserved
	 */
	char tempArray[8];

	// FIX: This restricts endianness-compatibility.
	uint64_t originalSize = input.getOriginalSize();
	memcpy(tempArray, &originalSize, 8);
	output.write(tempArray, 8);

	memcpy(tempArray, &bitSize, 1);
	output.write(tempArray, 1);

	const char nullArray[15] = "";
	output.write(nullArray, 15);
	return nullptr;
}
