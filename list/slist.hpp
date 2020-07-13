/***************************************************************************************************************************************************************
* FILE: slist.hpp                                                                                                                                              *
* DESC:                                                                                                                                                        *
* AUTH:                                                                                                                                                        *
***************************************************************************************************************************************************************/


#ifndef _SLIST_HPP_
#define _SLIST_HPP_

template<class T>
class Node{
public:
  T m_data;
  Node *m_next;
  
public:
  Node():m_data(0),m_next(0){}
  Node(T data):m_data(data),m_next(0){}
  Node<T>*& next(){return m_next;}
  T& data(){return m_data;}
};
  
template<class T>
class Slist{
  Node<T> *mHead;
  Node<T> *mTemp;
  int  mElements;
  
public:
  Slist():mHead(0),mTemp(0),mElements(0){}

  void addNode(T data){
      Node<T>* newNode = new Node<T>(data);
      newNode->m_next  = 0;

      if(!mHead){
	mHead = newNode;
      }
      else{
	mTemp = mHead;
	
	while(mTemp->m_next)
	  mTemp = mTemp->m_next;
	
	mTemp->m_next = newNode;
      }
  }
  
  void delNode(T data){
    
    mTemp = mHead;
    if(mTemp->m_data == data){//head is to be deleted
      mHead = mTemp->m_next;
      delete mTemp;
    }
    else{
//      mTemp = mTemp->m_next;
      while(mTemp->m_next->m_next){
	if(data == mTemp->m_next->m_data){
	  Node<T>*tempNode = mTemp->m_next;
	  mTemp->m_next = mTemp->m_next->m_next;
	  delete tempNode;
	}
	mTemp = mTemp->m_next;
      }
      //For the last node case
      if(mTemp->m_next->m_next == 0 && mTemp->m_next->m_data == data){
	delete mTemp->m_next;
	mTemp->m_next = 0;
      }
    }
  }
      
  bool search(T data){
    bool found = false;
    mTemp = mHead;
    while(mTemp->m_next){
      if(data == mTemp->m_data)
	found = true;
      mTemp = mTemp->m_next;
    }
    if(mTemp->m_data == data){
    	found = true;
    }
    return found;
  }
	
  void printList(){
	  mTemp = mHead;
    while(mTemp->m_next){
      std::cout<<mTemp->m_data<<" ";
      mTemp = mTemp->m_next;
    }
    std::cout<<mTemp->m_data<<std::endl;
  }
  
private:
  

protected:

};



#endif
