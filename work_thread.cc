#include "work_thread.h"
#include "thread_pool.h"

WorkThread::WorkThread(ThreadPool* pool) : 
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
        switch(thread_state_)
        {
        case TS_IDLE:
            // 在idle 条件下等待, 返回
            break;
        case TS_BUSY:
            break;
        case TS_SUSPEND:
            break;
        case TS_TERMINATE:
            break;
        default:
            break;
        }
    }
}
