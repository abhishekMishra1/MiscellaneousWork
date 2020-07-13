#include "Element.h"
#include <iostream>



Trie::Trie()
{
	m_pHead = new Node;
	for(char ch = 'a', int i = 0; i < 26; i++, ch++)
	{
		m_pHead->m_szInfo = ch;
		m_nConnections++;
	}
/*
	1. Fetch 1st char to match the trie branch
	2. If not exist, create new Connection and add whole info there
	3. If doesn't exist, fetch next char from info.
	4. Sink one step deep in tree and try to fetch the char with in point 3.
	5. Repeat from 2 till all characters added to trie
*/

void Trie::AddToTrie(std::String& info)
{
	if(!m_pHead)
	{
		cout<<"Seems to be born just now. Initializing the data...";
		createNode();
	}

	if(m_pHead && m_pHead->GetConnectionCounts() == HEAD_MAX_CONNECTIONS)
	{
		cout<<"Already limit reached for top entry\n";
	}	
}

void Trie::createNode()
{
	m_pHead = new Node;
	for(int i = 0; i < HEAD_MAX_CONNECTIONS; i++)
	{
		m_pWorkerNode = new Node;
		std::String sz;
		char ch = 'a';
		sz << ch;
		ch++;
		m_pHead->m_mLinkedNodes.push_back(m_pWorkerNode);
		m_nConnections++;
	}
	
	assert(m_nConnections <= HEAD_MAX_CONNECTIONS);
}

	
