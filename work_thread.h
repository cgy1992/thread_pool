#ifndef WORK_THREAD_H_
#define WORK_THREAD_H_

#include "thread.h"
#include "mutex.h"
#include "condition.h"

class ThreadPool;

class WorkThread : public Thread 
{
public:
    WorkThread(ThreadPool* pool);
    virtual ~WorkThread();
    virtual void Run();
    
private:
    ThreadPool* pool_;

    
};

#endif