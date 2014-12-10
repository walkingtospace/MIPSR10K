#include "instruction.h"

Instruction::Instruction() {
	id = 0;
	line = 0; //for branch identification
	activelistNum = 0; //#: 00,01..
	QueueNum = 0;  //#: 00,01..
	branchMask = "0000"; //0000
	memoryAddress = "0x00000000"; //init with 0x00000000
	status = ""; //init "not commited" -> canceld || committed
	op = rs = rt = rd = extra = "";
	ps = pt = pd = 0;
}

Instruction::Instruction(string inputStr, int insId) {
	id = 0;
	line = 0; //for branch identification
	activelistNum = 0; //#: 00,01..
	QueueNum = 0;  //#: 00,01..
	branchMask = "0000"; //0000
	memoryAddress = "0x00000000"; //init with 0x00000000
	status = ""; //init "not commited" -> canceld || committed
	op = rs = rt = rd = extra = "";
	ps = pt = pd = 0;

	istringstream iss(inputStr);
	int insCnt = 0;

	id = insId;
    while(iss) {
		if(insCnt == 0) {
			iss >> op;
		} else if(insCnt == 1) {
			iss >> rs;
		} else if(insCnt == 2) {
			iss >> rt;
		} else if(insCnt == 3) {
			iss >> rd;
		} else {
			iss >> extra;
		}

		insCnt++;
    }
}

Instruction::Instruction(string inputStr) {
	id = 0;
	line = 0; //for branch identification
	activelistNum = 0; //#: 00,01..
	QueueNum = 0;  //#: 00,01..
	branchMask = "0000"; //0000
	memoryAddress = "0x00000000"; //init with 0x00000000
	status = ""; //init "not commited" -> canceld || committed
	op = rs = rt = rd = extra = "";
	ps = pt = pd = 0;

	istringstream iss(inputStr);
	int insCnt = 0;

    while(iss) {
		if(insCnt == 0) {
			iss >> op;
		} else if(insCnt == 1) {
			iss >> rs;
		} else if(insCnt == 2) {
			iss >> rt;
		} else if(insCnt == 3) {
			iss >> rd;
		} else {
			iss >> extra;
		}

		insCnt++;
    }
}

Instruction::~Instruction() {

}

string Instruction::m_getOp() {
	return op;
}

string Instruction::m_getRs() {
	return rs;
}

string Instruction::m_getRt() {
	return rt;
}

string Instruction::m_getRd() {
	return rd;
}

string Instruction::m_getExtra() {
	return extra;
}

int Instruction::m_getPs() {
	return ps;
}

int Instruction::m_getPt() {
	return pt;
}

int Instruction::m_getPd() {
	return pd;
}

int Instruction::m_getId() {
	return id;
}

int Instruction::m_getLine() {
	return line;
}

int Instruction::m_getActivelistNum() {
	return activelistNum;
}

int Instruction::m_getQueueNum() {
	return QueueNum;
}

string Instruction::m_getBranchMask() {
	return branchMask;
}

string Instruction::m_getMemoryAddress() {
	return memoryAddress;
}

string Instruction::m_getStatus() {
	return status;
}

deque<string> Instruction::m_getPipelineLog() {

	return pipelineLog;
}

void Instruction::m_setOp(string input) {
	op = input;
}

void Instruction::m_setRs(string input) {
	rs = input;

}

void Instruction::m_setRt(string input) {
	rt = input;
}

void Instruction::m_setRd(string input) {
	rd =input;
}

void Instruction::m_setExtra(string input) {
	extra = input;
}

void Instruction::m_setPs(int input) {
	ps = input;
}

void Instruction::m_setPt(int input) {
	pt = input;
}

void Instruction::m_setPd(int input) {
	pd = input;
}

void Instruction::m_setId(int input) {
	id = input;
}

void Instruction::m_setLine(int input) {
	line = input;
}

void Instruction::m_setActivelistNum(int input) {
	activelistNum = input;
}

void Instruction::m_setQueueNum(int input) {
	QueueNum = input;
}

void Instruction::m_setBranchMask(string input) {
	branchMask = input;
}

void Instruction::m_setMemoryAddress(string input) {
	memoryAddress = input;
}

void Instruction::m_setStatus(string input) {
	status = input;
}

void Instruction::m_setPipelineLog(string input) {
	pipelineLog.push_back(input);
}

void Instruction::m_printIns() {
	cout<<op<<" "<<rs<<" "<<rt<<" "<<rd<<" "<<extra<<endl;
}

void Instruction::m_printPipeline() {
	deque<string> temp = m_getPipelineLog();
	
	int size = temp.size();
	for(int j=0; j<m_getId() ; ++j) cout<<"  ";
	for(int i=0; i< size; ++i) {
		cout<<temp.front()<<" ";
		temp.pop_front();
	}
	cout<<endl;
}
