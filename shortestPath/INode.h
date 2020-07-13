/***************************************************************************************************************************************************************
* FILE: INode.h                                                                                                                                                *
* DESC: Generic Node class for all types of Nodes                                                                                                              *
* AUTH: Abhishek Mishra                                                                                                                                        *
***************************************************************************************************************************************************************/


#ifndef _INODE_H_
#define _INODE_H_

template <class T>
class INode{
public:

	INode(INode* pNext=0, INode* pPrev=0, T* data=0):
		m_pNext(pNext)
		, m_pPrev(pPrev)
		, m_pData(data)
	{}

	INode* GetNextNode()
	{
		return m_pNext;
	}

	INode* GetPrevNode()
	{
		return m_pPrev;
	}

	T* GetData()
	{
		return m_pData;
	}

private:

protected:

	INode* m_pNext;
	INode* m_pPrev;

	T*	   m_pData;
	
};

#endif
