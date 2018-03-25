#pragma once

#include <thread>
#include <mutex>

class ThreadUnit
{
	std::thread thread;
	std::mutex m;

public:
	ThreadUnit();
	virtual ~ThreadUnit();
	virtual void run() abstract;
	void join();
	void start();
};

