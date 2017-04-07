#include "stringtable.hpp"
#include <cstdlib>

StringTable::StringTable(int maxSize, int stringLength) {
	tbl_symbol = (uint16_t*) malloc(sizeof(uint16_t) * maxSize);
	for (int i = 0; i < 256; ++i)
		tbl_symbol[i] = i;

	clear();
}

StringTable::~StringTable() {
	free(tbl_symbol);
//	free(tbl_previous);
}

void StringTable::clear() {

}
