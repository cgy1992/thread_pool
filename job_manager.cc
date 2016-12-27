#include "job_manager.h"

JobManager::JobManager() :
    mutex_(),
    cond_(mutex_)
{
    
}

JobManager::~JobManager()
{
    
}

void JobManager::AddJob(Job *job)
{
    MutexGuard guard(mutex_);
    if (job != NULL)
    {
        job_list_.push_back(job);
        cond_.Notify();
    }
}

void JobManager::RemoveJob(Job *job)
{
    MutexGuard guard(mutex_);
    if (job != NULL)
    {
        job_list_.remove(job);
    }
}

Job *JobManager::GetJob()
{
    MutexGuard guard(mutex_);
    Job* job = NULL;
    if (job_list_.size() != 0)
    {
        job = job_list_.front();
        job_list_.pop_front();
    }
    return job;
}