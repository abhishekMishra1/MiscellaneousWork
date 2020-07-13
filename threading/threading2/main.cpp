#include"Thread.hpp"

int main(){
	Thread* ptr = new myThread;
	ptr->execute();
	ptr->join();
	return 0;
}
