/***************************************************************************************************************************************************************
* FILE: bubble.hpp                                                                                                                                             *
* DESC:                                                                                                                                                        *
* AUTH:                                                                                                                                                        *
***************************************************************************************************************************************************************/


#ifndef _BUBBLE_HPP_
#define _BUBBLE_HPP_

#include"sort.hpp"


template<class T>
class Bubble:public Sort<T>{

public:
	Bubble(T *data, int size):Sort<T>(data, size){
	}
	int sortData();

protected:
	using Sort<T>::mSize;
	using Sort<T>::mData;
};

template<class T>
int Bubble<T>::sortData(){
	bool flag=false;
	for(int i = 0; i< mSize; i++){
		for(int j = 0; j<mSize-i-1;j++)
			if(mData[j]>mData[j+1]){
				this->swap(mData[j],mData[j+1]);
				flag = true;
			}
		if(!flag)
			break;
	}

}


#endif
  
