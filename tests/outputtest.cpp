#include <gtest/gtest.h>
#include "output.hpp"
#include <cstdio>
#include <string>
#include <exception>
#include <thread>

class OutputTest: public ::testing::Test {
public:
	std::string tempFileName1;

protected:
	virtual void SetUp() {
#ifdef __unix__
		char tmpnamBuffer[256];
		strcpy(tmpnamBuffer, "/tmp/tiralabra-compression-temp-XXXXXX");
		mkstemp(tmpnamBuffer);
		tempFileName1 = tmpnamBuffer;
#else
		char tmpnamBuffer[L_tmpnam];
		tmpnam(tmpnamBuffer);
		tempFileName1 = tmpnamBuffer;
#endif
	}

	virtual void TearDown() {
		FILE* tmpFile;
		tmpFile = fopen(tempFileName1.c_str(), "w");
		if (tmpFile) {
			fclose(tmpFile);
			remove(tempFileName1.c_str());
		}
	}
};

TEST_F(OutputTest, WritingToFile) {
	Output* out1 = new FileOutput;
	bool success = out1->openFile(tempFileName1);
	ASSERT_TRUE(success) << "FileOutput couldn't open file " << tempFileName1;
	const char* data = "ASDFGHJKL";
	out1->write(data, 9UL);
	delete out1;

	FILE* file1 = fopen(tempFileName1.c_str(), "r");
	ASSERT_TRUE(file1 != NULL) << "File created couldn't be opened: " << tempFileName1;

	char readBuffer[16] = "";
	size_t readSize = fread(readBuffer, sizeof(char), 16, file1);
	EXPECT_EQ(strlen(data), readSize) << "Created file is the wrong size: " << tempFileName1;

	char readStr[10] = "";
	strncpy(readStr, readBuffer, sizeof(char) * 9);
	EXPECT_STREQ(data, readStr) << "Written content doesn't match";
}

TEST_F(OutputTest, WritingToStream) {
	Output* out1 = new StreamOutput;
	testing::internal::CaptureStdout();
	std::string dataString = "QWERTYUIOP";
	out1->write(dataString.c_str(), dataString.length());
	delete out1;
	std::string capture = testing::internal::GetCapturedStdout();
	EXPECT_STREQ(dataString.c_str(), capture.c_str()) << "Stream output did not match with data";
}

TEST_F(OutputTest, WritingToEndlessBitVoid) {
	Output* out1 = new NullOutput;
	testing::internal::CaptureStdout();
	std::string dataString = "When you gaze long into an abyss the abyss also gazes into you.";
	out1->write(dataString.c_str(), dataString.size());
	delete out1;
	std::string capture = testing::internal::GetCapturedStdout();
	EXPECT_STREQ("", capture.c_str()) << "NullOutput printed to stdout";
}
