#include <gtest/gtest.h>
#include "output.hpp"
#include <cstdio>
#include <string>
#include <exception>

class OutputTest: public ::testing::Test {
public:
	std::string tempFileName1;
	std::string tempFileName2;

protected:
	virtual void SetUp() {
#ifdef __unix__
		char tmpnamBuffer[256];
		strcpy(tmpnamBuffer, "/tmp/tiralabra-compression-temp-XXXXXX");
		mkstemp(tmpnamBuffer);
		tempFileName1 = tmpnamBuffer;
		strcpy(tmpnamBuffer, "/tmp/tiralabra-compression-temp-XXXXXX");
		mkstemp(tmpnamBuffer);
		tempFileName2 = tmpnamBuffer;
#else
		char tmpnamBuffer[L_tmpnam];
		tmpnam(tmpnamBuffer);
		tempFileName1 = tmpnamBuffer;
		tmpnam(tmpnamBuffer);
		tempFileName2 = tmpnamBuffer;
#endif
	}

	virtual void TearDown() {
		FILE* tmpFile;
		tmpFile = fopen(tempFileName1.c_str(), "w");
		if (tmpFile) {
			fclose(tmpFile);
			remove(tempFileName1.c_str());
		}
		tmpFile = fopen(tempFileName2.c_str(), "w");
		if (tmpFile) {
			fclose(tmpFile);
			remove(tempFileName2.c_str());
		}
	}
};

TEST_F(OutputTest, OutputTest_WritingToFile) {
	FileOutput* out1 = new FileOutput;
	out1->openFile(tempFileName1);
	const char* data = "ASDFGHJKL";
	out1->write(data, 9UL);
	delete out1;

	FILE* file1 = fopen(tempFileName1.c_str(), "r");
	ASSERT_TRUE(file1 != NULL) << "File created couldn't be opened: " << tempFileName1;

	char readBuffer[16];
	size_t readSize = fread(readBuffer, sizeof(char), 16, file1);
	EXPECT_EQ(strlen(data), readSize) << "Created file is the wrong size: " << tempFileName1;
	char readStr[10];
	for (int i = 0; i < 10; ++i)
		readStr[i] = '\0';
	strncpy(readStr, readBuffer, sizeof(char) * 9);
	EXPECT_STREQ(data, readStr) << "Written content doesn't match";
}
