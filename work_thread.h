#ifndef WORK_THREAD_H_
#define WORK_THREAD_H_

#include "thread.h"

class Job;
class ThreadPool;

class WorkThread : public Thread 
{
public:
    WorkThread(ThreadPool* pool);
    virtual ~WorkThread();
    virtual void Run();
    
    void set_job(Job* job) { job_ = job; }
    
private:
    Job* job_;
    ThreadPool* pool_;
};

#endif