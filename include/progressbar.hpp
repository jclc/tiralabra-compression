#ifndef PROGRESSBAR_HPP
#define PROGRESSBAR_HPP

#include <string>
#include <atomic>
#include <thread>

class ProgressBar {
public:
	ProgressBar(int threads);
	~ProgressBar();

	void start();
	void stop();
	void setMessage(std::string msg);

	/**
	 * @brief Increase progress bar
	 * @param amount Percentage of progress (0.0 to 1.0)
	 * @param thread ID of thread of execution (for future multithreading support)
	 */
	void progress(int amount, int thread);

private:
	int length;
	int interval;
	int threads;
	std::atomic<int>* status;
	std::string message;
	bool started;
	bool kill;
	std::thread* printingThread;
};

#endif /* PROGRESSBAR_HPP */
