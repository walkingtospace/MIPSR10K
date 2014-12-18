#pragma once

#include "instruction.h"
#include "activelist.h"

struct Stack {
	int mapTable[REGISTER_SIZE];
	int busyBitTable[FREELIST_SIZE];
	int activeListNum;
		
	deque <Instruction> ins; //MAXSIZE == 8
	queue <int> freeList; //MAXSIZE == 64
	vector<ActiveList> activeList; //MAXSIZE == 32
	string mask;
};
