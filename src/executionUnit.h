#pragma once

#include "common.h"
#include "module.h"
#include "instruction.h"

class ExecutionUnit : public Module {
public:
	queue<Instruction> ALU1; //size == 1
	queue<Instruction> ALU2; //size == 1
	queue<Instruction> AddressUnit; //size == 1
	Instruction FPAdder[FPADDER_SIZE][FPADDER_SIZE]; //support pipeline
	Instruction FPMultiplier[FPADDER_SIZE][FPADDER_SIZE]; //support pipeline
	
	int FPAdder_cnt;
	int FPMultiplier_cnt;
	int* busyTable_ptr;

	ExecutionUnit();
	~ExecutionUnit();

	bool m_isALU1Full();
	bool m_isALU2Full();
	bool m_isAddressUnitFull();
	bool m_isAdderFull();
	bool m_isMultiplierFull();

	void m_transmitToALU1(Instruction ins); //branch, shift priority
	void m_transmitToALU2(Instruction ins); 
	void m_transmitToAddressUnit(Instruction ins); //for load/store
	void m_transmitToFPAdder(Instruction ins);
	void m_transmitToFPMultiplier(Instruction ins);

	void m_getBusyTable(int* bt_ptr);

	bool m_isClean();
	bool m_getEnable();
	void m_setNextEnable(bool result);
	void m_calc();
	void m_edge();
};