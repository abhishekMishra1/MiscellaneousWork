/***************************************************************************************************************************************************************
* FILE: ThreeDCoordinates.h                                                                                                                                       *
* DESC:                                                                                                                                                        *
* AUTH:                                                                                                                                                        *
***************************************************************************************************************************************************************/


#ifndef _THREEDCOORDINATES_H_
#define _THREEDCOORDINATES_H_
#include "Coordinate.h"

class ThreeDCoordinates
{
public:

	ThreeDCoordinates():
	m_X(0)
	, m_Y(0)
	, m_Z(0)
	{}

	ThreeDCoordinates(int x, int y, int z):
	m_X(x)
	, m_Y(y)
	, m_Z(z)
	{}

	ThreeDCoordinates GetCoordinates(){ return *this;}
	void GetCoordinates(int& x, int& y, int& z)
	{
		x = m_X.GetPosition();
		y = m_Y.GetPosition();
		z = m_Z.GetPosition();
	}
	
	void SetCoordinates(int x, int y, int z)
	{
		m_X.SetPosition(x);
		m_Y.SetPosition(y);
		m_Z.SetPosition(z);
	}



private:

protected:
	Coordinate m_X;
	Coordinate m_Y;
	Coordinate m_Z;
};

#endif
