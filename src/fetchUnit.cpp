#include "fetchUnit.h"

FetchUnit::FetchUnit(DecodeUnit* input) {
	du = input;
}

FetchUnit::~FetchUnit() {}


bool FetchUnit::pushInstructions(Instruction input) {
	try {
		ins.push(input);
	} catch(exception e) {
		cout<<"exception from FetchUnit.pushInstructions() : "<<endl;

		return false;
	}
	
	return true;
}

bool FetchUnit::m_isClean() {
	if(ins.size() != 0) {

		return false;
	} else {

		return true;
	}
};

bool FetchUnit::m_getEnable() {
	if(ins.size() < INT_MAX) {

		return true;
	} else {

		return false;
	}	
}

void FetchUnit::m_setNextEnable(bool result) {
	nextEnable = result;
}

void FetchUnit::m_calc() {
	m_setNextEnable(du->m_getEnable()); //check if decodeunit's ins buffer is full or not
}

void FetchUnit::m_edge() {
	if(nextEnable == true && ins.size() > 0) {
		Instruction temp = ins.front();

		temp.m_setPipelineLog("F");
		du->m_transmit(temp);
		ins.pop();
	} else {
		//stall
	}
}