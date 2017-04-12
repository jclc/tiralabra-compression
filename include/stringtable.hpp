#ifndef STRINGTABLE_HPP
#define STRINGTABLE_HPP

#include <cstdint>
#include <sstream>

struct symbol_ll;

class StringTable {
public:
	StringTable(int p_maxSize, int stringLength);
	~StringTable();

	void clear();
	void insert(uint8_t symbol);

	std::stringstream lastStr;
	int lastStrLength;
	uint16_t maxSize;
	uint16_t lastSymbol;
	uint16_t* tbl_symbol;
//	uint16_t* tbl_previous;
	symbol_ll** tbl_symbol_ll;
};

#endif /* STRINGTABLE_HPP */
