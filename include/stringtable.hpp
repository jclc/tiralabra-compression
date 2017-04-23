#ifndef STRINGTABLE_HPP
#define STRINGTABLE_HPP

#include <cstdint>
#include <cstring>
//#include <sstream>

struct symbol_ll;

class StringTable {
public:
	/**
	 * @brief StringTable constructor
	 * @param p_maxSize Number of elements the table can hold
	 * @param encode True if encoding, false if decoding
	 */
	StringTable(int p_maxSize, bool p_encode);
	~StringTable();

	/// Empty the table
	void clearTable();

	/// Insert a symbol in the table after string entry
	void insertEncodingSymbol(uint16_t str, uint8_t sym);

	void insertDecodingSymbol(uint16_t code, uint8_t sym);

	/// Returns true if the entry is in the table
	bool hasEntry(uint16_t entry);

	/// Whether the string + symbol exists in the table
	uint16_t getNextEncodingEntry(uint16_t str, uint8_t sym);

	/// Get the next entry in the table
	char* getDecodingString(uint16_t code);

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
	void newLink(uint16_t str, uint16_t target);

	/// Whether or not to be used for encoding
	bool encode;

	char* returnString;
	unsigned int stringBufferSize;
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

	/// Symbol to point to
	uint16_t targetSymbol;
	/// Next link in the linked list
	symbol_ll* nextLink;
};

inline StringTable::StringTable(int p_maxSize, bool p_encode) {
	maxSymbols = p_maxSize;
	tbl_symbol = (uint8_t*) malloc(sizeof(uint8_t) * maxSymbols);
	for (int i = 0; i < 256; ++i)
		tbl_symbol[i] = i;

	tbl_symbol_ll = (symbol_ll**) malloc(sizeof(symbol_ll*) * maxSymbols);
	for (int i = 0; i < maxSymbols; ++i)
		tbl_symbol_ll[i] = nullptr;

	lastSymbol = 255;
	if (p_encode) {
		encode = true;
		returnString = nullptr;
	} else {
		stringBufferSize = 256;
		returnString = (char*) malloc(sizeof(char) * stringBufferSize);
	}
}

inline StringTable::~StringTable() {
	clearTable();
	free(tbl_symbol);
	if (returnString)
		free(returnString);
}

inline void StringTable::insertEncodingSymbol(uint16_t str, uint8_t sym) {
	tbl_symbol[++lastSymbol] = sym;
	newLink(str, lastSymbol);
}

inline uint16_t StringTable::getNextEncodingEntry(uint16_t str, uint8_t sym) {
	symbol_ll* link = tbl_symbol_ll[str];
	if (link == nullptr)
		return 0;

	// Go through elements in the linked list
	while (link != nullptr) {
		if (sym == tbl_symbol[link->targetSymbol])
			return link->targetSymbol;
		link = link->nextLink;
	}
	return 0;
}

inline char* StringTable::getDecodingString(uint16_t code) {
	uint16_t sym = code;
	int i = stringBufferSize - 1; // Fill the string starting from the end
	returnString[i--] = '\0';
	while (true) {
		if (i < 0) {
			char* temp = (char*) malloc(sizeof(char*) * stringBufferSize * 2);
			memcpy(temp + stringBufferSize, returnString, sizeof(char) * stringBufferSize);
			free(returnString);
			returnString = temp;
			i += stringBufferSize;
			stringBufferSize *= 2;
		}

		returnString[stringBufferSize + i] = tbl_symbol[sym];

		if (tbl_symbol_ll[sym] == nullptr)
			break;

		sym = tbl_symbol_ll[sym]->targetSymbol;

		--i;
	}

	return returnString + i;
}

inline bool StringTable::hasEntry(uint16_t entry) {
	return (entry > lastSymbol);
}

inline bool StringTable::isFull() {
	return lastSymbol >= maxSymbols;
}

inline void StringTable::newLink(uint16_t str, uint16_t target) {
	symbol_ll* newLink = new symbol_ll();
	newLink->targetSymbol = target;

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
			tbl_symbol_ll[i] = nullptr;
		}
	}

	lastSymbol = 255;
}


#endif /* STRINGTABLE_HPP */
