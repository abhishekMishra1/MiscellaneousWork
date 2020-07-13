/***************************************************************************************************************************************************************
* FILE: registerTable.hpp                                                                                                                                      *
* DESC:                                                                                                                                                        *
* AUTH:                                                                                                                                                        *
***************************************************************************************************************************************************************/


#ifndef _REGISTERTABLE_HPP_
#define _REGISTERTABLE_HPP_

#include"server.hpp"
#include"client.hpp"

namespace registrationSpace{

	enum registrationType_e{
		SENDER,
		RECEIVER,
		BOTH
	};

	enum registrationError_e{
		NO_ERROR,
		INSERTION_FAILURE,
		NOT_FOUND_IN_REGISTER,
		MORE_THAN_ONE_ADDRESS,
	};
	
	class registry{
		//a dummy class to provide a proper linkage for all types of classes used in client server model.
		//need to inherit to those class who would participate in event creation.
		//This class will provide a single way to maintain the registration record.
	};


	class RegisterTable{

	public:
		static RegisterTable *mRegTable;
		static RegisterTable* getInstance();
		registrationError_e registerNewAddress(registry*, registrationType_e);
		registrationError_e lookupAddress(registry*, registrationType_e &where);
	private:
		std::vector<registry*> mSender;
		std::vector<registry*> mReceiver;
		std::vector::iterator mItr;
		

		RegisterTable();
		RegisterTable( const RegisterTable&){}
		RegisterTable& operator=(const RegisterTable&){}
		~RegisterTable();
	protected:

	};

}
#endif
