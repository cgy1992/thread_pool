#include "thread_manager.h"
#include "work_thread.h"
#include "job_manager.h"
#include <assert.h>

ThreadManager::ThreadManager(size_t size, size_t incr_size) :
    incr_size_(incr_size),
    running_(false),
    job_manager_(NULL),
    thread_pool_(NULL)
{
    job_manager_ = new JobManager();
    assert(job_manager_ != NULL);
    
    thread_pool_ = new ThreadPool(size);
    assert(thread_pool_ != NULL);
}

ThreadManager::~ThreadManager()
{
    if (job_manager_ != NULL)
        delete job_manager_;
    
    if (thread_pool_ != NULL)
        delete thread_pool_;
}

void ThreadManager::Run()
{
    running_ = true;
    
    while (running_)
    {
        Job* job = job_manager_->GetJob();
        if (job == NULL)
        {
            Thread::Sleep(1000);
            continue;
        }
        
        
        Thread* thread = thread_pool_->GetIdleThread();
        if (thread == NULL)
        {
            job_manager_->AddJob(job);
            Thread::Sleep(1000);
            continue;
        }
        
        WorkThread* work_thread = static_cast<WorkThread*>(thread);
        work_thread->set_job(job);
        work_thread->set_thread_state(TS_BUSY);
        work_thread->Resume();
    }
}

void ThreadManager::AddJob(Job *job)
{
    if (job != NULL)
    {
        job_manager_->AddJob(job);
    }
}





