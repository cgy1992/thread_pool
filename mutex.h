#ifndef MUTEX_H_
#define MUTEX_H_

#include <pthread.h>

class Mutex
{
public:
	Mutex();
	~Mutex();
	
	bool Lock();
	bool Unlock();
	
	pthread_mutex_t* GetPthreadMutex() { return &mutex_; }
	
private:
	pthread_mutex_t mutex_;
};

class MutexGuard
{
public:
	MutexGuard(Mutex& mutex);
	~MutexGuard();
	
private:
	Mutex& mutex_;
};


#endif

