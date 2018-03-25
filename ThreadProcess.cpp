#include "ThreadProcess.h"



ThreadProcess::ThreadProcess():
	running(false)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////

ThreadProcess::~ThreadProcess() {
}

///////////////////////////////////////////////////////////////////////////////////////////////

void ThreadProcess::run() {
	running = true;
	while (running)
		process();
}

///////////////////////////////////////////////////////////////////////////////////////////////

void ThreadProcess::stop() {
	running = false;
}

///////////////////////////////////////////////////////////////////////////////////////////////

bool ThreadProcess::isRunning() const {
	return running;
}