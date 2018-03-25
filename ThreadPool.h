#pragma once

#include "ThreadUnit.h"
#include "WorkerThread.h"
#include "xvector.h"

class ThreadPool: public ThreadUnit
{
	x::vector<WorkerThread*> workers;
	x::vector<Job*> jobs;

	//? finished unnecessary?
	volatile bool finished;

	void initializeWorkers();

public:
	//static constexpr size_t DEFAULT_WORKERS = 10;

	ThreadPool();
	ThreadPool(size_t workers);
	virtual ~ThreadPool();
	virtual void run() override;
	virtual void setThreads(size_t n);
	size_t threadsNumber() const;
	//void addWorker(WorkerThread* worker);
	void setJobs(x::vector<Job*> const& jobs);
	//void setJobs(x::vector<Job*> && jobs);
	//void execute();
	void finish();
};

