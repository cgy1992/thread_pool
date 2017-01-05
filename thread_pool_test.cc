#include "job.h"
#include "thread.h"
#include "thread_pool.h"
#include "thread_manager.h"


#include <iostream>
using namespace std;

class Job1 : public Job
{
public:
    virtual void DoJob()
    {
        if (param_ == NULL)
        {
            cout << "Job1 param == NULL" << endl;
        }
        else
        {
            cout << "Job1 &param = " << param() << endl;
        }

        Thread::Sleep(50000);
        
    }
};

int main()
{
    ThreadManager th_mgr;
    
    
    return 0;
}
