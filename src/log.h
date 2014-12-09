#pragma once

#include "common.h"
#include "instruction.h"

class LoggingModule {
public:

	LoggingModule();
	~LoggingModule();

	void push(Instruction ins);
	void print();
};