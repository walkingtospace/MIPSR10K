#include "common.h"
#include "instruction.h"
#include "fetchUnit.h"
#include "decodeUnit.h"
#include "issueUnit.h"
#include "executionUnit.h"
#include "commitUnit.h"
#include "log.h"

void startPipeline(FetchUnit* fu, DecodeUnit* du, IssueUnit* iu, ExecutionUnit* eu, CommitUnit* cu, LoggingModule* lg) {
	
	while(1) {
		fu->m_calc();
		du->m_calc();
		iu->m_calc();
		eu->m_calc();
		cu->m_calc();

		cu->m_edge();
		eu->m_edge();
		iu->m_edge();
		du->m_edge();
		fu->m_edge();

		if(fu->m_isClean() && du->m_isClean() && iu->m_isClean() && eu->m_isClean()) { //all work is done
			lg->m_pushInstruction(cu->m_dumpInstructions());

			break;
		}
	}
}


int main(int argc, char* argv[]) {
	if(argc <= 1) {
		cout<<"Please insert tracefile.txt"<<endl;

		return 0;
	}

	ifstream traceFile;
	string input = "";
	int insId = 0;

	LoggingModule log;
	CommitUnit commitUnit;
	ExecutionUnit exeUnit(&commitUnit);
	IssueUnit issueUnit(&exeUnit);
	DecodeUnit decodeUnit(&issueUnit);
	FetchUnit fetchUnit(&decodeUnit);
	
	//connect bypasses
	exeUnit.m_getRefToActivelist(&decodeUnit.activeList);
	commitUnit.m_getRefToActivelist(&decodeUnit.activeList); 
	commitUnit.m_getRefToFreelist(&decodeUnit.freeList);
	
	traceFile.open(argv[1]);
	

	//front-end dump
	while(getline(traceFile, input)) {
		Instruction insFromFile(input, insId);
		//insFromFile.m_printIns();

		fetchUnit.pushInstructions(insFromFile);
		insId++;
	}

	//do work
	startPipeline(&fetchUnit, &decodeUnit, &issueUnit, &exeUnit, &commitUnit, &log);
	log.m_printPipeline();
	//print result

	return 0;
}



