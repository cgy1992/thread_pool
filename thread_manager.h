#ifndef THREAD_MANAGER_H_
#define THREAD_MANAGER_H_

#include "thread.h"
#include "mutex.h"
#include "condition.h"

#include "thread_pool.h"

#include <list>
#include <stdint.h>

class Job;
class ThreadPool;

class ThreadManager
{
public:
    typedef std::list<Job*> JobList;
    
    ThreadManager(size_t size = 10);
    ~ThreadManager();

    void Run();

    void AddJob(Job* job);
    void RemoveJob(Job* job);
    Job* GetJob();
    
//    ThreadData& GetJobThreadData() { return mJobThreadData; }

    ThreadPool*  thread_pool() { return thread_pool_; }
    void IncreasePool(size_t size) { thread_pool_->Increase(size); }
    void DecreasePool(size_t size) { thread_pool_->Decrease(size); }
    void SetPoolSize(size_t size) { thread_pool_->set_pool_size(size); }
    void CleanUpPool() { thread_pool_->CleanUpPool(); }

//    HANDLE GetExitEvent() const { return mExitEvent; }
//    void SetRunEvent(ThreadData& threadData);

//    void EnumProcess(void);

private:
//    static UINT __stdcall JobThreadProc(LPVOID pParam);

private:
    JobList job_list_;
    ThreadPool* thread_pool_;
//    ThreadData mJobThreadData;
//    HANDLE mExitEvent;
};

#endif