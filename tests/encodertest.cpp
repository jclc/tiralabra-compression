#include <gtest/gtest.h>
#include <memory>
#include "encoder.hpp"
#include "testoutput.hpp"
#include "input.hpp"
#include <cstdio>

TEST(EncoderTest, BasicFileWithHeader) {
	Input in;
	ASSERT_TRUE(in.openFile("numbers.txt")) << "Couldn't open numbers.txt";
	std::shared_ptr<Output> out = std::shared_ptr<Output>(new TestOutput());
	try {
		encoder::encode(in, *out, 16, true);
	} catch (std::exception e) {
		ASSERT_FALSE(1) << e.what();
	}

	// Expected size: 8 bytes for start header
	// 10 * 2 = 20 bytes for the "compressed" content
	// 24 bytes for the end header
	int expectedSize = 8 + 20 + 24;
	std::shared_ptr<TestOutput> testout = std::dynamic_pointer_cast<TestOutput>(out);
	int charCount = testout->getOutputCharCount();
	EXPECT_EQ(expectedSize, charCount);

	for (int i = 0; i < 8 && i < charCount; ++i) {
		EXPECT_EQ(magicNumbers[i], testout->getOutput()[i])
			<< "Magic numbers differ at " << i;
	}
}
