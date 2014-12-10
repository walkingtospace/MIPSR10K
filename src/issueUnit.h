#pragma once

#include "common.h"
#include "module.h"
#include "instruction.h"
#include "executionUnit.h"

class IssueUnit : public Module {
public:
	queue<Instruction> ins;
	list<Instruction> FPQueue;
	list<Instruction> AddressQueue;
	list<Instruction> IntegerQueue;
	int registerFile[32];
	int* busyTable_ptr;

	//RegisterFile* rf //useless. because this is simulator, not real calculator
	ExecutionUnit* eu;

	IssueUnit(ExecutionUnit* eu);
	~IssueUnit();
	bool m_transmit(Instruction input);
	void m_getBusyTable(int* bt_ptr);

	bool m_isClean();
	bool m_getEnable();
	void m_setNextEnable(bool result);
	void m_calc();
	void m_edge();
};