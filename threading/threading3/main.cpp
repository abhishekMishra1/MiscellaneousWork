#include"Thread.hpp"

int main(){
	Thread ptr;// = new myThread;
	ptr.execute(new myThread);
	ptr.join();
	return 0;
}
