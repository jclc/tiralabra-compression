#include "encoder.hpp"
#include <cstdint>
#include <cstring>
#include "stringtable.hpp"
#include <stdexcept>
#include "bitbuffer.hpp"
#include <cmath>

const char* Encoder::operate(Input& input, Output& output) {

	/* Write start header
	 * <Bytes>   <Content>
	 * 0-7       Magic numbers (defined in input.hpp)
	 */
	output.write(magicNumbers, 8);

	unsigned int bitSize = input.getBitSize();
	if (bitSize != MIN_BIT_SIZE && bitSize != MAX_BIT_SIZE)
		throw std::runtime_error("Invalid bit size");

	unsigned int maxEntries = std::pow(2, bitSize) - 1;
	StringTable strTable(maxEntries, MAX_STR_LEN);
	uint8_t readBuffer[BUFFER_SIZE];
	BitBuffer bb(bitSize, BUFFER_SIZE, true);

	unsigned int maxBytes;
	if (bitSize == 12)
		maxBytes = BUFFER_SIZE*3/2;
	else
		maxBytes = BUFFER_SIZE*2;

	int bytesRead = input.read(readBuffer, 1);

	if (bytesRead == 0)
		throw std::runtime_error("Could not read from input file or file is empty");

	uint16_t str = (uint16_t) readBuffer[0];
	uint16_t temp;
	uint8_t sym;

	while ((bytesRead = input.read(readBuffer, BUFFER_SIZE)) != 0) {
		for (int i = 0; i < bytesRead; ++i) {
			sym = readBuffer[i];
			temp = strTable.getNextEntry(str, sym);
			if (temp) {
				// String + Symbol is already in the string table
				str = temp;
			} else {
				// String + Symbol is not yet in the string table
				bb.insert(str);
				strTable.insert(str, sym);
				str = (uint16_t) sym;
			}

			if (bb.getFullBytes() >= maxBytes) {
				output.write((char*) bb.buffer, bb.getFullBytes());
				bb.shift(bb.getFullWords());
			}
		}
		output.write((char*) bb.buffer, bb.getFullBytes());
		bb.shift(bb.getFullWords());
	}

	// Write the remaining bytes
	bb.insert(str);
	output.write((char*) bb.buffer, bb.getTotalBytes());

	/*
	 * Write end header
	 * <Bytes>   <Content>
	 * 0-7       Original size (unsigned long)
	 * 8         Bit size of code words
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
