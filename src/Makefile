MIPS: main.o activelist.o branchUnit.o commitUnit.o decodeUnit.o executionUnit.o fetchUnit.o instruction.o issueUnit.o log.o module.o
	g++ -std=gnu++11 -o MIPS main.o activelist.o branchUnit.o commitUnit.o decodeUnit.o executionUnit.o fetchUnit.o instruction.o issueUnit.o log.o module.o
 
main.o : common.h instruction.h fetchUnit.h decodeUnit.h issueUnit.h executionUnit.h commitUnit.h log.h main.cpp
	g++ -std=gnu++11 -c main.cpp
 
activelist.o : common.h activelist.cpp
	g++ -std=gnu++11 -c activelist.cpp
	
branchUnit.o : common.h module.h stack.h instruction.h activelist.h branchUnit.cpp
	g++ -std=gnu++11 -c branchUnit.cpp

commitUnit.o : common.h module.h instruction.h activelist.h commitUnit.cpp
	g++ -std=gnu++11 -c commitUnit.cpp
	
decodeUnit.o : common.h module.h issueUnit.h BranchUnit.h instruction.h activelist.h decodeUnit.cpp
	g++ -std=gnu++11 -c decodeUnit.cpp
	
executionUnit.o : common.h module.h commitUnit.h issueUnit.h BranchUnit.h executionUnit.cpp
	g++ -std=gnu++11 -c executionUnit.cpp

fetchUnit.o : common.h module.h decodeUnit.h instruction.h fetchUnit.cpp
	g++ -std=gnu++11 -c fetchUnit.cpp
	
instruction.o : common.h instruction.cpp
	g++ -std=gnu++11 -c instruction.cpp
	
issueUnit.o : common.h module.h executionUnit.h instruction.h issueUnit.cpp
	g++ -std=gnu++11 -c issueUnit.cpp

log.o : common.h instruction.h log.cpp
	g++ -std=gnu++11 -c log.cpp
	
module.o : common.h module.cpp
	g++ -std=gnu++11 -c module.cpp
	

	
