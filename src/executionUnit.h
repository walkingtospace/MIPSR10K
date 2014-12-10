#pragma once

#include "common.h"
#include "module.h"
#include "instruction.h"
#include "issueUnit.h"

class ExecutionUnit : public Module {
public:
	queue<Instruction> ALU1;
	queue<Instruction> ALU2;
	queue<Instruction> AddressUnit;
	Instruction FPAdder[2][2]; //support pipeline
	Instruction FPMultiplier[2][2]; //support pipeline
	
	int FPAdder_cnt;
	int FPMultiplier_cnt;

	ExecutionUnit();
	~ExecutionUnit();

	bool m_isALU1Full();
	bool m_isALU2Full();
	bool m_isAddressUnitFull();
	bool m_isAdderFull();
	bool m_isMultiplierFull();

	bool m_isClean();
	bool m_getEnable();
	void m_setNextEnable(bool result);
	void m_calc();
	void m_edge();
};