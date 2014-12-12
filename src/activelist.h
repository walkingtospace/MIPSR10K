#pragma once

#include "common.h"

class ActiveList {
public:
	int activeTag;
	int DestReg; //physical register;
	int ArchReg;
	int doneBit; //init with 0 

	void m_setDonebit(int bit);
	ActiveList();
	ActiveList(int dest, int arch, int done, int tg);
	~ActiveList();
};