/***************************************************************************************************************************************************************
* FILE: sort.hpp                                                                                                                                               *
* DESC:                                                                                                                                                        *
* AUTH:                                                                                                                                                        *
***************************************************************************************************************************************************************/


#ifndef _SORT_HPP_
#define _SORT_HPP_
#include<iostream>
#include<cstring>
enum sortType{
  BUBBLE,
  SELECTION,
  INDEX,
  SHELL,
  MERGE,
  QUICK,
  OTHERS
};

template<class T>
class Sort{

public:
  sortType mSortType;
  virtual int sortData()=0;
  virtual ~Sort(){}
  Sort(T *data, int size):mData(data),mSize(size),mSortType(OTHERS){}
  void displayData();

private:

protected:
  T *mData;
  int mSize;

  void swap(T &data1, T &data2);
};


template<class T>
void Sort<T>::displayData(){
	for(int i = 0; i<mSize; i++)
		std::cout<<mData[i]<<" ";
	std::cout<<std::endl;
}

template<class T>
void Sort<T>::swap(T &data1, T &data2){
	T temp;
	temp = data1;
	data1 = data2;
	data2 = temp;
}

  
#endif
