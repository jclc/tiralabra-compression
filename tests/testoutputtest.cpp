#include <gtest/gtest.h>
#include "testoutput.hpp"
#include <cstring>

TEST(TestOutput, TestOutput_Basic) {
	TestOutput to1;
	const char* test_str1 = "hello, this is a test string";
	to1.write(test_str1, strlen(test_str1));

	ASSERT_EQ(strlen(test_str1), to1.getOutputCharCount())
		<< "TestOutput returns wrong char count for test string";
	char ret[32];
	strncpy(ret, to1.getOutput(), strlen(test_str1));
	EXPECT_STREQ(test_str1, ret)
		<< "TestOutput doesn't return the test string";

	TestOutput to2;
	char test_chararray[2000];

	for (int i = 0; i < 2000; ++i) {
		test_chararray[i] = i % 256;
	}
	to2.write(test_chararray, 2000);

	ASSERT_EQ(2000, to2.getOutputCharCount())
		<< "TestOutput returns wrong char count for test array";
	const char* out_chararray = to2.getOutput();
	for (int i = 0; i < 2000; i += 13) {
		ASSERT_EQ((char) (i % 256), out_chararray[i])
			<< "TestOutput stores the wrong char at index " << i;
	}
}
