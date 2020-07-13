/***************************************************************************************************************************************************************
* FILE: NodeTable.h                                                                                                                                            *
* DESC:                                                                                                                                                        *
* AUTH:                                                                                                                                                        *
***************************************************************************************************************************************************************/


#ifndef _NODETABLE_H_
#define _NODETABLE_H_

#include <vector>
#include "ThreeDNode.h"

class NodeTable{
public:
	void GenerateRandomPoints(int howMany, int coordinateRange);

	void DisplayData();
	
private:
	void AddNewEntry(ThreeDNode<char>* val);

	int randomGeneration(int range=0);

protected:
	std::vector<ThreeDNode<char>*>	m_vTable;

};

#endif
