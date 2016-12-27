#ifndef JOB_MANAGER_H_
#define JOB_MANAGER_H_

#include "mutex.h"
#include "condition.h"
#include <list>

class Job;

class JobManager
{ 
public: 
    typedef std::list<Job*> JobList;
    
    JobManager();
    ~JobManager();
    
    void AddJob(Job* job);
    void RemoveJob(Job* job);
    Job* GetJob();
    
private:
    Mutex mutex_;
    Condition cond_;
    
    JobList job_list_;
}; 

#endif