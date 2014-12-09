#include "module.h"

Module::Module() {
	nextEnable = true;
	innerEnable = true;
}

Module::~Module() {}
bool Module::m_isClean() { return true; };
void Module::m_setNextEnable(bool result) {}
bool Module::m_getEnable() { return true; }
void Module::m_calc() {}
void Module::m_edge() {}

