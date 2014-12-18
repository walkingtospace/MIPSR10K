#pragma once

#include "common.h"
#include "module.h"
#include "stack.h"
#include "instruction.h"
#include "activelist.h"

class BranchUnit {
public:

	Stack branchStack[BRANCH_STACK_SIZE];
	int stackcnt;	


	BranchUnit();
	~BranchUnit();

	Stack m_getStatus();
	int m_size();
	void m_pop(string mask);
	bool m_isStackFull();
	void m_pushStatus(int* mapTable, int* busyBitTable, int activeListNum, deque <Instruction> ins, queue <int> freeList, vector<ActiveList> activeList, string mask);

};