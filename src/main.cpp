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

		
		if(eu->m_isMispredicted() == true) { //restore
			int id = eu->m_getBranchId();

			iu->m_flushQueues();
			//du->m_restoreStatus();
			//fu->m_rollback(id);

			eu->m_setMispredicted(false);
		}
		
		//cout<<fu->m_isClean()<<" "<<du->m_isClean()<<"  "<<iu->m_isClean()<<"  "<<eu->m_isClean()<<"  "<<cu->m_isClean()<<endl; 
		if(fu->m_isClean() && du->m_isClean() && iu->m_isClean() && eu->m_isClean() && cu->m_isClean() ) { //all work is done
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

	//initializations
	LoggingModule log;
	BranchUnit bu;
	CommitUnit commitUnit;
	ExecutionUnit exeUnit(&commitUnit, &bu);
	IssueUnit issueUnit(&exeUnit);
	DecodeUnit decodeUnit(&issueUnit, &bu);
	FetchUnit fetchUnit(&decodeUnit);
	
	//Connect bypasses
	exeUnit.m_getRefToActivelist(&decodeUnit.activeList);
	exeUnit.m_getIUInstance(&issueUnit);
	commitUnit.m_getRefToActivelist(&decodeUnit.activeList); 
	commitUnit.m_getRefToFreelist(&decodeUnit.freeList);
	commitUnit.m_getBusyTable(decodeUnit.busyBitTable);
	
	traceFile.open(argv[1]);

	//do front-end dump
	while(getline(traceFile, input)) {
		Instruction insFromFile(input, insId);
		fetchUnit.pushInstructions(insFromFile);

		insId++;
	}

	//do pipelining work
	startPipeline(&fetchUnit, &decodeUnit, &issueUnit, &exeUnit, &commitUnit, &log);

	//do print results
	log.m_sort();
	log.m_printExecutionDetail(argv[1]);
	log.m_printPipeline(argv[1]);

	cout<<"Processing is done";

	return 0;
}