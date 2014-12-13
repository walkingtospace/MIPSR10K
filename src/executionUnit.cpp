#include "executionUnit.h"

ExecutionUnit::ExecutionUnit(CommitUnit* cu_ptr) {
	FPAdder_cnt = 0;
	FPAdder_ptr = 0;
	FPMultiplier_cnt = 0;
	FPMultiplier_ptr = 0;

	for(int i=0; i<FPADDER_SIZE ; ++i) {
		Instruction emptyIns;
		FPAdder[i] = emptyIns;
		FPMultiplier[i] = emptyIns;
	}

	cu = cu_ptr;
}

ExecutionUnit::~ExecutionUnit() {}


void ExecutionUnit::m_setActiveDonebit(int bit, int activeTag) {
	int alSize = al_ptr->size();
	for(int i=0; i< alSize ; i++) {
		if( al_ptr->at(i).activeTag == activeTag) {
			al_ptr->at(i).m_setDonebit(bit);
			
		}
	}
}

void ExecutionUnit::m_getRefToActivelist(vector<ActiveList>* al) {
	al_ptr = al;
}

bool ExecutionUnit::m_isALU1Full() {
	if(ALU1.empty()) {

		return false;
	}

	return true;
}

bool ExecutionUnit::m_isALU2Full() {

	if(ALU2.empty()) {

		return false;
	}

	return true;

}

bool ExecutionUnit::m_isAddressUnitFull() {
	if(AddressUnit.empty()) {

		return false;
	}

	return true;

}

bool ExecutionUnit::m_isAdderFull() {
	if(FPAdder_ptr == 0) {

		return false;
	}

	return true;

}

bool ExecutionUnit::m_isMultiplierFull() {
	if(FPMultiplier_ptr == 0) {

		return false;
	}

	return true;
}

void ExecutionUnit::m_transmitToALU1(Instruction ins) { //branch, shift priority
	ALU1.push(ins);
}

void ExecutionUnit::m_transmitToALU2(Instruction ins) {
	ALU2.push(ins);
}

void ExecutionUnit::m_transmitToAddressUnit(Instruction ins) { //for load/store
	AddressUnit.push(ins);
}

void ExecutionUnit::m_transmitToFPAdder(Instruction ins) {
	FPAdder[FPAdder_ptr] = ins;
	FPAdder_cnt++;
}

void ExecutionUnit::m_transmitToFPMultiplier(Instruction ins) {
	FPMultiplier[FPMultiplier_ptr] = ins;
	FPMultiplier_cnt++;
}

void ExecutionUnit::m_getBusyTable(int* bt_ptr) {
	busyTable_ptr = bt_ptr;
}

void ExecutionUnit::m_writeBackToRF(int phyReg) {
	busyTable_ptr[phyReg] = 0;
}

bool ExecutionUnit::m_isClean() {
	if(FPAdder_cnt == 0 && FPMultiplier_cnt == 0 && !m_isAddressUnitFull() && !m_isALU1Full() && !m_isALU2Full()) {
		
		return true;
	}

	return false;
};

bool ExecutionUnit::m_getEnable() {

	return true;
}

void ExecutionUnit::m_setNextEnable(bool result) {
	nextEnable = result;
}

void ExecutionUnit::m_calc() {

}

void ExecutionUnit::m_edge() {
		if(ALU1.empty() == false) { //branch or Integer
		Instruction temp = ALU1.front();
		ALU1.pop();

		temp.m_setPipelineLog("E");

		if(temp.m_getOp() == BRANCH) {

		} else if(temp.m_getOp() == INTEGER) {
			m_writeBackToRF(temp.m_getPd()); //set busytable[phyReg] as 0
			m_setActiveDonebit(1, temp.m_getActivelistNum());

			cu->m_transmit(temp);
		}
	}

	if(ALU2.empty() == false) {
		Instruction temp = ALU2.front();
		ALU2.pop();

		temp.m_setPipelineLog("E");

		if(temp.m_getOp() == BRANCH) {

		} else if(temp.m_getOp() == INTEGER) {
			m_writeBackToRF(temp.m_getPd()); //set busytable[phyReg] as 0
			m_setActiveDonebit(1, temp.m_getActivelistNum());

			cu->m_transmit(temp);
		}
	}

	if(AddressUnit.empty() == false) {
		if(AddressUnit.size() == 1) {
			Instruction temp = AddressUnit.front(); //copy to simulate pipeline
			
			temp.m_setPipelineLog("A");
			AddressUnit.push(temp);
		} else if(AddressUnit.size() == 2) {
			AddressUnit.pop(); //throw away the first one

			Instruction temp = AddressUnit.front();
			AddressUnit.pop();
	
			temp.m_setPipelineLog("E");

			//m_writeBackToRF(temp.m_getPd()); //writeback
			m_setActiveDonebit(1, temp.m_getActivelistNum());

			cu->m_transmit(temp);
		}
	}

	if(FPAdder_cnt > 0) { //rightshift
		FPAdder[0].m_setPipelineLog("E");
		FPAdder[1].m_setPipelineLog("E");
		FPAdder[2].m_setPipelineLog("F");

		Instruction dummy;
		Instruction temp = FPAdder[2];

		FPAdder[2] = FPAdder[1];
		FPAdder[1] = FPAdder[0];
		FPAdder[0] = dummy;

		if(temp.m_getOp() == DUMMY_INSTRUCTION) {
			//empty instruction
		} else {
			FPAdder_ptr = 0;
			FPAdder_cnt--;

			m_writeBackToRF(temp.m_getPd()); //writeback
			m_setActiveDonebit(1, temp.m_getActivelistNum());

			cu->m_transmit(temp);
		}
	}

	if(FPMultiplier_cnt > 0) { //rightshift
		FPMultiplier[0].m_setPipelineLog("E");
		FPMultiplier[1].m_setPipelineLog("E");
		FPMultiplier[2].m_setPipelineLog("F");

		Instruction dummy;
		Instruction temp = FPMultiplier[2];

		FPMultiplier[2] = FPMultiplier[1];
		FPMultiplier[1] = FPMultiplier[0];
		FPMultiplier[0] = dummy;

		if(temp.m_getOp() == DUMMY_INSTRUCTION) {
			//empty instruction
		} else {
			FPMultiplier_ptr = 0;
			FPMultiplier_cnt--;

			m_writeBackToRF(temp.m_getPd()); //writeback
			m_setActiveDonebit(1, temp.m_getActivelistNum());

			cu->m_transmit(temp);
		}
	}
}