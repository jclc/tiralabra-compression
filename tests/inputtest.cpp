#include <gtest/gtest.h>
#include "testoutput.hpp"
#include "input.hpp"
#include <unistd.h>

TEST(InputTestSuite, InputTest_OpenFile) {
	Input in1;
	std::string filepath = "lorem_ipsum_eng.txt";
	bool openSuccess = in1.openFile(filepath);
	ASSERT_TRUE(openSuccess) << "Failed to open file 'lorem_ipsum_eng.txt'";
	TestOutput out1;
}
