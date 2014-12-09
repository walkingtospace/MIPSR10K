#pragma once

#include "common.h"
#include "module.h"
#include "instruction.h"
#include "DecodeUnit.h"

class FetchUnit : public Module {
public:
	queue<Instruction> ins;
	DecodeUnit* du;

	FetchUnit(DecodeUnit* input);
	~FetchUnit();
	bool pushInstructions(Instruction input);
	
	bool m_isClean();
	bool m_getEnable();
	void m_setNextEnable(bool result);
	void m_calc();
	void m_edge();
};