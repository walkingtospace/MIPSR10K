#include "issueUnit.h"

IssueUnit::IssueUnit(ExecutionUnit* input) {
	busyTable_ptr = NULL;
	eu = eu;

	for(int i=0; i<32; ++i) { //32 is REGISTERFILE SIZE
		registerFile[i] = 0;
	}
}
IssueUnit::~IssueUnit() {}

bool IssueUnit::m_transmit(Instruction input) {
	ins.push(input);

	return true;
}

void IssueUnit::m_getBusyTable(int* bt_ptr) {
	busyTable_ptr = bt_ptr;
}


bool IssueUnit::m_isClean() {
	if(FPQueue.size() == 0 && AddressQueue.size() == 0 && IntegerQueue.size() == 0) {

		return true;
	} else {

		return false;
	}
};

bool IssueUnit::m_getEnable() {

	return true;
}

void IssueUnit::m_setNextEnable(bool result) {
	nextEnable = result;
}


void IssueUnit::m_calc() {
	int size = ins.size();

	for(int i=0; i<size ; ++i) {
		Instruction insItem = ins.front();
		ins.pop();

		if(insItem.m_getOp() == INTEGER || insItem.m_getOp() == BRANCH) {
			IntegerQueue.push_back(insItem);
		} else if(insItem.m_getOp() == ADDFP || insItem.m_getOp() == MULTIFP ) {
			FPQueue.push_back(insItem);
		} else if(insItem.m_getOp() == LOAD || insItem.m_getOp() == STORE ) {
			AddressQueue.push_back(insItem);
		}
	}

	//check ALU1, ALU2,  Address calc, FPadder FPMultiplier
	//check operands are available


	nextEnable = true;
}

void IssueUnit::m_edge() {
	if(nextEnable == true) {
		


	} else {
		//stall
	}
}