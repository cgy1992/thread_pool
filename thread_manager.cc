#include "thread_manager.h"
#include "work_thread.h"
#include "job_manager.h"
#include <assert.h>

ThreadManager::ThreadManager(size_t size) :
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
        
        // TODO 根据相应的算法，决定什么时候扩容
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





