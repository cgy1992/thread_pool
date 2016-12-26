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

Thread::Thread(bool detach) :
    running_(false),
    detached_(detach),
    thread_state_(TS_IDLE),
    errno_(0),
    thread_id_(-1)    ,
    mutex_(),
    cond_(mutex_)
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
    
    pthread_attr_init(&thread_attr_);
    
    if (detached_)
    {
        errno_ = pthread_attr_setdetachstate(&thread_attr_, PTHREAD_CREATE_DETACHED);
        detached_ = errno_ == 0;
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

bool Thread::Resume()
{
    cond_.Notify();
    return true;
}

bool Thread::Suspend()
{
    if (thread_state_ == TS_BUSY || thread_state_ == TS_SUSPEND || thread_state_ == TS_TERMINATE)
        return false;
    
    while (thread_state_!= TS_IDLE)
        cond_.Wait();
    
    return true;
}
