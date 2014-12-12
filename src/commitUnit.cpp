#include "commitUnit.h"

CommitUnit::CommitUnit() {}
CommitUnit::~CommitUnit() {}

void CommitUnit::m_getRefToActivelist(vector<ActiveList>* al) {
	al_ptr = al;
}

void CommitUnit::m_getRefToFreelist(queue <int>* freeList) {
	fl_ptr = freeList;
}

void CommitUnit::m_transmit(Instruction input) {
	ins.push(input);
}

vector<Instruction> CommitUnit::m_dumpInstructions() {

	return result;
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

}

//********************************* need refactoring later, or someday..*************************/
void CommitUnit::m_edge() {
/*
	int alSize = al_ptr->size();
	for(int i=0 ; i<alSize ; i++) {
		if(al_ptr->at(i).doneBit == 1) {
			cout<<al_ptr->at(i).activeTag<<" "<<al_ptr->at(i).DestReg<<" "<<al_ptr->at(i).doneBit<<endl;
		}
	}
	cout<<endl;
*/
	int size = ins.size();

	for(int i=0 ; i<size; ++i) {
		Instruction temp = ins.front();
		ins.pop();
		
		vector<ActiveList>::iterator it = al_ptr->begin();

		if(al_ptr->at(0).doneBit == 1 && temp.m_getActivelistNum() == al_ptr->at(0).activeTag) {
			fl_ptr->push(temp.m_getPd()); //release physical register	
			al_ptr->erase(it);

			temp.m_setPipelineLog("C");
			result.push_back(temp);
		} else {

			break;
		}
	}
}