#include "issueUnit.h"

IssueUnit::IssueUnit(ExecutionUnit* input) {
	busyTable_ptr = NULL;
	eu = input;
}

IssueUnit::~IssueUnit() {}

bool IssueUnit::m_transmit(Instruction input) {
	ins.push_back(input);

	return true;
}

void IssueUnit::m_getBusyTable(int* bt_ptr) {
	busyTable_ptr = bt_ptr;
}

void IssueUnit::m_putStall() {
	int size = IntegerQueue.size();

	for(int i=0; i<size; ++i) {
		Instruction item = IntegerQueue.front();
		IntegerQueue.pop_front();

		item.m_setPipelineLog("S");

		IntegerQueue.push_back(item);
	}

	size = FPQueue.size();
	for(int i=0; i<size; ++i) {
		Instruction item = FPQueue.front();
		FPQueue.pop_front();

		item.m_setPipelineLog("S");

		FPQueue.push_back(item);
	}

	size = AddressQueue.size();
	for(int i=0; i<size; ++i) {
		Instruction item = AddressQueue.front();
		AddressQueue.pop_front();

		item.m_setPipelineLog("S");

		AddressQueue.push_back(item);
	}
}

bool IssueUnit::m_busyTableCheck(int phyRegNum) {
	if(busyTable_ptr[phyRegNum] == 0) {

		return true;
	}

	return false;
}

bool IssueUnit::m_isClean() {
	if(ins.size() == 0 && FPQueue.size() == 0 && AddressQueue.size() == 0 && IntegerQueue.size() == 0) {

		return true;
	} else {

		return false;
	}
};

bool IssueUnit::m_getEnable() {
	if(FPQueue.size() >= QUEUE_SIZE || AddressQueue.size() >= QUEUE_SIZE && IntegerQueue.size() >= QUEUE_SIZE) {

		return false;
	}

	return true;
}

void IssueUnit::m_setNextEnable(bool result) {
	nextEnable = result;
}


void IssueUnit::m_calc() {
	int size = ins.size();

	for(int i=0; i<size ; ++i) {
		Instruction insItem = ins.front();
		ins.pop_front();

		if(insItem.m_getOp() == INTEGER || insItem.m_getOp() == BRANCH) {
			IntegerQueue.push_back(insItem);
		} else if(insItem.m_getOp() == ADDFP || insItem.m_getOp() == MULTIFP ) {
			FPQueue.push_back(insItem);
		} else if(insItem.m_getOp() == LOAD || insItem.m_getOp() == STORE ) {
			AddressQueue.push_back(insItem);
		}
	}

	nextEnable = true;
}

/*******************************need refactoring later*******************************/
void IssueUnit::m_edge() {
	eu->m_getBusyTable(busyTable_ptr);

	if(!eu->m_isALU1Full()) { //check next unit is available
		int size = IntegerQueue.size(); 	//branch priority
		bool isTransmitted = false;

		for(int i=0; i<size; ++i) {
			Instruction temp = IntegerQueue.front();
			IntegerQueue.pop_front();

			if(temp.m_getOp() == BRANCH) {
				if(m_busyTableCheck(temp.m_getPs()) == true && m_busyTableCheck(temp.m_getPt()) == true) {
					temp.m_setPipelineLog("I");

					eu->m_transmitToALU1(temp);
					isTransmitted = true;

					break;
				} else {
					IntegerQueue.push_back(temp);
				}
			} else {
				IntegerQueue.push_back(temp);
			}
		}//end for

		if(isTransmitted == false) { //not found independent branch yet
			size = IntegerQueue.size();

			for(int i=0; i<size; ++i) {
				Instruction temp = IntegerQueue.front();
				IntegerQueue.pop_front();

				if(temp.m_getOp() == INTEGER) {
					if(m_busyTableCheck(temp.m_getPs()) == true && m_busyTableCheck(temp.m_getPt()) == true ) {
						temp.m_setPipelineLog("I");

						eu->m_transmitToALU1(temp);
						isTransmitted = true;

						break;
					} else {
						IntegerQueue.push_back(temp);
					}
				} else {
					IntegerQueue.push_back(temp);
				}
			}
		}
	} //end if 
	
	if(!eu->m_isALU2Full()) {
		int size = IntegerQueue.size();

		for(int i=0; i<size; ++i) {
			Instruction temp = IntegerQueue.front();
			IntegerQueue.pop_front();

			if(m_busyTableCheck(temp.m_getPs()) == true && m_busyTableCheck(temp.m_getPt()) == true) {
				temp.m_setPipelineLog("I");

				eu->m_transmitToALU2(temp);

				break;
			} else {
				IntegerQueue.push_back(temp);
			}
		}
	} 
	
	if(!eu->m_isAddressUnitFull()) {
		if(AddressQueue.size() > 0) {
			Instruction temp = AddressQueue.front();
			AddressQueue.pop_front();

			if(m_busyTableCheck(temp.m_getPs()) == true && m_busyTableCheck(temp.m_getPt()) == true) {
				temp.m_setPipelineLog("I");

				eu->m_transmitToAddressUnit(temp);
			} else {
				AddressQueue.push_back(temp);
			}
		}
	} 
	
	if(!eu->m_isAdderFull()) {
		int size = FPQueue.size();

		for(int i=0; i<size; ++i) {
			Instruction temp = FPQueue.front();
			FPQueue.pop_front();

			if(temp.m_getOp() == ADDFP && m_busyTableCheck(temp.m_getPs()) == true && m_busyTableCheck(temp.m_getPt()) == true) {
				temp.m_setPipelineLog("I");
				eu->m_transmitToFPAdder(temp);

				break;
			} else {
				FPQueue.push_back(temp);
			}  
		} //end for
	}

	if(!eu->m_isMultiplierFull()) {
		int size = FPQueue.size();

		for(int i=0; i<size; ++i) {
			Instruction temp = FPQueue.front();
			FPQueue.pop_front();
			
			if(temp.m_getOp() == MULTIFP && m_busyTableCheck(temp.m_getPs()) == true && m_busyTableCheck(temp.m_getPt()) == true) {
				temp.m_setPipelineLog("I");
				eu->m_transmitToFPMultiplier(temp);

				break;
			} else {
				FPQueue.push_back(temp);
			}  
		} //end for
	} 
	
	m_putStall(); //the other instructions left in the queues are all stalled
}