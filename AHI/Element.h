#ifndef	_ELEMENT_H_
#define _ELEMENT_H_

#include <vector>
#include <map>
#include <string>
/*Element is having
	Field		Type			Size				Description
	Data		unsignedchar	1 byte				Stores the smallest element
	Connector	Element			100*SizeOf(Element)	Used to connecting with other elements
*/

class Element
{
	public:
		std::vector<Element*> 	m_vLinkedNodes;
		unsigned char			m_Data;
};

/*
	As we know, we can broadly categorize our communication methods and languages used.
	Languages: English, Hindi etc ...
	Numbers: 0-9
	
	Now considering only English language, we have 26 characters defined. So, we can have a language set of 26 characters. Out of this 26 character set, we can memorize an information by storing the index of the elements in the character set.
	- On retrieval, we can recreate the string by using the index. 
	- Storing index in a digit will require very less memory but time and cpu cycle will be consumed while evaluating the information. 
*/

/*
	Identity: Brain should have identity to get recognized uniquely
*/
class Brain
{
	public:
		void Memorize(std::String& info);	//Storing or remebering the information
		void Retrieve(std::String& info);	//Retrieving the information
	private:
		Element 							*m_pHead;
		Element 							*m_pElement;
		std::map<std::String, unsigned int>	m_vIndexers;
};
/*
	Memorization: This is an important part of this activity. Through this, brain will be able to learn about the surroundings and can start comparing, retrieve and decide based on the stored information.
				We all know that such information must be serialized so as save the information even if the system is dead.
	
	Serialization: Very important part of the brain. Main responsibilities are
		- Compact: If the serialized data is more compact, space issue won't occur. Faster processing can be achieved due to smaller data size.
		- Secure: Security is required so that no outer world can corrupt/play/exploit the information used by brain.
*/

/*
	Trie: A trie DS will help in managing the space economically and easy to retrieve. The behaviour of trie here will be little different. Only trie for those strings will be maintained or created which are existing or heard. Rest will be discarded.
*/

#define HEAD_MAX_CONNECTIONS	26

class Trie
{
	public:
		void AddToTrie(std::String& info);
		void RetrieveInfo(std::vector<std::String> info);
		Trie();
	private:
		ManageTrie();	//This function need to be called when you want to re-structurize the stored information properly as per standard.
		createNode();
	
	
	private:

		class Node
		{
			public:
				unsigned int getConnectionCounts(){return m_nConnections;}
				Node():m_szInfo(""), m_nConnections(0)
			public:
				std::vector<Node*> 		m_vLinkedNodes;
				char					m_szInfo;
				unsigned int			m_nConnections;
		};
		
		Node *m_pHead;
		Node *m_pWorker;
};