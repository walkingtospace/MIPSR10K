#pragma once

#include "common.h"
#include "module.h"
#include "instruction.h"

class IssueUnit : public Module {
public:
	queue<Instruction> ins;
	list<Instruction> FPQueue;
	list<Instruction> AddressQueue;
	list<Instruction> IntegerQueue;
	int registerFile[32];

	IssueUnit();
	~IssueUnit();
	bool m_transmit(Instruction input);

	bool m_isClean();
	bool m_getEnable();
	void m_setNextEnable(bool result);
	void m_calc();
	void m_edge();
};