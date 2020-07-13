/***************************************************************************************************************************************************************
* FILE: quick.hpp                                                                                                                                              *
* DESC:                                                                                                                                                        *
* AUTH:                                                                                                                                                        *
***************************************************************************************************************************************************************/


#ifndef _QUICK_HPP_
#define _QUICK_HPP_

#include"sort.hpp"

template<class T>
class Quick:public Sort<T>{
public:
	int sortData();
	Quick(T *data, int size):Sort<T>(data,size){}
private:
	void quickSort( int lower, int upper );
	int partition( int lower, int upper );
protected:
	using Sort<T>::mSize;
	using Sort<T>::mData;
};

template<class T>
int Quick<T>::sortData(){
		quickSort(0, mSize-1);
		return 0;
}

template<class T>
int Quick<T>::partition( int low, int up ){
	int l, u, p,t;
	l = low+1;
	u = up;
	p = mData[l];
	if(u>=l){
		while(mData[l]<p)
			l++;
		while(mData[u]>p)
			u--;
		if(l<u){
			t = mData[l];
			mData[l] = mData[u];
			mData[u] = t;
		}
	}
	t = mData[low];
	mData[low] = mData[up];
	mData[up] = t;
}

template<class T>
void Quick<T>::quickSort(int lower, int upper){
	int pivot = partition( lower, upper );
	this->quicksort( lower, pivot-1);
	this->quicksort( pivot+1, upper);
}
#endif
