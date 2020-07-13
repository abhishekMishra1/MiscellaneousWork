/***************************************************************************************************************************************************************
* FILE: ThreeDNode.h                                                                                                                                               *
* DESC:                                                                                                                                                        *
* AUTH:                                                                                                                                                        *
***************************************************************************************************************************************************************/


#ifndef _THREEDNODE_H_
#define _THREEDNODE_H_

#include "INode.h"
#include "ThreeDCoordinates.h"
#include<stdlib.h>

template <class T>
class ThreeDNode: public INode<T>
{
public:
	ThreeDNode(int x=0, int y=0, int z=0, T* data=0):
		INode<T>(0,0,data)
		, m_Coordinates(x, y, z)
	{
		//m_Coordinates.SetCoordinates(x, y, z);
	}
		
	
private:

protected:
	ThreeDCoordinates m_Coordinates;	

};

#endif
