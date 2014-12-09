#pragma once

#include "common.h"

class Module {
public:
	bool nextEnable; //enable calc->edge
	bool innerEnable;

	Module();
	~Module();

	virtual bool m_isClean();
	virtual void m_setNextEnable(bool result);
	virtual bool m_getEnable();

	virtual void m_calc();
	virtual void m_edge();
};