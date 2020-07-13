#include<pthread.h>
#include<iostream>
#include<semaphore.h>
#include<unistd.h>

class Threadable{
public:
	virtual void execute()=0;
	Threadable(){
		mResult = sem_init(&mBinSema, 0,1);
		if(mResult !=0){
			std::cerr<<"Failed to init new semaphore\n";
			return;
			}
		std::cout<<"Successfully created semaphore\n";
		}
	sem_t mBinSema;
	virtual ~Threadable(){}
protected:
	int mResult;
};

	
class Thread{

public:
	Thread(){
/*		mResult = sem_init(&mBinSema, 0, 0);
		if(mResult !=0){
			std::cerr<<"Failed to init new semaphore\n";
			return;
			}
		std::cout<<"Successfully created semaphore\n";
		
		mResult = pthread_mutex_init(&mLock, NULL);
		if(mResult !=0){
			std::cerr<<"Failed to init new mutex\n";
			return;
			}
		std::cout<<"Successfully created mutex\n";		
*/		}

	void execute(Threadable *that){
		sem_wait(&that->mBinSema);
		mResult = pthread_create(&mThreadId, NULL, run, that);
		if(mResult !=0){
			std::cerr<<"Failed to create new thread\n";
			return;
		}
		std::cout<<"Created Thread with Id: "<<mThreadId;
		std::cout<<std::endl;
		sem_post(&that->mBinSema);

	}
			
	void join(){
		mResult = pthread_join(mThreadId, &mData);
		if(mResult !=0){
			std::cerr<<"Failed to join newly thread\n";
			return;
		}
		std::cout<<"Thread successfully joined\n";
	}
		
		

protected:
//	virtual void runMe()=0;
	
private:
	static void *run(void* that){
		sem_wait(&(static_cast<Threadable*>(that)->mBinSema));
		static_cast<Threadable*>(that)->execute();
		sem_post(&(static_cast<Threadable*>(that)->mBinSema));
	}



	private:
	pthread_t mThreadId;
	int mResult;
	void* mData;
//	sem_t mBinSema;
//	pthread_mutex_t mLock;
};


class myThread:public Threadable{

public:
	void execute(){
		for(int i=0;i<5;i++){
			//sleep(1);
			std::cout<<"Thread running: "<<i<<std::endl;
		}
	}
};



