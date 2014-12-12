#include "log.h"


LoggingModule::LoggingModule() {

}

LoggingModule::~LoggingModule() {

}

void LoggingModule::m_pushInstruction(vector<Instruction> is) {
	ins = is;
}

void LoggingModule::m_sort() {
	for(int i=0; i<ins.size() ; ++i) {
		for(int j=i; j<ins.size() ; ++j) {
			if(ins[i].id > ins[j].id) {
				Instruction temp = ins[i];
				ins[i] = ins[j];
				ins[j] = temp; 
			}
		}
	}
}

void LoggingModule::m_printPipeline() {
	m_sort();

	for(int i=0 ; i<ins.size() ; ++i) {
		ins[i].m_printPipeline();
	}
}