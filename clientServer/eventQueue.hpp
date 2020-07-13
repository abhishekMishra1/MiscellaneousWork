/***************************************************************************************************************************************************************
* FILE: eventQueue.hpp                                                                                                                                         *
* DESC:                                                                                                                                                        *
* AUTH:                                                                                                                                                        *
***************************************************************************************************************************************************************/


#ifndef _EVENTQUEUE_HPP_
#define _EVENTQUEUE_HPP_

#include"event.hpp"
#include<queue>

class EventQueue{
public:
	virtual void pushEvent(event *ev);
	virtual Event* popEvent();	
private:
	std::queue<Event *>eventQ;
protected:
	
};


#endif
