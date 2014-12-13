#pragma once

#include "common.h"
#include "module.h"
#include "instruction.h"
#include "activelist.h"

class CommitUnit : public Module { //commit should be done in order by referring to active list
public:
	vector<Instruction> result;
	queue<Instruction> ins;
	queue<int>* fl_ptr;
	vector<ActiveList>* al_ptr;
	int* busyTable_ptr;

	CommitUnit();
	~CommitUnit();

	void m_transmit(Instruction input);
	void m_getRefToActivelist(vector<ActiveList>* al_ptr);
	void m_getRefToFreelist(queue <int>* freeList);
	vector<Instruction> m_dumpInstructions();
	void m_getBusyTable(int* bt_ptr);
	void m_writeBackToRF(int phyReg);


	bool m_isClean();
	bool m_getEnable();
	void m_setNextEnable(bool result);
	void m_calc();
	void m_edge();
};