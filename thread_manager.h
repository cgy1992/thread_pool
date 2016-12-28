#ifndef THREAD_MANAGER_H_
#define THREAD_MANAGER_H_

#include "thread_pool.h"
#include <list>

const size_t DEFAULT_POOL_SIZE = 2;
const size_t DEFAULT_INCR_SIZE = 5;

class Job;
class JobManager;
class ThreadPool;

class ThreadManager
{
public:
    explicit ThreadManager(size_t size = DEFAULT_POOL_SIZE, size_t incr_size = DEFAULT_INCR_SIZE);
    ~ThreadManager();

    void Run();
    
    void AddJob(Job* job);


private:
    ThreadPool*  thread_pool() { return thread_pool_; }
    void IncreasePool(size_t size) { thread_pool_->Increase(size); }
    void DecreasePool(size_t size) { thread_pool_->Decrease(size); }
    void SetPoolSize(size_t size) { thread_pool_->set_pool_size(size); }
    void CleanUpPool() { thread_pool_->CleanUpPool(); }
    
    
    size_t incr_size_;
    bool running_;
    JobManager* job_manager_;
    ThreadPool* thread_pool_;
    
};

#endif