#include "decodeUnit.h"

DecodeUnit::DecodeUnit(IssueUnit* input) {
	iu = input;
	activeListNum = 0;

	for(int i=0 ; i<REGISTER_SIZE ; ++i) { //32 is QUEUESIZE
		freeList.push(i);
		mapTable[i] = i;
	}

	for(int i=0; i<REGISTER_SIZE ; ++i) {
		busyBitTable[i] = 0;
	}
}

DecodeUnit::~DecodeUnit() {}

bool DecodeUnit::m_transmit(Instruction input) {
	ins.push_back(input);
	
	return true;
}

int DecodeUnit::m_getFreeList() {
	int reg = freeList.front();
	freeList.pop();

	return reg; 
}

int* DecodeUnit::m_transmitBusyTable() {

	return busyBitTable;
}


bool DecodeUnit::m_isClean() {
	if(ins.size() != 0) {

		return false;
	} else {

		return true;
	}
};

bool DecodeUnit::m_getEnable() {
	if(ins.size() < INSBUFFSIZE && innerEnable == true) {

		return true;
	} else {

		return false;
	}	
}

void DecodeUnit::m_setNextEnable(bool result) {
	nextEnable = result;
}

void DecodeUnit::m_calc() {
	if(activeListNum < REGISTER_SIZE && ins.size() > 0 && freeList.size() > 0 && iu->m_getEnable() == true) {
		Instruction input = ins.front();
		ins.pop_front();
	
		if(input.m_getOp() == INTEGER || input.m_getOp() == ADDFP || input.m_getOp() == MULTIFP || input.m_getOp() == LOAD) { //rs,rt,rd
			int rd = std::stoi(input.m_getRd(),nullptr,16); 
			int rs = std::stoi(input.m_getRs(),nullptr,16);
			int rt = std::stoi(input.m_getRt(),nullptr,16);
			int freeReg = m_getFreeList();
			int oldFreeReg =  mapTable[rd];

			busyBitTable[freeReg] = 1;
			mapTable[rd] = freeReg;
			ActiveList actItem(oldFreeReg, rd, 0); //dest, arch, doneBit

			input.m_setActivelistNum(activeListNum);
			input.m_setPd(freeReg);
			input.m_setPs(mapTable[rs]);
			input.m_setPt(mapTable[rt]);

			activeList[activeListNum++] = actItem;

			ins.push_front(input);

			innerEnable = true;
			m_setNextEnable(true);
		} else if (input.m_getOp() == BRANCH || input.m_getOp() == STORE) { //rs,rt 
			int rs = std::stoi(input.m_getRs(),nullptr,16);
			int rt = std::stoi(input.m_getRt(),nullptr,16);
			int rd = std::stoi(input.m_getRd(),nullptr,16);
			int oldFreeReg = mapTable[rd];
	
			ActiveList actItem(oldFreeReg, rt, 0); //dest, arch, doneBit

			input.m_setActivelistNum(activeListNum);
			input.m_setPs(mapTable[rs]);
			input.m_setPt(mapTable[rt]);

			activeList[activeListNum++] = actItem;

			ins.push_front(input);

			m_setNextEnable(true);
			innerEnable = true;
		} else {
			cout<<"wrong instruction op : "<<input.m_getId()<<endl;
		}
	} else { //stall 
		if(activeListNum >= REGISTER_SIZE || freeList.size() <= 0) {
			Instruction temp = ins.front();
			ins.pop_front();

			temp.m_setPipelineLog("S");
			ins.push_front(temp);
		}

		innerEnable = false;
		nextEnable = false;
	}
}

void DecodeUnit::m_edge() { //already checked queus is available
	if(nextEnable == true) {
		Instruction temp = ins.front();
		temp.m_setPipelineLog("D");

		iu->m_transmit(temp);
		iu->m_getBusyTable(m_transmitBusyTable());

		ins.pop_front();
	} else {

	}
}