#include "progressbar.hpp"
#include <iostream>
#include <cstdio>
#include <chrono>

ProgressBar::ProgressBar(int p_threads) {
	length = 78;
	started = false;
	kill = false;
	threads = p_threads;
	status = (std::atomic<int>*) malloc(sizeof(std::atomic<int>) * threads);
	for (int i = 0; i < threads; ++i)
		status[i] = 0;
	printingThread = nullptr;
	message = "";
}

ProgressBar::~ProgressBar() {
	if (printingThread) {

	}
		delete printingThread;
}

void ProgressBar::start() {
	printingThread = new std::thread([this]() -> void {
		while (!kill) {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			int progress = 0;
			for (int i = 0; i < threads; ++i)
				progress += status[i];
			progress /= threads;
			std::cout << "\r" << message << progress << "%" << std::flush;
		}
		std::cout << "\r" << message << "100%" << std::endl;
	});
}

void ProgressBar::stop() {
	kill = true;
	printingThread->join();
}

void ProgressBar::setMessage(std::string msg) {
	message = msg;
}

void ProgressBar::progress(int amount, int thread) {
	status[thread] = amount;
}
