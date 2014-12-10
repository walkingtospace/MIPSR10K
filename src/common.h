#pragma once

#include <iostream>
#include <fstream>
#include <ostream>
#include <deque>
#include <queue>
#include <list>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

const int INSBUFFSIZE = 8;
const int REGISTER_SIZE = 32;
const int FPADDER_SIZE = 3;
const int FPMULTIPLIER_SIZE = 3;

const string INTEGER = "I"; //rs, rt / rd
const string ADDFP = "A"; //rs, rt / rd
const string MULTIFP = "M"; //rs, rt / rd
const string LOAD = "L"; //rs / rt
const string STORE = "S"; //rs, rt / --
const string BRANCH = "B"; //rs, rt / --

/*
L 1f 12 xx ABCD1234  (r18 = MEM[r31+imm] which is MEM [ABCD1234])
S 10 12 xx ABCD1234  (MEM[r16+imm] which is MEM [ABCD1234] = r18)
*/
