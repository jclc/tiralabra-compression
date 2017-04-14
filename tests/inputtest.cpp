#include <gtest/gtest.h>
#include "testoutput.hpp"
#include "input.hpp"

TEST(InputTest, OpenFile) {
	Input in;
	bool openSuccess = in.openFile("lorem_ipsum_eng.txt");
	ASSERT_TRUE(openSuccess) << "Failed to open file lorem_ipsum_eng.txt";
}

TEST(InputTest, RecogniseUncompressedFile) {
	Input in;
	bool openSuccess = in.openFile("ebook.txt");
	ASSERT_TRUE(openSuccess) << "Failed to open file ebook.txt";
	EXPECT_EQ(COMPRESS, in.getOpMode()) << "Failed to assign opmode for ebook.txt";
	EXPECT_EQ(338791UL, in.getFileSize()) << "Incorrect file size";
}

TEST(InputTest, RecogniseCompressedFile) {
	Input in;
	std::string filepath = "fake_compressed_file.bin";
	bool openSuccess = in.openFile(filepath);
	ASSERT_TRUE(openSuccess) << "Failed to open file " << filepath;
	EXPECT_EQ(DECOMPRESS, in.getOpMode())
		<< "Failed to assign opmode for fake_compressed_file.bin";
	EXPECT_EQ(16, (int) in.getBitSize()) << "Incorrect bit size";
	EXPECT_EQ(256UL, in.getOriginalSize()) << "Incorrect original size";
	EXPECT_EQ(279UL, in.getFileSize()) << "Incorrect file size";
}

TEST(InputTest, ReadingWorks) {
	Input in;
	std::string filepath = "numbers.txt";
	bool openSuccess = in.openFile(filepath);
	ASSERT_TRUE(openSuccess) << "Failed to open file " << filepath;
	uint8_t buffer[20];
	int returned = in.read(buffer, 20);
	EXPECT_EQ(10, returned) << "Didn't read correct amount of bytes";
	buffer[10] = '\0';
	EXPECT_STREQ("0123456789", (char*) buffer);
}

TEST(InputTest, ReadingWithBoundsWorks) {
	Input in;
	std::string filepath = "ebook.txt";
	bool openSuccess = in.openFile(filepath);
	ASSERT_TRUE(openSuccess) << "Failed to open file " << filepath;
	// There are 3 magic numbers at the start of the file which we have to account for
	in.setBounds(15, 24);
	uint8_t buffer[20];
	int returned = in.read(buffer, 20);
	EXPECT_EQ(9, returned) << "Didn't read correct amount of bytes";
	buffer[10] = '\0';
	EXPECT_STREQ("Gutenberg", (char*) buffer);
}
