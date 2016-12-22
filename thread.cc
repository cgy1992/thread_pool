#include "thread.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>


static void* ThreadProc(void* arg)
{
    Thread* thread =reinterpret_cast<Thread*>(arg);
    assert(thread != NULL);
    thread->Run();
    return NULL;
}

Thread::Thread() :
    running_(false),
    create_suspended_(false),
    detached_(false),
    thread_state_(TS_FREE),
    errno_(0),
    sched_priority_(SP_OTHER),
    thread_id_(-1)    
{
    
}

Thread::Thread(bool suspend, bool detach) :
    running_(false),
    create_suspended_(suspend),
    detached_(detach),
    thread_state_(TS_FREE),
    errno_(0),
    sched_priority_(SP_OTHER),
    thread_id_(-1)    
{
    
}

Thread::~Thread()
{
    
}

bool Thread::Detach()
{
    if (!running_ && !detached_)
    {
        errno_ = pthread_detach(thread_id_);
        detached_ = errno_ != 0;
    }
    return detached_;
}

bool Thread::Start()
{
    running_ = true;
    
    // 默认优先级是 SCHED_OTHER, 现在要提高线程的优先级， 提高成SCHED_RR
    pthread_attr_init(&thread_attr_);
    struct sched_param param;
    param.sched_priority = 51;
    
    if (detached_)
    {
        errno_ = pthread_attr_setdetachstate(&thread_attr_, PTHREAD_CREATE_DETACHED);
        detached_ = errno_ == 0;
    }
    
    if (sched_priority_ != SP_OTHER) 
    {
        errno_ = pthread_attr_setschedpolicy(&thread_attr_, SCHED_RR);
        errno_ = pthread_attr_setschedparam(&thread_attr_, &param);                 
        errno_ = pthread_attr_setinheritsched(&thread_attr_, PTHREAD_EXPLICIT_SCHED);                
    }
    
    if (( errno_ = pthread_create(&thread_id_, &thread_attr_, ThreadProc, this)) != 0)
    {
        printf("创建线程失败, %s\n", strerror(errno_)); // Resource temporarily unavailable 是因为线程创建过多，结束时没有释放资源
        abort();
    }
    return true;
}

void Thread::Sleep(int usec)
{
    usleep(usec);
}

bool Thread::Wakeup()
{
    
}

bool Thread::Yield()
{
    errno_ = pthread_yield();
    return errno_ == 0;
}

bool Thread::Join()
{
    errno_ =  pthread_join(thread_id_, NULL);
    return errno_ == 0;
}

bool Thread::Terminate()
{
    
}

void Thread::Exit()
{
    
}
