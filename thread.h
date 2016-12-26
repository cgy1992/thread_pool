#ifndef THREAD_H_
#define THREAD_H_

#include <string>
#include <pthread.h>

#include "mutex.h"
#include "condition.h"

enum ThreadState
{
    TS_IDLE = 0,
    TS_BUSY,
    TS_SUSPEND,
    TS_TERMINATE
};

class Thread
{
public:
    explicit Thread(bool detach = false);
    virtual ~Thread();
    virtual void Run() = 0;
    
    bool Detach();
    
    bool Start();
    static void Sleep(int usec);
    void Stop() { running_ = false; }
    void Terminate();
    
    bool Yield();
    bool Join();
    
    bool Resume();
    bool Suspend();

    ThreadState  thread_state() const { return thread_state_; }

    void set_thread_name(const std::string& name) { thread_name_ = name; }
    const std::string& thread_name() const { return thread_name_; }

    pthread_t thread_id() const { return thread_id_; }
    static pthread_t ThreadSelf();

    void set_thread_state(ThreadState state) { thread_state_ = state;}
    void set_errno(int errno) { errno_ = errno; }
    int last_errno(){ return errno_; }

protected:
    bool running_;
    bool create_suspended_;
    bool detached_;
    ThreadState thread_state_;
    int errno_;
    pthread_t thread_id_;
    pthread_attr_t thread_attr_;
    std::string thread_name_;
    Mutex mutex_;
    Condition cond_;
};

#endif
