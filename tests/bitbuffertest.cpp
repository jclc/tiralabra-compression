#include <gtest/gtest.h>
#include "bitbuffer.hpp"

TEST(BitBufferTest, StoresCorrectly) {
	BitBuffer bb(12, 3, true);

	ASSERT_EQ(0, bb.bitsUsed) << "Empty BitBuffer doesn't use 0 bits";
	ASSERT_EQ(12, bb.bitSize) << "Stores wrong bit size";

	// Only these 12 bytes from both words are to be inserted:
	//                  vvv
	uint16_t word1 = 0xF321;
	uint16_t word2 = 0xF654;

	bb.insert(word1);
	ASSERT_EQ(12, bb.bitsUsed)
		<< "After inserting a word, doesn't store correct amount of bits";

	bb.insert(word2);
	ASSERT_EQ(24, bb.bitsUsed)
		<< "After inserting a second word, doesn't store correct amount of bits";

	uint8_t ret[3];
	memcpy(ret, bb.buffer, sizeof(uint8_t) * 3);
	EXPECT_EQ(0x21, ret[0]) << "The first returned word is incorrect";
	EXPECT_EQ(0x43, ret[1]) << "The second returned word is incorrect";
	EXPECT_EQ(0x65, ret[2]) << "The third returned word is incorrect";
}

TEST(BitBufferTest, ShiftsCorrectly) {
	BitBuffer bb1(12, 3, true);
	uint16_t word1 = 0xF321;
	uint16_t word2 = 0xF654;
	uint16_t word3 = 0xF987;
	bb1.insert(word1);
	bb1.insert(word2);
	bb1.insert(word3);

	bb1.shift(12);
	ASSERT_EQ(24, bb1.bitsUsed) << "Doesn't store correct amount of bits after shifting";

	uint8_t ret[2];
	memcpy(ret, bb1.buffer, sizeof(uint8_t) * 2);
	EXPECT_EQ(0xFB, bb1.buffer[0]) << "The first returned word is incorrect";
	EXPECT_EQ(0xA0, bb1.buffer[1]) << "The second returned word is incorrect";
}
