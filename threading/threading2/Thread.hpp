#include<pthread.h>
#include<iostream>

class Threadable{
public:
	void execute()=;
};

	
class Thread{

public:
	void execute(){
		mResult = pthread_create(&mThreadId, NULL, run, this);
		if(mResult !=0){
			std::cerr<<"Failed to create new thread\n";
			return;
		}
		std::cout<<"Created Thread with Id: "<<mThreadId<<std::endl;
	}
			
	void join(){
		mResult = pthread_join(mThreadId, &mData);
		if(mResult !=0){
			std::cerr<<"Failed to join newly thread\n";
			return;
		}
	}
		
		

protected:
	static void *run(void* that){
		static_cast<Thread*>(that)->main();
	}
	
private:
	virtual void main()=0;



	private:
	pthread_t mThreadId;
	int mResult;
	void* mData;

};






class myThread:public Thread{

public:
	void main(){
		for(int i=0;i<5;i++){
			std::cout<<"Thread running: "<<i<<std::endl;
		}
	}
};



