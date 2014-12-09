#pragma once

#include "common.h"

class ActiveList {
public:
	int DestReg; //physical register;
	int ArchReg;
	int doneBit; //init with 0 

	ActiveList(int dest, int arch, int done);
	~ActiveList();
};