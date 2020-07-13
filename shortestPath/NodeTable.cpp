/***************************************************************************************************************************************************************
* FILE: NodeTable.cpp                                                                                                                                          *
* DESC:                                                                                                                                                        *
* AUTH:                                                                                                                                                        *
***************************************************************************************************************************************************************/


#include"NodeTable.h"
#include <iostream>
using namespace std;

int NodeTable::randomGeneration(int range)
{
	int randomNumber = 0;
	/* initialize random seed: */
	srand(time(NULL));
	if(range)
		randomNumber = rand()%range;
	else
		randomNumber = rand();

	return randomNumber;
}

void NodeTable::AddNewEntry(ThreeDNode<char>* val)
{
	m_vTable.push_back(val);
}


void NodeTable::GenerateRandomPoints(int howMany, int coordinateRange)
{
	int x, y, z;
	std::vector<std::string> vNames;
	vNames.push_back("Abhishek");
	vNames.push_back("Mishra");
	vNames.push_back("is");
	vNames.push_back("a");
	vNames.push_back("Software");
	vNames.push_back("Engineer");
	vNames.push_back("in");
	vNames.push_back("a");
	vNames.push_back("small");
	vNames.push_back("software");
	vNames.push_back("company");
	
	for(int i = 0; i < 10; i++)
	{
		x = randomGeneration(coordinateRange);
		y = randomGeneration(coordinateRange);
		z = randomGeneration(coordinateRange);
		const std::string szName = vNames[i].c_str();
		AddNewEntry(new ThreeDNode<char>(x,y,z, szName.c_str());
	}
}

void NodeTable::DisplayData()
{
	cout<<"Data Field           Coordinates\n";
	cout<<"                     x   y   z  \n";
	int x, y, z;
	for(int i = 0; i < m_vTable.size(); i++)
	{
		m_vTable[i].GetCoordinates(x,y,z);
		cout<<m_vTable[i].GetData();
		cout<<"           ";
		cout<<x<<" "<<y<<" "<<z<<endl;
	}
}
