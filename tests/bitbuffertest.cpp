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

	bb.insert(word1);
	ASSERT_EQ(1, bb.wordsUsed)
		<< "After inserting a word, doesn't store correct amount of words";
	bb.insert(word2);
	ASSERT_EQ(2, bb.wordsUsed)
		<< "After inserting a second word, doesn't store correct amount of words";

	uint8_t ret[3];
	memcpy(ret, bb.buffer, sizeof(uint8_t) * 3);
	EXPECT_EQ(0x21, ret[0]) << "The first returned word is incorrect";
	EXPECT_EQ(0x53, ret[1]) << "The second returned word is incorrect";
	EXPECT_EQ(0x76, ret[2]) << "The third returned word is incorrect";
}

TEST(BitBufferTest, 16BitWordsStoredCorrectly) {
	BitBuffer bb(16, 2, true);

	ASSERT_EQ(0, bb.wordsUsed) << "Empty BitBuffer doesn't use 0 bits";
	ASSERT_EQ(16, bb.bitSize) << "Stores wrong bit size";

	uint16_t word1 = 0x4321;
	uint16_t word2 = 0x8765;

	bb.insert(word1);
	ASSERT_EQ(1, bb.wordsUsed)
		<< "After inserting a word, doesn't store correct amount of words";
	bb.insert(word2);
	ASSERT_EQ(2, bb.wordsUsed)
		<< "After inserting a second word, doesn't store correct amount of words";

	uint8_t ret[4];
	memcpy(ret, bb.buffer, sizeof(uint8_t) * 4);
	EXPECT_EQ(0x21, ret[0]) << "The first returned word is incorrect";
	EXPECT_EQ(0x43, ret[1]) << "The second returned word is incorrect";
	EXPECT_EQ(0x65, ret[2]) << "The third returned word is incorrect";
	EXPECT_EQ(0x87, ret[3]) << "The fourth returned word is incorrect";
}

TEST(BitBufferTest, Shifts12BitWordsCorrectlyWithEvenValues) {
	BitBuffer bb1(12, 4, true);
	uint16_t word1 = 0xF321;
	uint16_t word2 = 0xF654;
	uint16_t word3 = 0xF987;
	uint16_t word4 = 0xFCBA;
	bb1.insert(word1);
	bb1.insert(word2);
	bb1.insert(word3);
	bb1.insert(word4);

	bb1.shift(2);
	ASSERT_EQ(2, bb1.wordsUsed) << "Doesn't store correct amount of bits after shifting";

	uint8_t ret[3];
	memcpy(ret, bb1.buffer, sizeof(uint8_t) * 3);
	EXPECT_EQ(0x87, bb1.buffer[0]) << "The first returned byte is incorrect";
	EXPECT_EQ(0xA9, bb1.buffer[1]) << "The second returned byte is incorrect";
	EXPECT_EQ(0xCB, bb1.buffer[2]) << "The third returned byte is incorrect";
}

TEST(BitBufferTest, Shifts12BitWordsCorrectlyWithUnevenValues) {
	BitBuffer bb1(12, 4, true);
	uint16_t word1 = 0xF321;
	uint16_t word2 = 0xF654;
	uint16_t word3 = 0xF987;
	uint16_t word4 = 0xFCBA;
	uint16_t word5 = 0xF10D;
	uint16_t word6 = 0xF432;

	// Fill the buffer with garbage first to test
	bb1.insert(word1);
	bb1.insert(word2);
	bb1.insert(word3);
	bb1.insert(word4);
	bb1.insert(word5);
	bb1.insert(word6);

	bb1.shift(1);
	ASSERT_EQ(5, bb1.wordsUsed)
		<< "Doesn't store correct amount of bits after shifting odd number";

	uint8_t ret[5];
	memcpy(ret, bb1.buffer, sizeof(uint8_t) * 5);
	EXPECT_EQ(0x54, bb1.buffer[0]) << "The first returned byte is incorrect";
	EXPECT_EQ(0x76, bb1.buffer[1]) << "The second returned byte is incorrect";
	EXPECT_EQ(0x98, bb1.buffer[2]) << "The third returned byte is incorrect";
	EXPECT_EQ(0xBA, bb1.buffer[3]) << "The fourth returned byte is incorrect";
	EXPECT_EQ(0xDC, bb1.buffer[4]) << "The fifth returned byte is incorrect";
	EXPECT_EQ(0x10, bb1.buffer[5]) << "The sixth returned byte is incorrect";
	EXPECT_EQ(0x32, bb1.buffer[6]) << "The seventh returned byte is incorrect";
	EXPECT_EQ(0x04, bb1.buffer[7]) << "The last returned byte is incorrect";

	bb1.shift(2);
	ASSERT_EQ(3, bb1.wordsUsed)
		<< "Doesn't store correct amount of bits after shifting even number";
	EXPECT_EQ(0xBA, bb1.buffer[0]) << "The first returned byte is incorrect";
	EXPECT_EQ(0xDC, bb1.buffer[1]) << "The second returned byte is incorrect";
	EXPECT_EQ(0x10, bb1.buffer[2]) << "The third returned byte is incorrect";
	EXPECT_EQ(0x32, bb1.buffer[3]) << "The fourth returned byte is incorrect";
	EXPECT_EQ(0x04, bb1.buffer[4]) << "The last returned byte is incorrect";
}

