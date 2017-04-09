#ifndef BITBUFFER_HPP
#define BITBUFFER_HPP

#include <cstdint>
#include <cstdlib>
#include <iostream>

/**
 * @brief A class which stores arbitrarily sized words in a buffer
 * no actually just 12-bit and 16-bit words because this is too hard
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
	void insert12(uint16_t word);
	void insert16(uint16_t word);

	/**
	 * @brief Remove N bits and shift the remaining bits to the beginning
	 * @param bits Amount of bits to erase
	 */
	void shift(unsigned long words);

	uint16_t* getFullArray(int* returned);

	int bitSize;
	unsigned int wordsUsed;
	unsigned long maxBits;
	uint8_t* buffer;
	uint16_t wordMask;
//	uint16_t firstByte = 0x00FF;
//	uint16_t secondByte = 0xFF00;
};

BitBuffer::BitBuffer(int p_bitSize, unsigned long p_bufferSize, bool encode) {
	buffer = (uint8_t*) malloc(sizeof(uint8_t) * (p_bufferSize / 8) + 2);
	for (int i = 0; i < (p_bufferSize / 8) + 2; ++i)
		buffer[i] = 0;
	wordsUsed = 0U;
	maxBits = p_bufferSize;
	bitSize = p_bitSize;
	wordMask = (1 << (p_bitSize - 1)) - 1;
}

BitBuffer::~BitBuffer() {
	free(buffer);
}

inline void BitBuffer::insert12(uint16_t word) {
	unsigned int i = wordsUsed + (wordsUsed/2);
	if (wordsUsed % 2) {
		buffer[i] |= (word << 4) & 0xF0;
		buffer[i+1] = (word >> 4);
	} else {
		buffer[i] = word;
		buffer[i+1] = (word >> 8) & 0x0F;
	}
	++wordsUsed;
}

inline void BitBuffer::insert16(uint16_t word) {
	buffer[wordsUsed*2] = word;
	buffer[(wordsUsed*2) + 1] = word >> 8;
	++wordsUsed;
}

//inline void BitBuffer::shift(unsigned long words) {
//	if (bitSize == 16) {

//	}
//	unsigned long bitsLeft = bitsUsed - bits;
//	int remainder = bitsLeft % 8;
//	int i = 0;
//	while (bitsLeft > 8) {
//		uint8_t tmp = buffer[bits / 8] << remainder;
//		tmp |= buffer[bits / 8 + 1] >> (8 - remainder);
//		buffer[i] = tmp;
//		++i;
//		bitsLeft -= 8;
//	}
//	buffer[i] = buffer[bits / 8] << remainder;
//	buffer[i+1] = 0;
//	bitsUsed -= bits;
//}

//inline uint16*

#endif /* BITBUFFER_HPP */
