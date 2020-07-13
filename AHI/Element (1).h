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

		