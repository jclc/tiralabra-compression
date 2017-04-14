#ifndef STRINGTABLE_HPP
#define STRINGTABLE_HPP

#include <cstdint>
//#include <sstream>

struct symbol_ll;

class StringTable {
public:
	StringTable(int p_maxSize);
	~StringTable();

	/// Empty the table
	void clearTable();
	/// Insert a symbol in the table after string entry
	void insert(uint16_t str, uint8_t sym);
	/// Whether the string + symbol exists in the table
	uint16_t getNextEntry(uint16_t str, uint8_t sym);
	/// Get the next entry in the table
	uint16_t getNext(uint16_t str, uint8_t sym);
	/// Whether the table has reached its limit
	bool isFull();

	/// The very last symbol in the table
	uint16_t lastSymbol;
	/// How many symbols fit in the table
	uint16_t maxSymbols;

private:
	/// Table with symbol values
	uint8_t* tbl_symbol;
	/// Array of linked lists for each table entry pointing to other entries that follow
	symbol_ll** tbl_symbol_ll;
	/// Create a new link pointing from entry str to entry sym
	void newLink(uint16_t str, uint16_t next);
};

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

StringTable::StringTable(int p_maxSize) {
	maxSymbols = p_maxSize;
	tbl_symbol = (uint8_t*) malloc(sizeof(uint8_t) * maxSymbols);
	for (int i = 0; i < 256; ++i)
		tbl_symbol[i] = i;

	tbl_symbol_ll = (symbol_ll**) malloc(sizeof(symbol_ll*) * maxSymbols);
	for (int i = 0; i < maxSymbols; ++i)
		tbl_symbol_ll[i] = nullptr;

	lastSymbol = 255;
}

StringTable::~StringTable() {
	clearTable();
	free(tbl_symbol);
}

inline void StringTable::insert(uint16_t str, uint8_t sym) {
	tbl_symbol[++lastSymbol] = sym;
	newLink(str, lastSymbol);
}

inline uint16_t StringTable::getNextEntry(uint16_t str, uint8_t sym) {
	symbol_ll* link = tbl_symbol_ll[str];
	if (link == nullptr)
		return 0;

	// Go through elements in the linked list
	while (link != nullptr) {
		if (sym == tbl_symbol[link->nextSymbol])
			return link->nextSymbol;
		link = link->nextLink;
	}
	return 0;
}

inline bool StringTable::isFull() {
	return lastSymbol >= maxSymbols;
}

inline void StringTable::newLink(uint16_t str, uint16_t next) {
	symbol_ll* newLink = new symbol_ll();
	newLink->nextSymbol = next;

	symbol_ll* lastInChain = tbl_symbol_ll[str];
	if (lastInChain == nullptr) {
		tbl_symbol_ll[str] = newLink;
		return;
	}

	if (lastInChain != nullptr) {
		while (lastInChain->nextLink != nullptr)
			lastInChain = lastInChain->nextLink;
	}

	lastInChain->nextLink = newLink;
}

inline void StringTable::clearTable() {

	for (int i = 0; i < maxSymbols; ++i) {
		if (tbl_symbol_ll[i]) {
			delete tbl_symbol_ll[i];
		}
	}

	lastSymbol = 255;
}


#endif /* STRINGTABLE_HPP */
