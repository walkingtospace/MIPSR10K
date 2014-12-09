#include "issueUnit.h"

IssueUnit::IssueUnit() {
	for(int i=0; i<32; ++i) { //32 is REGISTERFILE SIZE
		registerFile[i] = 0;
	}
}
IssueUnit::~IssueUnit() {}

bool IssueUnit::m_transmit(Instruction input) {
	ins.push(input);
	/*
	deque<string> temp = input.m_getPipelineLog();
	
	int size = temp.size();
	for(int j=0; j<input.m_getId() ; ++j) cout<<"  ";
	for(int i=0; i< size; ++i) {
		cout<<temp.front()<<" ";
		temp.pop_front();
	}
	cout<<endl;
	*/

	return true;
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
	nextEnable = false;

}

void IssueUnit::m_edge() {
	if(nextEnable == true) {
		//trasmit
		innerEnable = true;
	} else {
		//stall
	}
}