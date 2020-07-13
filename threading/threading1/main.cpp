/***************************************************************************************************************************************************************
* FILE: main.cpp                                                                                                                                               *
* DESC:                                                                                                                                                        *
* AUTH:                                                                                                                                                        *
***************************************************************************************************************************************************************/


#include<iostream>
#include"thread.hpp"

using namespace std;

int main(){

	Thread t1;
	char ch;
	while(1){
		cout<<"\nCreating Thread:\n1. 'c' for Creating thread.\n2. 'd' for Destroying created thread.\n3. 'e' for Exit.\nAns:";
		cin>>ch;
		cout<<endl;
		if(ch == 'c' || ch == 'C')
			t1.createThrd();
		else if(ch == 'd' || ch == 'D')
			t1.destroyThrd();
		else break;
	}
	cout<<"Thank you. Hope your return\n\n";
return 0;
}
