#pragma once

#include "common.h"
#include "module.h"
#include "DecodeUnit.h"
#include "instruction.h"

class FetchUnit : public Module {
public:
	deque<Instruction> ins;
	stack<Instruction> ins_buffer; //for mis-taken branch rollback
	DecodeUnit* du;

	FetchUnit(DecodeUnit* input);
	~FetchUnit();
	bool pushInstructions(Instruction input);
	void m_rollback(int id);
	
	bool m_isClean();
	bool m_getEnable();
	void m_setNextEnable(bool result);
	void m_calc();
	void m_edge();
};