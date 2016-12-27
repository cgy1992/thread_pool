#ifndef JOB_H_
#define JOB_H_

class Job
{ 
public: 
    Job();
    virtual ~Job();
    virtual void DoJob(void* arg) = 0; 
}; 

#endif