#pragma once

#include "common.h"
#include "module.h"
#include "executionUnit.h"
#include "instruction.h"

class ExecutionUnit;
class IssueUnit : public Module {
public:
	deque<Instruction> ins;
	list<Instruction> FPQueue;
	list<Instruction> AddressQueue;
	list<Instruction> IntegerQueue;
	int* busyTable_ptr;
	bool ALU1Enable;
	bool ALU2Enable;
	bool FPAdderEnable;
	bool FPMultiEnable;
	bool addressEnable;

	ExecutionUnit* eu;

	IssueUnit(ExecutionUnit* input);
	~IssueUnit();

	bool m_transmit(Instruction input);
	void m_getBusyTable(int* bt_ptr);
	void m_putStall();
	bool m_busyTableCheck(int phyRegNum);
	void m_flushQueues();

	bool m_isClean();
	bool m_getEnable();
	void m_setNextEnable(bool result);
	void m_calc();
	void m_edge();
};
