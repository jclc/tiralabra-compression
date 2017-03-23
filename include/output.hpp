#include <string>

class Output {
public:
	virtual bool openFile(std::string& fileName);
	virtual void write(const char* data, int buffer);
};
