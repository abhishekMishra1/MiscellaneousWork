/***************************************************************************************************************************************************************
* FILE: Coordinate.h                                                                                                                                           *
* DESC:                                                                                                                                                        *
* AUTH:                                                                                                                                                        *
***************************************************************************************************************************************************************/


#ifndef _COORDINATE_H_
#define _COORDINATE_H_
class Coordinate{
public:
	Coordinate():m_Position(0){}
	Coordinate(int Position):m_Position(Position){}
	~Coordinate(){}
	
	int GetPosition(){return m_Position;}
	void SetPosition(int position)
	{
		m_Position = position;
	}
private:

protected:
	int m_Position;

};

#endif
