#include "executionUnit.h"

ExecutionUnit::ExecutionUnit() {
	FPMultiplier_cnt = 0;
	FPAdder_cnt = 0;

	for(int i=0; i<FPADDER_SIZE ; ++i) {
		for(int j=0; j<FPADDER_SIZE ; ++j) {
			Instruction emptyIns;
			FPAdder[i][j] = emptyIns;
			FPMultiplier[i][j] = emptyIns;
		}
	}

}
ExecutionUnit::~ExecutionUnit() {}

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
	if(FPAdder_cnt < FPADDER_SIZE) {

		return false;
	}

	return true;

}

bool ExecutionUnit::m_isMultiplierFull() {
	if(FPMultiplier_cnt < FPMULTIPLIER_SIZE) {

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
	FPAdder[FPAdder_cnt++][0] = ins;
}

void ExecutionUnit::m_transmitToFPMultiplier(Instruction ins) {
	FPMultiplier[FPMultiplier_cnt++][0] = ins;
	
	for(int i=0; i<REGISTER_SIZE ; ++i) {
		cout<<busyTable_ptr[i]<<" ";
	}

	cout<<"!!"<<endl;
}

void ExecutionUnit::m_getBusyTable(int* bt_ptr) {
	busyTable_ptr = bt_ptr;
}


bool ExecutionUnit::m_isClean() {
	if((FPMultiplier_cnt == 0) && (FPAdder_cnt == 0) && !m_isAddressUnitFull() && !m_isALU1Full() && !m_isALU2Full()) {
		
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


	nextEnable = true;
}

void ExecutionUnit::m_edge() {
	if(nextEnable == true) {
		


	} else {
		//stall
	}
}