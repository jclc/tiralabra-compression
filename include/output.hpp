#include <string>

class Output {
public:
	virtual bool openFile(std::string& fileName) {}
	virtual void write(const char* data, int bufferSize) = 0;
};

class FileOutput: public Output {
public:
	FileOutput();
	bool openFile(std::string& fileName);
	void write(const char *data, int bufferSize);
};

class StdOutput: public Output {
public:
	StdOutput();
	void write(const char *data, int bufferSize);
};
