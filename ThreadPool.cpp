#include "ThreadPool.h"



void ThreadPool::initializeWorkers() {
	for (auto*& w : workers)
		w = new WorkerThread;
}

///////////////////////////////////////////////////////////////////////////////////////////////

ThreadPool::ThreadPool():
	workers(10),
	finished(false)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////

ThreadPool::ThreadPool(size_t workers):
	workers((WorkerThread*)nullptr, workers),
	finished(false)
{
	initializeWorkers();
}

///////////////////////////////////////////////////////////////////////////////////////////////

ThreadPool::~ThreadPool() {
	workers.call(&WorkerThread::stop);
	workers.call(&WorkerThread::join);
	workers.delete_each();
}

///////////////////////////////////////////////////////////////////////////////////////////////

void ThreadPool::run() {
	workers.call(&WorkerThread::start);
}

///////////////////////////////////////////////////////////////////////////////////////////////

void ThreadPool::setThreads(size_t n) {
	workers.delete_each().clear();
	repeat(n)
		workers.push_back(new WorkerThread);
}

///////////////////////////////////////////////////////////////////////////////////////////////

size_t ThreadPool::threadsNumber() const {
	return workers.size();
}

///////////////////////////////////////////////////////////////////////////////////////////////

//void ThreadPool::addWorker(WorkerThread * worker) {
//	workers.push_back(worker);
//}

void ThreadPool::setJobs(x::vector<Job*> const & jobs) {
	//while (!finished){}
	//finished = false;
	for (size_t i = 0, ws = workers.size(); i<ws; ++i) 
		workers[i]->setJob(jobs[i]);
	//finished = true;
	//this->jobs = jobs;
}

//void ThreadPool::setJobs(x::vector<Job*>&& jobs) {
//	this->jobs = jobs.move();
//}

//void ThreadPool::execute() {
//	/*for (size_t i = 0, ws = workers.size(); i<ws; ++i) 
//		workers[i]->setJob(jobs[i]);
//	workers.call(&WorkerThread::finish, 1);*/
//}

void ThreadPool::finish() {
	workers.call(&WorkerThread::finish, 1);
}
