#include "thread_pool.h"
#include "work_thread.h"

ThreadPool::ThreadPool(size_t size) :
    pool_size_(size),
    mutex_()
{
    CreateThreadPool(size);
}

ThreadPool::~ThreadPool()
{
    
}

Thread *ThreadPool::GetIdleThread()
{
    MutexGuard guard(mutex_);
    Thread* thread = NULL;
    if (!idle_threads_.empty())
    {
        thread = idle_threads_.front();
        idle_threads_.pop_front();
    }
    return thread;
}

void ThreadPool::Increase(size_t size)
{
    MutexGuard guard(mutex_);
    pool_size_ += size;
    CreateThreadPool(size);
}

void ThreadPool::Decrease(size_t size)
{
    MutexGuard guard(mutex_);
    
    if (idle_threads_.size() < size)
    {
        size = idle_threads_.size();
    }
    pool_size_ -= size;
    
    while (size > 0)
    {
        Thread* thread = idle_threads_.front();
        if (thread != NULL)
        {
            thread->Terminate();
            delete thread;
        }
        --size;
    }
}

void ThreadPool::CleanUpPool()
{
    MutexGuard guard(mutex_);
    while (!idle_threads_.empty())
    {
        Thread* thread = idle_threads_.front();
        idle_threads_.pop_front();
        if (thread != NULL)
        {
            thread->Terminate();
            delete thread;
        }
    }
    pool_size_ -= idle_threads_.size();
}

void ThreadPool::CreateThreadPool(size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        idle_threads_.push_back(new WorkThread(this));
    }
}

