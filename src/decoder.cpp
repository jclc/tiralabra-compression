#include "input.hpp"
#include "decoder.hpp"
#include "bitbuffer.hpp"
#include "stringtable.hpp"
#include <cmath>
#include <cstring>
#include <cstdlib>

void decoder::decode(Input& input, Output& output,
	std::shared_ptr<ProgressBar> progress) {

	unsigned int bitSize = input.getBitSize();
	unsigned int maxEntries = std::pow(2, bitSize) - 1;
	StringTable strTable(maxEntries, false);
	uint16_t readBuffer[BUFFER_SIZE];
	BitBuffer bb(bitSize, BUFFER_SIZE, true);

	if (bitSize != MIN_BIT_SIZE && bitSize != MAX_BIT_SIZE)
		throw std::runtime_error("Invalid bit size");

	uint16_t clearTableSignal;
	unsigned int maxBytes;
	if (bitSize == 12) {
		maxBytes = BUFFER_SIZE*3/2;
		clearTableSignal = 0x0FFF;
	} else {
		maxBytes = BUFFER_SIZE*2;
		clearTableSignal = 0xFFFF;
	}

	int bytesRead = -1;
	bool firstRun = true;

	if (progress)
		progress->setMessage("Decoding: ");

	uint16_t code;
	uint16_t str;
	char* strPtr;
	unsigned int len;
	bool specialOccurred = false; // mark as true after the special case has occurred
	char special; // When encountering the special case, append

//	char tmpout[1024];

	while ((bytesRead = input.read(bb.buffer, maxBytes)) != 0) {
		if (progress) {
			progress->progress(
				100*((float)(input.getCurrentPos()-input.getReadStart())
					/(input.getReadEnd()-input.getReadStart())), 0);
		}


		bb.setBytesRead(bytesRead);
		unsigned int wordsUsed = bb.getFullArray(readBuffer);

		for (int i = 0; i < wordsUsed; ++i) {

			if (readBuffer[i] == clearTableSignal) {
				// Clear table if we reach the signal
				firstRun = true;
				strTable.clearTable();
				continue;
			}\
			if (firstRun) {
				// This is needed inside the loop since we cannot read just one code
				// because the bitsize may be 12
				code = readBuffer[i];

				strPtr = strTable.getDecodingString(code, &len);
				output.write(strPtr, 1);
				str = code;
				firstRun = false;
			} else {

				code = readBuffer[i];
				if (!strTable.hasEntry(code)) {
					// Deal with the special circumstance where the read code is not
					// in the string table
					strPtr = strTable.getDecodingString(str, &len);
					str = strTable.insertDecodingSymbol(str, strPtr[0]);
					strPtr = strTable.getDecodingString(str, &len);
					output.write(strPtr, len);
				} else {
					// When the code is in the table
					strPtr = strTable.getDecodingString(code, &len);
					output.write(strPtr, len);
					strTable.insertDecodingSymbol(str, strPtr[0]);
					str = code;
				}
			}
		}
		bb.shift(wordsUsed);
	}

	return;
}
