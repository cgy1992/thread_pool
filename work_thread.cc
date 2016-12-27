#include "work_thread.h"
#include "thread_pool.h"
#include "job.h"

#include <assert.h>

WorkThread::WorkThread(ThreadPool* pool) : 
    job_(NULL),
   pool_(pool)
{
    
}

WorkThread::~WorkThread()
{
    
}

void WorkThread::Run()
{
    while (running_)
    {
        thread_state_ = TS_BUSY;   
        assert(job_ != NULL);
        job_->DoJob(NULL);
        delete job_;
        job_ = NULL;
        thread_state_ = TS_IDLE;
        pool_->AddIdleThread(this);
        Suspend();
    }
}
