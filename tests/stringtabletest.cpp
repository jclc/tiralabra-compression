#include "stringtable.hpp"
#include <gtest/gtest.h>
#include <cmath>

TEST(StringTableTest, EncodingSymbols) {
	int bitSize = 12;
	int maxEntries = std::pow(2, bitSize) - 1;
	StringTable strTbl(maxEntries, true);
	ASSERT_EQ(255, strTbl.lastSymbol) << "Incorrect amount of entries after initialisation";

	uint16_t entry = strTbl.getNextEncodingEntry((int) 'a', 'b');
	ASSERT_EQ(0, entry) << "Doesn't return zero when searching for a nonexistent entry";

	strTbl.insertEncodingSymbol((int) 'a', 'b');
	ASSERT_EQ(256, strTbl.lastSymbol) << "Doesn't increment symbolcount after insertion";
	entry = strTbl.getNextEncodingEntry((int) 'a', 'b');
	EXPECT_EQ(256, entry) << "Doesn't return the first new entry";
	strTbl.insertEncodingSymbol(entry, 'c');
	entry = strTbl.getNextEncodingEntry(entry, 'c');
	EXPECT_EQ(257, entry) << "Doesn't return the second new entry";

	strTbl.insertEncodingSymbol(256, 'x');
	entry = strTbl.getNextEncodingEntry(256, 'x');
	EXPECT_EQ(258, entry) << "Doesn't return the third new entry";
}

TEST(StringTableTest, ClearingTable) {
	int bitSize = 12;
	int maxEntries = std::pow(2, bitSize) - 1;
	StringTable strTbl(maxEntries, true);
	ASSERT_EQ(255, strTbl.lastSymbol) << "Incorrect amount of entries after initialisation";

	strTbl.insertEncodingSymbol((int) 'a', 'b');
	strTbl.insertEncodingSymbol(256, 'c');
	strTbl.insertEncodingSymbol(257, 'd');
	ASSERT_EQ(258, strTbl.lastSymbol) << "Incorrect amount of entries after insertion";

	strTbl.clearTable();
	ASSERT_EQ(255, strTbl.lastSymbol) << "Incorrect amount of entries after clearing";
	ASSERT_EQ(0, strTbl.getNextEncodingEntry((int) 'a', 'b'))
		<< "Didn't delete reference to new entry";
	ASSERT_EQ(0, strTbl.getNextEncodingEntry(256, 'c'))
		<< "Didn't delete reference to new entry outside initial entry list";
}

TEST(StringTableTest, DecodingSymbols) {
	int bitSize = 12;
	int maxEntries = std::pow(2, bitSize) - 1;
	StringTable strTbl(maxEntries, false);
	ASSERT_EQ(255, strTbl.lastSymbol) << "Incorrect amount of entries after initialisation";
	char* str;
	unsigned int len;
	str = strTbl.getDecodingString((int) 'z', &len);
	ASSERT_EQ(1, len) << "Returns wrong length for decoding string with a single byte input";
	EXPECT_EQ('z', str[0]) << "Doesn't return correct string with single byte input";

	strTbl.insertDecodingSymbol((int) 'a', 'b');
	ASSERT_EQ(256, strTbl.lastSymbol) << "Incorrect amount of entries after insertion";
	strTbl.insertDecodingSymbol(256, 'c');

	str = strTbl.getDecodingString(257, &len);
	ASSERT_EQ(3, len) << "Returns wrong length for string after 2 inserts";
	EXPECT_EQ('a', str[0]) << "Doesn't return correct string after 2 inserts";
	EXPECT_EQ('b', str[1]) << "Doesn't return correct string after 2 inserts";
	EXPECT_EQ('c', str[2]) << "Doesn't return correct string after 2 inserts";
}

TEST(StringTableTest, CheckingForSymbols) {
	int bitSize = 12;
	int maxEntries = std::pow(2, bitSize) - 1;
	StringTable strTbl(maxEntries, true);

	EXPECT_FALSE(strTbl.hasEntry(256)) << "Empty table reports having an entry";
	EXPECT_FALSE(strTbl.hasEntry(257)) << "Empty table reports having an entry";
	strTbl.insertEncodingSymbol('m', 'n');
	EXPECT_TRUE(strTbl.hasEntry(256)) << "Doesn't report having an entry after insertion";
	EXPECT_FALSE(strTbl.hasEntry(257)) << "Reports having more than one entry after insertion";
}
