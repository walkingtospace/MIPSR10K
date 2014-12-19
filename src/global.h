#pragma once

#include <queue>
#include "instruction.h"

extern queue<Instruction> canceledIns;
extern bool g_isMispredicted = false;
extern int g_misBranchID = -1;