/***************************************************************************************************************************************************************
* FILE: Main.cpp                                                                                                                                               *
* DESC:                                                                                                                                                        *
* AUTH:                                                                                                                                                        *
***************************************************************************************************************************************************************/


#include<iostream>

#include "ThreeDNode.h"
#include "NodeTable.h"

using namespace std;

int main()
{
	NodeTable myTable;
	myTable.GenerateRandomPoints(10, 100);
	myTable.DisplayData();	

	return 0;
}
