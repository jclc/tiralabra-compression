#include <gtest/gtest.h>
#include "testoutput.hpp"
#include "input.hpp"

TEST(InputTest, OpenFile) {
	Input in1;
	bool openSuccess = in1.openFile("lorem_ipsum_eng.txt");
	ASSERT_TRUE(openSuccess) << "Failed to open file lorem_ipsum_eng.txt";
	TestOutput out1;
}

TEST(InputTest, RecogniseUncompressedFile) {
	Input in1;
	bool openSuccess = in1.openFile("ebook.txt");
	ASSERT_TRUE(openSuccess) << "Failed to open file ebook.txt";
	EXPECT_EQ(COMPRESS, in1.getOpMode()) << "Failed to assign opmode for ebook.txt";
	EXPECT_EQ(338791UL, in1.getFileSize()) << "Incorrect file size";
}

TEST(InputTest, RecogniseCompressedFile) {
	Input in1;
	std::string filepath1 = "fake_compressed_file.bin";
	bool openSuccess = in1.openFile("fake_compressed_file.bin");
	ASSERT_TRUE(openSuccess) << "Failed to open file " << filepath1;
	EXPECT_EQ(DECOMPRESS, in1.getOpMode())
		<< "Failed to assign opmode for fake_compressed_file.bin";
	EXPECT_EQ(16, ( int ) in1.getBitSize()) << "Incorrect bit size";
	EXPECT_EQ(256UL, in1.getOriginalSize()) << "Incorrect original size";
	EXPECT_EQ(8UL, in1.getDataSegmentLoc()) << "Incorrect data segment location";
	EXPECT_EQ(64UL, in1.getDictionaryLoc()) << "Incorrect dictionary location";
	EXPECT_EQ(279UL,     in1.getFileSize()) << "Incorrect file size";
}
