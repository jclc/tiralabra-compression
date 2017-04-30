#include <gtest/gtest.h>
#include <cstdio>
#include <cstdint>
#include "input.hpp"
#include "output.hpp"
#include "testoutput.hpp"
#include "encoder.hpp"
#include "decoder.hpp"
#include "bitbuffer.hpp"
#include "tempfilenames.hpp"

class IntegrationTest: public ::testing::Test {
public:
	std::string tempFileName1;
	std::string tempFileName2;
	std::string tempFileName3;

protected:
	virtual void SetUp() {
		tempFileName1 = getTempFileName();
		tempFileName2 = getTempFileName();
		tempFileName3 = getTempFileName();
	}

	virtual void TearDown() {
		FILE* fp;
		if (fp = fopen(tempFileName1.c_str(), "r")) {
			fclose(fp);
			remove(tempFileName1.c_str());
		}
		if (fp = fopen(tempFileName2.c_str(), "r")) {
			fclose(fp);
			remove(tempFileName2.c_str());
		}
		if (fp = fopen(tempFileName3.c_str(), "r")) {
			fclose(fp);
			remove(tempFileName3.c_str());
		}
	}
};

TEST_F(IntegrationTest, EncodesFile) {
//	std::string file = getTempFileName();
	Input input1;
	bool success = input1.openFile("simple.txt");
	ASSERT_TRUE(success) << "Couldn't open file \"simple.txt\"";

	FileOutput* output1 = new FileOutput;
	success = output1->openFile(tempFileName1);
	ASSERT_TRUE(success) << "Couldn't open temp file \"" << tempFileName1 << "\"";

	Encoder encoder;
	encoder.encode(input1, *output1, 12, nullptr);
	delete output1;

	FILE* fp = fopen(tempFileName1.c_str(), "r");
	ASSERT_TRUE(fp != nullptr) << "Couldn't open encoded file \"" << tempFileName1 << "\"";

	uint16_t expected[] = {
		'a', 'b', 'c', 256, 258, 257, 259, 262, 261, 264, 260, 266, 263, 'c'
	};
	BitBuffer bb(12, 64, false);
	fseek(fp, 8, SEEK_SET);
	unsigned int read = fread(bb.buffer, sizeof(char), 21, fp);
	bb.setBytesRead(read);
	EXPECT_EQ(21, read);

	uint16_t received[64];
	unsigned int wordsRead = bb.getFullArray(received);

	EXPECT_EQ(14, wordsRead) << "Encoded file is the wrong size";

	for (int i = 0; i < wordsRead && i < 14; ++i) {
		EXPECT_EQ(expected[i], received[i]);
	}
}

TEST_F(IntegrationTest, DecodesFile) {
	Input* input1 = new Input;
	input1->openFile("simple.txt");
	FileOutput* output1 = new FileOutput;
	output1->openFile(tempFileName2);
	Encoder encoder;
	encoder.encode(*input1, *output1, 12, nullptr);
	delete input1;
	delete output1;

	Input* input2 = new Input;
	bool success = input2->openFile(tempFileName2);
	ASSERT_TRUE(success) << "Couldn't open file \"" << tempFileName2 << "\"";
	input2->setBounds(8, input2->getFileSize()-24);

	Decoder decoder;
	FileOutput* output2 = new FileOutput;
	success = output2->openFile(tempFileName3);
	ASSERT_TRUE(success) << "Couldn't open file \"" << tempFileName3 << "\"";
	decoder.decode(*input2, *output2, nullptr);
	delete input2;
	delete output2;

	FILE* org = fopen("simple.txt", "r");
	FILE* dec = fopen(tempFileName3.c_str(), "r");
	ASSERT_TRUE(org != nullptr);
	ASSERT_TRUE(dec != nullptr);
	uint8_t original[64];
	uint8_t decoded[64];
	unsigned int originalSize = fread(original, sizeof(uint8_t), 64, org);
	unsigned int decodedSize = fread(decoded, sizeof(uint8_t), 64, dec);
	EXPECT_EQ(originalSize, decodedSize) << "Decoded file size doesn't match original";
	for (int i = 0; i < originalSize && i < decodedSize; ++i) {
		EXPECT_EQ(original[i], decoded[i]) << "Decoded file differs at index " << i;
	}
	fclose(org);
	fclose(dec);
}
