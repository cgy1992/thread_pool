#ifndef JOB_H_
#define JOB_H_

#include <stdlib.h>

class Job
{ 
public: 
    Job() : param_(NULL) {}
    virtual ~Job();
    virtual void DoJob() = 0; 
    
    void set_param(void* param) { param_ = param; }
    void* param() { return param_; }
    
protected:
    void* param_;
}; 

#endif