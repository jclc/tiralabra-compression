#ifndef STRINGTABLE_HPP
#define STRINGTABLE_HPP

#include <cstdint>

class StringTable {
public:
	StringTable(int maxSize, int stringLength);
	~StringTable();

	void clear();
//	bool isIn

	char* lastStr;
	int lastStrLength;
	int lastEntry;
	uint16_t* tbl_symbol;
	uint16_t* tbl_previous;
	uint16_t** tbl_possibleNext;
};

#endif /* STRINGTABLE_HPP */
