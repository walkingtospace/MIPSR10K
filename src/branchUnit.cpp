#include "BranchUnit.h"

BranchUnit::BranchUnit() {
	stackcnt = 0;
}
BranchUnit::~BranchUnit() {}

bool BranchUnit::m_isStackFull() {
	if(stackcnt >= BRANCH_STACK_SIZE) {

		return true;
	} 

	return false;
}

void BranchUnit::m_pushStatus(int* mapTable, int* busyBitTable, int activeListNum, deque <Instruction> ins, queue <int> freeList, vector<ActiveList> activeList, string mask) {
	for(int i=0; i<REGISTER_SIZE ; ++i) {
		branchStack[stackcnt].mapTable[i] = mapTable[i];
	}

	for(int i=0; i<FREELIST_SIZE ; ++i) {
		branchStack[stackcnt].busyBitTable[i] = busyBitTable[i];
	}

	branchStack[stackcnt].mask = mask;
	branchStack[stackcnt].activeListNum = activeListNum;
	branchStack[stackcnt].ins = ins;
	branchStack[stackcnt].freeList = freeList;
	branchStack[stackcnt].activeList = activeList;

	stackcnt++;
}

Stack BranchUnit::m_getStatus() { 
	Stack empty;

	if(stackcnt <= 0) {
		cout<<"branch stack is empty"<<endl;

		return empty;
	}

	stackcnt--;

	return branchStack[stackcnt];
}

int BranchUnit::m_size() {

	return stackcnt;
}

void BranchUnit::m_pop(string mask) {
	int size = stackcnt;

	for(int i=0; i<size ; ++i) {
		if(branchStack[i].mask == mask) {
			for(int j=i; j<size-1 ; ++j) {
				branchStack[j] = branchStack[j+1];
			}

			break;
		}
	}
}