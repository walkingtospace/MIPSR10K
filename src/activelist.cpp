#include "activelist.h"

ActiveList::ActiveList() {

}

ActiveList::ActiveList(int dest, int arch, int done, int tg) {
	DestReg = dest; //physical register;
	ArchReg = arch;
	doneBit = done; //init with 0 
	activeTag = tg;
}
ActiveList::~ActiveList() {}

void ActiveList::m_setDonebit(int bit) {
	doneBit = bit;
}
