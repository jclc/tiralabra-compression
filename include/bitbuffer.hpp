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

	/**
	 * @brief BitBuffer
	 * @param bitSize Size of a word in bits
	 * @param bufferSize Size of the buffer in _bits_
	 * @param encode
	 */
	BitBuffer(int bitSize, unsigned long bufferSize, bool encode);
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
	unsigned long maxBits;
	uint8_t* buffer;
};

BitBuffer::BitBuffer(int p_bitSize, unsigned long p_bufferSize, bool encode) {
	buffer = (uint8_t*) malloc(sizeof(uint8_t) * (p_bufferSize / 8) + 2);
	for (int i = 0; i < (p_bufferSize / 8) + 2; ++i)
		buffer[i] = 0;
	bitsUsed = 0UL;
	maxBits = p_bufferSize;
	bitSize = p_bitSize;
}

BitBuffer::~BitBuffer() {
	free(buffer);
}

inline void BitBuffer::insert(uint16_t word) {
	int remainder = bitsUsed % 8;
	// Append the first bits of the new word into the last word
	buffer[bitsUsed / 8] |= (word >> remainder);
	// Put the remaining bits of the new word into the new entry
	buffer[bitsUsed / 8 + 1] = (word << (8 - remainder));

	bitsUsed += bitSize;
}

inline void BitBuffer::shift(unsigned long bits) {
	unsigned long bitsLeft = bitsUsed - bits;
	int remainder = bitsLeft % 8;
	int i = 0;
	while (bitsLeft > 8) {
		uint8_t tmp = buffer[bits / 8] << remainder;
		printf("%x\n", tmp);
		tmp |= buffer[bits / 8 + 1] >> (8 - remainder);
		printf("%x\n", tmp);
		buffer[i] = tmp;
		++i;
		bitsLeft -= 8;
	}
	buffer[i] = buffer[bits / 8] << remainder;
	buffer[i+1] = 0;
	bitsUsed -= bits;
}

#endif /* BITBUFFER_HPP */
