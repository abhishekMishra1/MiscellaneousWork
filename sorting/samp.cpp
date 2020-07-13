#include<iostream>


template<class T>
class base{
public:
	T m;
	void basefun(){
		m=10;
		std::cout<<"Base fun\n";}
};

template<class T>
class deri:public base<T>{
public:
	T d;
	void fun(){
		std::cout<<"Derived fun\n";
		m=20;	//will give a compilation error
	//	this->m=20;	//will run successfully
		d=10;
	}
};

int main(){
	deri<int> obj;
	obj.fun();
	obj.basefun();
	return 0;
}
