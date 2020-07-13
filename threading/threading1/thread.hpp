/***************************************************************************************************************************************************************
* FILE: thread.hpp                                                                                                                                             *
* DESC:                                                                                                                                                        *
* AUTH:                                                                                                                                                        *
***************************************************************************************************************************************************************/


#ifndef _THREAD_HPP_
#define _THREAD_HPP_

#include<pthread.h>
#include<string>
#include<vector>

class Thread{
public:
	static void* increment(void *arg);
	static void* decrement(void *arg);
	void createThrd();
	void destroyThrd();
	Thread();
	~Thread();
private:
	std::vector<pthread_t > mThrdId;
	static int mShared;
	static int mThreadCounter;
	typedef void* (*FnPtr)(void*);
	FnPtr mTrdFn;
	static char msg[256];


protected:

};

#endif
