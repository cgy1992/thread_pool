#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_

#include "mutex.h"
#include <list>
#include <stdint.h>

class Thread;

class ThreadPool
{
public:
    typedef std::list<Thread*> ThreadList;
    
    explicit ThreadPool(size_t size);
    ~ThreadPool();
    Thread* GetIdleThread();
    void AddIdleThread(Thread* thread);
    
    void Increase(size_t size);
    void Decrease(size_t size);
    
    void CleanUpPool();
    
    void set_pool_size(size_t size) { pool_size_ = size; }
    const size_t pool_size() const { return pool_size_; }
    
private:
    void CreateThreadPool(size_t size );

private:
    size_t pool_size_;
    Mutex mutex_;
    ThreadList idle_threads_;
    ThreadList busy_threads_;
};

#endif