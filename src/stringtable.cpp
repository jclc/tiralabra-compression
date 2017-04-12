#include "stringtable.hpp"
#include <cstdlib>

/**
 * @brief Linked list for entries that follow a symbol, forming a string
 */
struct symbol_ll {
	symbol_ll() {
		nextLink = nullptr;
	}
	~symbol_ll() {
		if (nextLink)
			delete nextLink;
	}

	uint16_t nextSymbol;
	symbol_ll* nextLink;
};

StringTable::StringTable(int p_maxSize, int stringLength) {
	maxSize = p_maxSize;
	tbl_symbol = (uint16_t*) malloc(sizeof(uint16_t) * maxSize);
	for (int i = 0; i < 256; ++i)
		tbl_symbol[i] = i;

	tbl_symbol_ll = (symbol_ll**) malloc(sizeof(symbol_ll*) * maxSize);
	for (int i = 0; i < maxSize; ++i)
		tbl_symbol_ll[i] = nullptr;

	lastSymbol = 255;
}

StringTable::~StringTable() {
	free(tbl_symbol);
//	free(tbl_previous);
}

void StringTable::insert(uint8_t symbol) {
	lastStr << symbol;
}

void StringTable::clear() {

	for (int i = 0; i < maxSize; ++i)
		if (tbl_symbol_ll[i])
			delete tbl_symbol_ll[i];

	lastSymbol = 255;
}
