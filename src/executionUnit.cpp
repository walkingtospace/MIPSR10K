#include "executionUnit.h"

ExecutionUnit::ExecutionUnit() {}
ExecutionUnit::~ExecutionUnit() {}

bool ExecutionUnit::m_isClean() {
	
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