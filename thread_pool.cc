#include "thread_pool.h"
#include "work_thread.h"

#include <assert.h>

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
        busy_threads_.push_back(thread);
        assert(idle_threads_.size() + busy_threads_.size() == pool_size_);
    }
    return thread;
}

void ThreadPool::AddIdleThread(Thread *thread)
{
    MutexGuard guard(mutex_);
    if (thread != NULL)
    {
        idle_threads_.push_back(thread);
        busy_threads_.remove(thread);
        assert(idle_threads_.size() + busy_threads_.size() == pool_size_);
    }
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
    Thread* thread = NULL;
    while (!idle_threads_.empty())
    {
        Thread* thread = idle_threads_.front();
        idle_threads_.pop_front();
        if (thread != NULL)
        {
            thread->Terminate();
            delete thread;
            thread = NULL;
        }
    }
    pool_size_ -= idle_threads_.size();
    
    while (!busy_threads_.empty())
    {
        thread = busy_threads_.front();
        busy_threads_.pop_front();
        if (thread != NULL)
        {
            thread->Terminate();
            delete thread;
            thread = NULL;
        }
    }
    pool_size_ -= busy_threads_.size();
    assert(pool_size_ == 0);
}

void ThreadPool::CreateThreadPool(size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        idle_threads_.push_back(new WorkThread(this));
    }
}

