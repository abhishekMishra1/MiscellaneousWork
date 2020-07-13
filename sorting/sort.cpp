/***************************************************************************************************************************************************************
* FILE: sort.cpp                                                                                                                                               *
* DESC:                                                                                                                                                        *
* AUTH:                                                                                                                                                        *
***************************************************************************************************************************************************************/


#include<iostream>
#include"bubble.hpp"
#include"selection.hpp"
using namespace std;

int main(){
  int arr[] ={4,8,3,7,1};
  Selection<int> b(arr,5);
  b.displayData();
  b.sortData();
  b.displayData();

char cr[] ="Abhishek";
Selection<char> c(cr,strlen(cr));
c.displayData();
c.sortData();
c.displayData();

float fr[] ={1.2,6.5,34,0.56,43.54};
Selection<float> f(fr,5);
f.displayData();
f.sortData();
f.displayData();

  return 0;
}
