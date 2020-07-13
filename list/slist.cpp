/***************************************************************************************************************************************************************
* FILE: slist.cpp                                                                                                                                              *
* DESC:                                                                                                                                                        *
* AUTH:                                                                                                                                                        *
***************************************************************************************************************************************************************/


#include<iostream>
#include"slist.hpp"

using namespace std;

int main(){

  Slist<int> lst;
  lst.addNode(10);
  lst.addNode(20);
  lst.addNode(30);
  lst.addNode(40);
  lst.addNode(50);
  
  lst.printList();
  bool found=false;
  found = lst.search(80);
  if(found)
    cout<<"Found the searched item\n";
  else
    cout<<"Not found searched item\n";

  lst.printList();
  lst.addNode(80);
  lst.printList();
  found = lst.search(80);
  if(found)
    cout<<"Found the searched item\n";
  else
    cout<<"Not found searched item\n";
  lst.delNode(30);
  lst.printList();
  
  cout<<endl;
  Slist<char> clst;
  clst.addNode('a');
  clst.addNode('b');
  clst.addNode('c');
  clst.addNode('d');
  clst.addNode('e');
  
  clst.printList();
  found = clst.search('f');
  if(found)
    cout<<"Found the searched item\n";
  else
    cout<<"Not found searched item\n";

  clst.printList();
  clst.addNode('f');
  clst.printList();
  found = clst.search('f');
  if(found)
    cout<<"Found the searched item\n";
  else
    cout<<"Not found searched item\n";
  clst.delNode('d');
  clst.printList();
  
  
  return 0;
}
