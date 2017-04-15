#include "progressbar.hpp"
#include <iostream>
#include <cstdio>

ProgressBar::ProgressBar(int p_threads) {
	length = 78;
	started = false;
	threads = p_threads;
	status = (float*) malloc(sizeof(float) * threads);
	for (int i = 0; i < threads; ++i)
		status[i] = 0.0F;
}

ProgressBar::~ProgressBar() {
}

void ProgressBar::start() {
	printingThread = new std::thread([this]() -> void {return;});
}

void ProgressBar::stop() {

}

void ProgressBar::message(std::string msg) {
	std::cout << '\r' << msg << std::endl;
}

void ProgressBar::progress(float amount, int thread) {
	status[thread] = amount;
}
