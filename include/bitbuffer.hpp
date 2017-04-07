#ifndef BITBUFFER_HPP
#define BITBUFFER_HPP

#include <cstdint>
#include <cstdlib>
#include <iostream>

/**
 * @brief A class which stores arbitrarily sized words in a buffer
 */
class BitBuffer {
public:
	BitBuffer(int bitSize, int bufferSize, bool encode);
	~BitBuffer();

	/**
	 * @brief Insert N first bits of a word in the bit buffer
	 * @param word
	 */
	void insert(uint16_t word);

	/**
	 * @brief Remove N bits and shift the remaining bits to the beginning
	 * @param bits Amount of bits to erase
	 */
	void shift(unsigned long bits);

	int bitSize;
	unsigned long bitsUsed;
	uint8_t* buffer;
};

BitBuffer::BitBuffer(int p_bitSize, int p_bufferSize, bool encode) {
	buffer = (uint8_t*) malloc(sizeof(uint8_t) * p_bufferSize * 2);
	bitsUsed = 0UL;
	bitSize = p_bitSize;
}

BitBuffer::~BitBuffer() {
	free(buffer);
}

inline void BitBuffer::insert(uint16_t word) {
	int remainder = bitsUsed % 8;
	buffer[bitsUsed / 8] |= (word << remainder);
	buffer[bitsUsed / 8 + 1] = (word >> (8 - remainder));

	bitsUsed += bitSize;
}

inline void shift(unsigned long bits) {

}

#endif /* BITBUFFER_HPP */
