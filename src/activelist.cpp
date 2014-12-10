#include "activelist.h"

ActiveList::ActiveList() {}

ActiveList::ActiveList(int dest, int arch, int done) {
	DestReg = dest; //physical register;
	ArchReg = arch;
	doneBit = done; //init with 0 
}
ActiveList::~ActiveList() {}