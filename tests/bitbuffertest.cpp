#include <gtest/gtest.h>
#include "bitbuffer.hpp"

TEST(BitBufferTest, StoresCorrectly) {
	BitBuffer bb(12, 3, true);

	EXPECT_EQ(0, bb.bitsUsed) << "Empty BitBuffer doesn't use 0 bits";
	EXPECT_EQ(12, bb.bitSize) << "Stores wrong bit size";

	uint16_t word1 = 0x00FF;
	uint16_t word2 = 0x0AFF;

	bb.insert(word1);
	ASSERT_EQ(12, bb.bitsUsed)
		<< "After inserting a word, doesn't store correct amount of bits";

	bb.insert(word2);
	ASSERT_EQ(24, bb.bitsUsed)
		<< "After inserting a second word, doesn't store correct amount of bits";

	uint8_t ret[3];
	memcpy(ret, bb.buffer, sizeof(uint8_t) * 3);

	EXPECT_EQ(0xFF, ret[0]) << "The first returned word is incorrect";
	EXPECT_EQ(0xF0, ret[1]) << "The second returned word is incorrect";
	EXPECT_EQ(0xAF, ret[2]) << "The third returned word is incorrect";
}