TEST(BitBufferTest, Shifts16BitWordsCorrectly) {
	BitBuffer bb1(16, 6, true);
	uint16_t word1 = 0xF321;
	uint16_t word2 = 0xF654;
	uint16_t word3 = 0xF987;
	uint16_t word4 = 0xBF23;
	uint16_t word5 = 0xECD1;
	uint16_t word6 = 0xFDBA;
	bb1.insert(word1);
	bb1.insert(word2);
	bb1.insert(word3);
	bb1.insert(word4);
	bb1.insert(word5);
	bb1.insert(word6);

	ASSERT_EQ(6, bb1.wordsUsed) << "Doesn't store correct amount of words before shifting";
	bb1.shift(3);
	ASSERT_EQ(3, bb1.wordsUsed) << "Doesn't store correct amount of words after shifting";
	EXPECT_EQ(0x23, bb1.buffer[0]);
	EXPECT_EQ(0xBF, bb1.buffer[1]);
	EXPECT_EQ(0xD1, bb1.buffer[2]);
	EXPECT_EQ(0xEC, bb1.buffer[3]);
	EXPECT_EQ(0xBA, bb1.buffer[4]);
	EXPECT_EQ(0xFD, bb1.buffer[5]);
}

TEST(BitBufferTest, GetFullArrayWorksWith12BitWords) {
	BitBuffer bb1(12, 6, true);
	uint16_t word1 = 0xF321;
	uint16_t word2 = 0xF654;
	uint16_t word3 = 0xF987;
	uint16_t word4 = 0xFF23;
	uint16_t word5 = 0xFCD1;
	uint16_t word6 = 0xFDBA;
	bb1.insert(word1);
	bb1.insert(word2);
	bb1.insert(word3);
	bb1.insert(word4);
	bb1.insert(word5);
	bb1.insert(word6);

	ASSERT_EQ(6, bb1.wordsUsed);
	uint16_t retArray[5];
	bb1.shift(1);
	unsigned int returnedElems = bb1.getFullArray(retArray);
	ASSERT_EQ(5, returnedElems) << "getFullArray doesn't return correct amount of elements";

	EXPECT_EQ(0x0654, retArray[0]);
	EXPECT_EQ(0x0987, retArray[1]);
	EXPECT_EQ(0x0F23, retArray[2]);
	EXPECT_EQ(0x0CD1, retArray[3]);
	EXPECT_EQ(0x0DBA, retArray[4]);

	bb1.shift(2);
	returnedElems = bb1.getFullArray(retArray);
	ASSERT_EQ(3, returnedElems) << "getFullArray doesn't return correct amount of elements";

	EXPECT_EQ(0x0F23, retArray[0]);
	EXPECT_EQ(0x0CD1, retArray[1]);
	EXPECT_EQ(0x0DBA, retArray[2]);
}

TEST(BitBufferTest, GetFullArrayWorksWith16BitWords) {
	BitBuffer bb1(16, 6, true);
	uint16_t word1 = 0xF321;
	uint16_t word2 = 0xF654;
	uint16_t word3 = 0xF987;
	uint16_t word4 = 0xBF23;
	uint16_t word5 = 0xECD1;
	uint16_t word6 = 0xFDBA;
	bb1.insert(word1);
	bb1.insert(word2);
	bb1.insert(word3);
	bb1.insert(word4);
	bb1.insert(word5);
	bb1.insert(word6);

	ASSERT_EQ(6, bb1.wordsUsed);
	uint16_t retArray[5];
	bb1.shift(1);
	unsigned int returnedElems = bb1.getFullArray(retArray);
	ASSERT_EQ(5, returnedElems) << "getFullArray doesn't return correct amount of elements";

	EXPECT_EQ(word2, retArray[0]);
	EXPECT_EQ(word3, retArray[1]);
	EXPECT_EQ(word4, retArray[2]);
	EXPECT_EQ(word5, retArray[3]);
	EXPECT_EQ(word6, retArray[4]);
}
