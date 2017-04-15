#ifndef PROGRESSBAR_HPP
#define PROGRESSBAR_HPP

#include <string>
#include <mutex>
#include <thread>

class ProgressBar {
public:
	ProgressBar(int threads);
	~ProgressBar();

	void start();
	void stop();

	/**
	 * @brief Post a status message
	 * @param msg Status message
	 */
	void message(std::string msg);

	/**
	 * @brief Increase progress bar
	 * @param amount Percentage of progress (0.0 to 1.0)
	 * @param thread ID of thread of execution (for future multithreading support)
	 */
	void progress(float amount, int thread);

private:
	int length;
	int interval;
	int threads;
	float* status;
	std::mutex lock;
	bool started;
	std::thread* printingThread;
};

#endif /* PROGRESSBAR_HPP */
