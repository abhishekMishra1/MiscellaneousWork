/***************************************************************************************************************************************************************
* FILE: selection.hpp                                                                                                                                          *
* DESC:                                                                                                                                                        *
* AUTH:                                                                                                                                                        *
***************************************************************************************************************************************************************/


#ifndef _SELECTION_HPP_
#define _SELECTION_HPP_

#include"sort.hpp"

template<class T>
class Selection:public Sort<T>{

public:
	int sortData();
	Selection(T* data, int size):Sort<T>(data, size){}
private:

protected:
	using Sort<T>::mSize;
	using Sort<T>::mData;
};

template<class T>
int Selection<T>::sortData(){
	for(int i = 0; i< mSize; i++)
		for(int j = i+1; j<mSize;j++)
			if(mData[i]>mData[j])
				this->swap(mData[i],mData[j]);

}

#endif
