#pragma once

#include "common.h"
#include "module.h"
#include "instruction.h"
#include "activelist.h"

class CommitUnit : public Module { //commit should be done in order by referring to active list
public:
	list<Instruction> ins;
	ActiveList* al_ptr;

	CommitUnit();
	~CommitUnit();

	void m_transmit(Instruction input);
	void m_getActivelist(ActiveList* ptr);

	bool m_isClean();
	bool m_getEnable();
	void m_setNextEnable(bool result);
	void m_calc();
	void m_edge();
};