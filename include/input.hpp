#include <string>
#include "output.hpp"

class Input {
public:
	Input();
	bool openFile(std::string& fileName);
	void compress(Output& out);
private:

};
