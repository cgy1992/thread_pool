#include "condition.h"
#include <errno.h> // ETIMEOUT
#include <time.h> // clock_gettime

Condition::Condition(Mutex& mutex) : mutex_(mutex)
{
	pthread_cond_init(&cond_, NULL);
}

Condition::~Condition()
{
	pthread_cond_destroy(&cond_);
}

void Condition::Wait()
{
	pthread_cond_wait(&cond_, mutex_.GetPthreadMutex());
}

bool Condition::WaitForSeconds(int seconds)
{
    struct timespec abstime;
    clock_gettime(CLOCK_REALTIME, &abstime);
    abstime.tv_sec += seconds;
    return pthread_cond_timedwait(&cond_, mutex_.GetPthreadMutex(), &abstime) == ETIMEDOUT;
}

void Condition::Notify()
{
    pthread_cond_signal(&cond_);
}

void Condition::NotifyAll()
{
    pthread_cond_broadcast(&cond_);
}
