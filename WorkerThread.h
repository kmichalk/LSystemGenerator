#pragma once

#include "ThreadProcess.h"
#include "Job.h"

class WorkerThread: public ThreadProcess
{
	static constexpr int DEFAUTL_FINISH_CHECK_INTERVAL = 1;
	static constexpr int DEFAUTL_JOB_CHECK_INTERVAL = 1;

	volatile bool finished;
	int jobCheckInterval;
	Job* job;
	std::mutex jobLock;

public:
	WorkerThread();
	virtual ~WorkerThread();
	virtual void run() override;
	virtual void process() override;
	void finish(int checkInterval = DEFAUTL_FINISH_CHECK_INTERVAL);
	bool hasFinished() const;
	void setJobCheck(int ms);
	void setJob(Job* job);
};

