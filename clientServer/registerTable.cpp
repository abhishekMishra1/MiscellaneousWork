/***************************************************************************************************************************************************************
* FILE: registerTable.cpp                                                                                                                                      *
* DESC:                                                                                                                                                        *
* AUTH:                                                                                                                                                        *
***************************************************************************************************************************************************************/


#include"registerTable.hpp"

using namespace registrationSpace;

RegisterTable::RegisterTable(){
	if(!mRegTable)
		mRegTable = new RegisterTable;
	return mRegTable;
};

RegisterTable* RegisterTable::getInstance(){
	return mRegTable;
}

registrationError_e RegisterTable::registerNewAddress(registry *rg, registrationType_e tp){
	registrationError_e er = NO_ERROR;
	switch(tp){
		case SENDER:
			mSender.push(rg);
		break;

		case RECEIVER:
			mReceiver.push(rg);
		break;

		case BOTH:
		default:
			mSender.push(rg);
			mReceiver.push(rg);
		break;
	}
	
	return er;
}

registrationError_e RegisterTable::lookupAddress(registry*, registrationType_e &where){
	registrationError_e er = NO_ERROR;
	switch(tp){
		case SENDER:
			
		break;

		case RECEIVER:
			mRegTable->mReceiver.push(rg);
		break;

		case BOTH:
		default:
			mRegTable->mSender.push(rg);
			mRegTable->mReceiver.push(rg);
		break;
	}
	return er;
}
	

RegisterTable::~RegisterTable(){
	delete mRegTable;
	}
			


