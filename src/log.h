#pragma once

#include "common.h"
#include "instruction.h"

class LoggingModule {
public:

	vector<Instruction> ins;

	LoggingModule();
	~LoggingModule();
	void m_pushInstruction(vector<Instruction> is);
	void m_printPipeline(string inputName);
	void m_sort();
	void m_printExecutionDetail(string inputName);

	void push(Instruction ins);
	void print();
};