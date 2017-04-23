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

	unsigned int maxBytes;
	if (bitSize == 12)
		maxBytes = BUFFER_SIZE*3/2;
	else
		maxBytes = BUFFER_SIZE*2;

	int bytesRead = -1;
	bool firstRun = true;

	if (progress)
		progress->setMessage("Decoding: ");

	uint16_t code;
	uint16_t str;
	char* entry;
	unsigned int len;

	while ((bytesRead = input.read(bb.buffer, maxBytes)) != 0) {
		if (progress) {
			progress->progress(
				100*((float)(input.getCurrentPos()-input.getReadStart())
					/(input.getReadEnd()-input.getReadStart())), 0);
		}

		bb.setBytesRead(bytesRead);
		unsigned int wordsUsed = bb.getFullArray(readBuffer);

		// This is needed inside the loop since we cannot read just one code
		// because the bitsize may be 12
		if (firstRun) {
			code = readBuffer[0];

			char* outStr = strTable.getDecodingString(code, &len);
			output.write(outStr, 1);
		}

		for (int i = 0 + (firstRun ? 1 : 0); i < wordsUsed; ++i) {
			code = readBuffer[i];
			if (!strTable.hasEntry(code)) {
				// Deal with the special circumstance where the read code is not
				// in the string table
				printf("uh oh!\n");
				continue;

			} else {
				entry = strTable.getDecodingString(code, &len);
				if (code < 256)
					printf("%d -> %d\n", code, len);
			}
			output.write(entry, len);
		}
		bb.shift(wordsUsed);
		firstRun = false;
	}

	return;
}
