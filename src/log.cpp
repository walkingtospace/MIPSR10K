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

void LoggingModule::m_printPipeline(string inputName) {
	ofstream output;
	output.open("[Pipeline]"+ inputName);

	output<<"[Pipeline Diagram]"<<endl;
	for(int i=0 ; i<ins.size() ; ++i) {
		ins[i].m_printPipeline(&output);
	}
	
	output.close();
}

void LoggingModule::m_printExecutionDetail(string inputName) {
	ofstream output;
	string str_id = "";
	string str_line = "";
	string str_ps = "";
	string str_pt = "";
	string str_pd = "";
	string str_actNum = "";
	int id = 0;
	int line = 0;
	int Ps = 0;
	int Pt = 0;
	int Pd = 0;
	int actNum = 0;

	output.open("[Execution Detail]"+ inputName);
	
	output<<"[Execution Detail]"<<endl;
	output<<"ID | LINE | TYPE | Rs(Phy) | Rt(Phy) | Rd(Phy) | Activelist# | BranchMask | MemoryAddress | Status"<<endl;

	for(int i=0 ; i<ins.size() ; ++i) {
		id = ins[i].m_getId();
		line = ins[i].m_getLine();
		Ps = ins[i].m_getPs();
		Pt = ins[i].m_getPt();
		Pd = ins[i].m_getPd();
		actNum = ins[i].m_getActivelistNum();

		str_id = id<10 ? "0" + to_string((long long)id) : to_string((long long)id);
		str_line = line<10 ? "0" + to_string((long long)line) : to_string((long long)line);
		str_ps = Ps<10 ? "0" + to_string((long long)Ps) : to_string((long long)Ps);
		str_pt = Pt<10 ? "0" + to_string((long long)Pt) : to_string((long long)Pt);
		str_pd = Pd<10 ? "0" + to_string((long long)Pd) : to_string((long long)Pd);
		str_actNum = actNum<10 ? "0" + to_string((long long)actNum) : to_string((long long)actNum);
		 
		output<<str_id<<" |    "<<str_line<<" |     "<<ins[i].m_getOp()<<" |         "<<str_ps<<" |        "<<str_pt<<" |        "<<str_pd<<" |            "<<str_actNum<<" |           "<<ins[i].m_getBranchMask()<<" |      "<<ins[i].m_getMemoryAddress()<<" | "<<ins[i].m_getStatus()<<endl;
	}
	
	output.close();
}