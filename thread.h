#ifndef THREAD_H_
#define THREAD_H_

#include <string>
#include <pthread.h>

enum ThreadState
{
    TS_FREE = 0,
    TS_BUSY,
    TS_SUSPEND,
    TS_TERMINATE
};

class Thread
{
public:
    Thread();
    Thread(bool suspend, bool detach);
    virtual ~Thread();
    virtual void Run() = 0;
    
    bool Detach();
    
    bool Start();
    static void Sleep(int micro_seconds);
    bool Wakeup();
    
    bool Yield();
    bool Join();
    
    bool Terminate();
    void Exit();

    ThreadState  thread_state() const { return thread_state_; }

    void set_thread_name(const std::string& name) { thread_name_ = name; }
    const std::string& thread_name() const { return thread_name_; }

    pthread_t thread_id() const { return thread_id_; }
    static pthread_t ThreadSelf();

    bool set_priority(int priority);
    int priority() const { return priority_; }

    void set_thread_state(ThreadState state) { thread_state_ = state;}
    void set_errno(int errno) { errno_ = errno; }
    int last_errno(){ return errno_; }

private:
    bool running_;
    bool create_suspended_;
    bool detachd_;
    ThreadState thread_state_;
    int errno_;
    int priority_;
    pthread_t thread_id_;
    std::string thread_name_;
};

#endif
