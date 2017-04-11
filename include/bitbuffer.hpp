#ifndef BITBUFFER_HPP
#define BITBUFFER_HPP

#include <cstdint>
#include <cstdlib>
#include <iostream>

/**
 * @brief A class which stores 12- or 16-bit words.
 */
class BitBuffer {
public:

	/**
	 * @brief BitBuffer
	 * @param bitSize Size of a word in bits (either 12 or 16)
	 * @param bufferSize Size of the buffer in bitSize-sized words
	 * @param encode
	 */
	BitBuffer(int bitSize, unsigned int bufferSize, bool encode);
	~BitBuffer();

	/**
	 * @brief Insert 12 first bits of a word in the bit buffer
	 * @param word
	 */
	void insert12(uint16_t word);

	/**
	 * @brief Insert 16 first bits of a word in the bit buffer
	 * @param word
	 */
	void insert16(uint16_t word);

	/**
	 * @brief Remove N (bitSize-sized) words and shift the remaining words to the beginning
	 * @param bits Amount of bits to erase
	 */
	void shift(unsigned int wordsToShift);

	/**
	 * @brief Empties the buffer. Doesn't overwrite old values, only moves pointer.
	 */
	void clear();

	/**
	 * @brief Convert an array of bitSize-sized words into full 16-bit words and write
	 * to array pointed by the pointer
	 * @param arrayPtr Array to write in
	 * @return Number of elements written
	 */
	unsigned int getFullArray(uint16_t* arrayPtr);

	int bitSize;
	unsigned int wordsUsed;
	unsigned int maxWords;
	uint8_t* buffer;
	uint16_t wordMask;
};

BitBuffer::BitBuffer(int p_bitSize, unsigned int p_bufferSize, bool encode) {
	buffer = (uint8_t*) malloc(sizeof(uint8_t) * (p_bufferSize +
		(p_bitSize == 12 ? p_bufferSize/2 : p_bufferSize) + 2));
	for (int i = 0; i < (p_bufferSize / 8) + 2; ++i)
		buffer[i] = 0;
	wordsUsed = 0U;
	maxWords = p_bufferSize;
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

inline void BitBuffer::shift(unsigned int wordsToShift) {
	if (wordsToShift >= wordsUsed) {
		wordsUsed = 0;
		return;
	}

	if (bitSize == 16) {
		for (int i = 0; i < (wordsUsed - wordsToShift); ++i) {
			buffer[i*2] = buffer[(wordsToShift+i)*2];
			buffer[i*2+1] = buffer[(wordsToShift+i)*2+1];
		}
	} else {
		int byteOffset = wordsToShift*3/2;
		if (wordsToShift % 2) {
			unsigned int finalByte = (wordsUsed - wordsToShift)*3/2;
			for (int b = 0; b < finalByte; ++b) {
				buffer[b] = buffer[b+byteOffset] >> 4 | buffer[b+byteOffset+1] << 4;
			}
			buffer[(wordsUsed - wordsToShift)*3/2] = buffer[wordsUsed*3/2-1] >> 4;
		} else {
			// Even number of words means we can simply copy the necessary bytes
			// without the need for bit shifting
			for (int i = 0; i < (wordsUsed - wordsToShift)*3/2; ++i) {
				buffer[i] = buffer[byteOffset+i];
			}
		}
	}
	wordsUsed -= wordsToShift;
}

inline void BitBuffer::clear() {
	wordsUsed = 0;
}

inline unsigned int BitBuffer::getFullArray(uint16_t* arrayPtr) {
	if (bitSize == 16) {
		for (int i = 0; i < wordsUsed; ++i) {
			arrayPtr[i] = (buffer[i*2] | (buffer[(i*2)+1] << 8));
		}
	} else {
		for (int i = 0; i < wordsUsed; ++i) {
			if (i % 2) {
				arrayPtr[i] = buffer[i*3/2] >> 4 | (buffer[i*3/2+1] << 4);
			} else {
				arrayPtr[i] = buffer[i*3/2] | ((buffer[i*3/2+1] & 0x0F) << 8);
			}
		}
	}
	return wordsUsed;
}

#endif /* BITBUFFER_HPP */
