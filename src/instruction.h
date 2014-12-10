#pragma once

#include "common.h"

class Instruction {
public:
	int id;
	int line; //for branch identification
	int activelistNum; //#: 00,01..
	int QueueNum;  //#: 00,01..
	string branchMask; //0000
	string memoryAddress; //init with 0x00000000
	string status; //init "not commited" -> canceld || committed
	deque <string> pipelineLog; //2(ex: start cycle), F, D, I, "S" ,"E" ," ", " " , "C" 

	string op;
	string rs;
	string rt;
	string rd;
	string extra;

	int ps;
	int pt;
	int pd;

	Instruction();
	Instruction(string inputStr); //parse instruction into member variables
	Instruction(string inputStr, int id); //parse instruction into member variables
	~Instruction();

	string m_getOp();
	string m_getRs();
	string m_getRt();
	string m_getRd();
	string m_getExtra();
	int m_getPs();
	int m_getPt();
	int m_getPd();

	int m_getId();
	int m_getLine();
	int m_getActivelistNum();
	int m_getQueueNum();
	string m_getBranchMask();
	string m_getMemoryAddress();
	string m_getStatus();
	deque <string> m_getPipelineLog();
	
	void m_setOp(string input);
	void m_setRs(string input);
	void m_setRt(string input);
	void m_setRd(string input);
	void m_setExtra(string input);
	void m_setPs(int input);
	void m_setPt(int input);
	void m_setPd(int input);

	void m_setId(int input);
	void m_setLine(int input);
	void m_setActivelistNum(int input);
	void m_setQueueNum(int input);
	void m_setBranchMask(string input);
	void m_setMemoryAddress(string input);
	void m_setStatus(string input);
	void m_setPipelineLog(string input);
	/***************** a lot of getter/setter should be refactored later *****************************/

	void m_printIns();
	void m_printPipeline();
};