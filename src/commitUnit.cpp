#include "commitUnit.h"

CommitUnit::CommitUnit() {}
CommitUnit::~CommitUnit() {}

void CommitUnit::m_getActivelist(ActiveList* ptr) {
	al_ptr = ptr;
}

void CommitUnit::m_transmit(Instruction input) { //branch, shift priority
	ins.push_back(input);
	//input.m_printPipeline();
}


bool CommitUnit::m_isClean() {
	if(ins.size() != 0) {

		return false;
	} else {

		return true;
	}
};

bool CommitUnit::m_getEnable() {
	return true;
}

void CommitUnit::m_setNextEnable(bool result) {
	nextEnable = result;
}

void CommitUnit::m_calc() {

	cout<<al_ptr->ArchReg<<"  "<<al_ptr->DestReg<<endl;

	nextEnable = false;
}

void CommitUnit::m_edge() { //already checked queus is available
	if(nextEnable == true) {
	
	} else {

	}
}