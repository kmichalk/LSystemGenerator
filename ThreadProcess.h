#pragma once

#include "ThreadUnit.h"

class ThreadProcess: public ThreadUnit
{
protected:
	volatile bool running;

public:
	ThreadProcess();
	virtual ~ThreadProcess();
	virtual void run() override;
	void stop();
	virtual void process() abstract;
	bool isRunning() const;
};

