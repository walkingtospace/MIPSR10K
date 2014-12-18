#pragma once

#include "common.h"
#include "module.h"
#include "commitUnit.h"
#include "issueUnit.h"
#include "BranchUnit.h"

class IssueUnit; //forward referencing for IU
class ExecutionUnit : public Module {
public:
	queue<Instruction> ALU1; //size == 1
	queue<Instruction> ALU2; //size == 1
	queue<Instruction> AddressUnit; //size == 1
	Instruction FPAdder[3]; //support pipeline
	Instruction FPMultiplier[3]; //support pipeline
	

	bool isMispredicted;
	int branchId;
	int FPAdder_ptr;
	int FPAdder_cnt;
	int FPMultiplier_ptr;
	int FPMultiplier_cnt;
	int* busyTable_ptr;
	vector<ActiveList>* al_ptr;
	CommitUnit* cu;
	IssueUnit* iu;
	BranchUnit* bu;

	ExecutionUnit(CommitUnit* cu, BranchUnit* bu);
	~ExecutionUnit();

	void m_setActiveDonebit(int bit, int activeTag);
	void m_getRefToActivelist(vector<ActiveList>* al_ptr);
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
	void m_writeBackToRF(int phyReg);
	void m_getIUInstance(IssueUnit* iu);
	bool m_isMispredicted();
	void m_setMispredicted(bool value);
	int m_getBranchId();

	bool m_isClean();
	bool m_getEnable();
	void m_setNextEnable(bool result);
	void m_calc();
	void m_edge();
};
