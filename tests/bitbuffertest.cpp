#include <gtest/gtest.h>
#include "bitbuffer.hpp"

TEST(BitBufferTest, 12BitWordsStoredCorrectly) {
	BitBuffer bb(12, 3, true);

	ASSERT_EQ(0, bb.wordsUsed) << "Empty BitBuffer doesn't use 0 bits";
	ASSERT_EQ(12, bb.bitSize) << "Stores wrong bit size";

	// Only these 12 bits (1.5 bytes) from both words are to be inserted:
	//                  vvv
	uint16_t word1 = 0x4321;
	uint16_t word2 = 0x8765;

	bb.insert12(word1);
	ASSERT_EQ(1, bb.wordsUsed)
		<< "After inserting a word, doesn't store correct amount of words";
	bb.insert12(word2);
	ASSERT_EQ(2, bb.wordsUsed)
		<< "After inserting a second word, doesn't store correct amount of words";

	uint8_t ret[3];
	memcpy(ret, bb.buffer, sizeof(uint8_t) * 3);
	EXPECT_EQ(0x21, ret[0]) << "The first returned word is incorrect";
	EXPECT_EQ(0x53, ret[1]) << "The second returned word is incorrect";
	EXPECT_EQ(0x76, ret[2]) << "The third returned word is incorrect";
}

TEST(BitBufferTest, 16BitWordsStoredCorrectly) {
	BitBuffer bb(16, 3, true);

	ASSERT_EQ(0, bb.wordsUsed) << "Empty BitBuffer doesn't use 0 bits";
	ASSERT_EQ(16, bb.bitSize) << "Stores wrong bit size";

	uint16_t word1 = 0x4321;
	uint16_t word2 = 0x8765;

	bb.insert16(word1);
	ASSERT_EQ(1, bb.wordsUsed)
		<< "After inserting a word, doesn't store correct amount of words";
	bb.insert16(word2);
	ASSERT_EQ(2, bb.wordsUsed)
		<< "After inserting a second word, doesn't store correct amount of words";

	uint8_t ret[4];
	memcpy(ret, bb.buffer, sizeof(uint8_t) * 4);
	EXPECT_EQ(0x21, ret[0]) << "The first returned word is incorrect";
	EXPECT_EQ(0x43, ret[1]) << "The second returned word is incorrect";
	EXPECT_EQ(0x65, ret[2]) << "The third returned word is incorrect";
	EXPECT_EQ(0x87, ret[3]) << "The fourth returned word is incorrect";
}

TEST(BitBufferTest, Shifts12BitWordsCorrectly) {
	BitBuffer bb1(12, 3, true);
	uint16_t word1 = 0xF321;
	uint16_t word2 = 0xF654;
	uint16_t word3 = 0xF987;
	uint16_t word4 = 0xFCBA;
	bb1.insert12(word1);
	bb1.insert12(word2);
	bb1.insert12(word3);
	bb1.insert12(word4);

	bb1.shift(2);
	ASSERT_EQ(2, bb1.wordsUsed) << "Doesn't store correct amount of bits after shifting";

	uint8_t ret[2];
	memcpy(ret, bb1.buffer, sizeof(uint8_t) * 2);
	EXPECT_EQ(0x87, bb1.buffer[0]) << "The first returned word is incorrect";
	EXPECT_EQ(0xA9, bb1.buffer[1]) << "The second returned word is incorrect";
}

TEST(BitBufferTest, Shifts16BitWordsCorrectly) {
	BitBuffer bb1(16, 6, true);
	uint16_t word1 = 0xF321;
	uint16_t word2 = 0xF654;
	uint16_t word3 = 0xF987;
	uint16_t word4 = 0xBF23;
	uint16_t word5 = 0xECD1;
	uint16_t word6 = 0xFDBA;
	bb1.insert16(word1);
	bb1.insert16(word2);
	bb1.insert16(word3);
	bb1.insert16(word4);
	bb1.insert16(word5);
	bb1.insert16(word6);

	ASSERT_EQ(6, bb1.wordsUsed) << "Doesn't store correct amount of words before shifting";
	bb1.shift(3);
	ASSERT_EQ(3, bb1.wordsUsed) << "Doesn't store correct amount of words after shifting";
	EXPECT_EQ(0x23, bb1.buffer[0]);
	EXPECT_EQ(0xD1, bb1.buffer[2]);
	EXPECT_EQ(0xEC, bb1.buffer[3]);
	EXPECT_EQ(0xBA, bb1.buffer[4]);

	uint16_t* retArray = (uint16_t*) malloc(sizeof(uint16_t) * bb1.wordsUsed);
	unsigned int returnedElements = bb1.getFullArray(retArray);
	ASSERT_EQ(3, returnedElements) << "getFullArray doesn't return correct amount of elements";

	EXPECT_EQ(0xBF23, retArray[0]) << "The first returned word is incorrect";
	EXPECT_EQ(0xECD1, retArray[1]) << "The second returned word is incorrect";
	EXPECT_EQ(0xFDBA, retArray[2]) << "The third returned word is incorrect";
	free(retArray);
}
