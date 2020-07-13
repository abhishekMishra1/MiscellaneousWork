/***************************************************************************************************************************************************************
* FILE: thread.cpp                                                                                                                                             *
* DESC:                                                                                                                                                        *
* AUTH:                                                                                                                                                        *
***************************************************************************************************************************************************************/


#include"thread.hpp"
#include<stdio.h>
#include<unistd.h>
#include<iostream>
#include<cstring>

int Thread::mThreadCounter = 0;
int Thread::mShared;
pthread_mutex_t glock;
char Thread::msg[256] = "";

Thread::Thread():mThrdId(0),mTrdFn(0){
	pthread_mutex_init(&glock, NULL);
	pthread_t dummy = 0;
	mThrdId.push_back(dummy);

}


void* Thread::increment(void* arg){
	std::cout<<"\nThread number "<<mThreadCounter<<" started\nTrying to aquire lock\n";
	char data[] = "Incremental thread exited\n";
	for(int i=0;i<5;i++){
		pthread_mutex_lock(&glock);
		//--------------CRITICAL SECTION STARTED---------------
			std::cout<<"Lock aquired\n";
			++mShared;
		//--------------CRITICAL SECTION END-------------------
		pthread_mutex_unlock(&glock);
		std::cout<<"\nmShared: "<<mShared<<"\nLock released by thread "<<mThreadCounter<<std::endl;
		sleep(2);
	}

	strcpy(msg,data);
	pthread_exit(static_cast<void*>(msg));
}

void* Thread::decrement(void* arg){
	std::cout<<"\nThread number "<<mThreadCounter<<" started\n";
	char data[] = "Decremental thread exited\n";
	for(int i=0;i<5;i++){
		pthread_mutex_lock(&glock);
		//--------------CRITICAL SECTION STARTED---------------
			std::cout<<"Lock aquired\n";
			--mShared;
		//--------------CRITICAL SECTION END-------------------
		pthread_mutex_unlock(&glock);
		std::cout<<"\nmShared: "<<mShared<<"\nLock released by thread "<<mThreadCounter<<std::endl;
		sleep(3);
	}
	strcpy(msg,data);
	pthread_exit(static_cast<void*>(msg));
}

void Thread::createThrd(){
	pthread_t tdId;
	int res;
	void* threadRes;
	char greet[]="Hello";
	if(mThreadCounter%2 == 0)
		mTrdFn = increment;
	else
		mTrdFn = decrement;

	res = pthread_create(&tdId,NULL, mTrdFn, NULL);
	if(res != 0){
		std::cerr<<"\nError in creating thread\n";
		return;
	}
	std::cout<<"\nThread Id is "<<tdId<<" for thread number "<<mThreadCounter<<std::endl;
	mThrdId.push_back(tdId);
	++mThreadCounter;
}

void Thread::destroyThrd(){
	if(mThreadCounter > 0){
		pthread_t& tdId = mThrdId[mThreadCounter];
		std::cout<<"\nThread Id is "<<tdId<<" for thread number "<<mThreadCounter<<std::endl;
		mThrdId.pop_back();
		--mThreadCounter;
		void* data = 0;
		int res = pthread_join(tdId, &data);
		if(res !=0 ){
			std::cerr<<"\nError in joining thread\n";
			return;
		}
		std::cout<<"\nReceived Thread msg: "<<static_cast<char*>(data)<<std::endl;
	}
	else std::cerr<<"\nNo thread remained for killing\n";
}

Thread::~Thread(){
	pthread_mutex_destroy(&glock);
}

