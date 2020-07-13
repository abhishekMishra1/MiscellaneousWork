/***************************************************************************************************************************************************************
* FILE: event.hpp                                                                                                                                              *
* DESC:                                                                                                                                                        *
* AUTH:                                                                                                                                                        *
***************************************************************************************************************************************************************/


#ifndef _EVENT_HPP_
#define _EVENT_HPP_

#include<string>
#include"registerTable.hpp"

namespace EventSpace{
enum priority_e{
	HIGH,
	MID,
	LOW
	};
	


class Event{
	public:
	private:
		priority mPrio;
		registerTable *mSourceAddr;
		registerTable *mDestinationAddr;
		string mInfo;
	protected

	};


}
#endif
