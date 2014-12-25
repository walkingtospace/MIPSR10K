MIPSR10K
========

MIPS R10000 architecture simulator with C++ for UCSD CSE 250A Computer Architecture class 

In this project I implemented a cycle-accurate out-of-order simulator modelingthe microarchitecture of the MIPS R10K. I implemented its backend (which includes renaming and everything afterwards), and also developed a trace file that will go into the class testing repository.

**Source code**

	./src

**Trace files** 
	
    ./trace

**How to execute**

	$copy ./trace/trace0.txt ./src/

	$./src/make

	$./MIPS trace0.txt

Then it will make [pipeline]trace0.txt, [execution detail]trace0.txt outputs at the same directory

**Output format**

    [Pipeline Diagram]
    M 01 01 01                |F|D|I|E|E|F|C|
    M 01 01 01                |  |F|D|S|I|E|E|F|C|
    M 01 01 01                |  |  |F|D|S|S|I|E|E|F|C|
    L 01 01 01 00000000       |  |  |  |F|D|S|S|S|S|I|A|E|C|
    L 01 02 02 00000000       |  |  |  |  |F|D|S|S|S|S|S|I|A|E|C|

**Machine configuration and assumption**

1) There would be only load,store,integer,branch,fpadd and fpmul operations

2) There are 32 registers (architectural registers not physical ones), while register 0 is always zero. 

3) There is no separate FP register file. (And correspondingly there are only 64 physical registers total in the machine and only one free and active list.)

4) Treat floating point multiply and floating point add as straight three-cycle functional units. Do not worry about the unpack/pack optimizations for bypassing.

5) Assume that the cache always hits, and that you can do one load or store per cycle.

6) Assume there are no delay slots, and you do not need to worry about branch taken penalties or buffering in the front end. 

7) Assume that communication between floating point and integer instructions is unrestricted, even if it seems nonsensical; e.g a floating point add being used to compute the address of a load. We will use these sequences to test timing characteristics of the pipeline in the absence of variable latency instructions like cache misses.

8) Assume that all state updates occur on the clock edge that marks the transition between pipeline stage. For example, things will be enqued into the active list on the edge between Decode and Issue. Instructions will hang out in the I stage until they move to the execution units.

**References**

http://cseweb.ucsd.edu/classes/fa14/cse240A-a/pdf/04/MIPS_R10K.pdf

http://www.ece.mtu.edu/faculty/rmkieckh/cla/4173/MIPS-R10K-uman1.pdf

http://cseweb.ucsd.edu/classes/fa14/cse240A-a/pdf/04/MIPS_R10K_MPR.pdf

http://cseweb.ucsd.edu/classes/fa14/cse240A-a/pdf/04/Gonzalez_Processor_Microarchitecture_2010_Claypool.pdf


**License**

This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this
file, You can obtain one at http://mozilla.org/MPL/2.0/.


