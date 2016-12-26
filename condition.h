#ifndef CONDITION_H_
#define CONDITION_H_

#include "mutex.h"

#include <pthread.h>

class Condition
{
public:
	Condition(Mutex& mutex);
	~Condition();
	
	void Wait();
    
    bool WaitForSeconds(int seconds);
	
	void Notify();
	
	void NotifyAll();
	
private:
	pthread_cond_t cond_;
	Mutex& mutex_;
};






#endif


