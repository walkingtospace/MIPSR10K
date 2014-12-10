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

const string INTEGER = "I"; //rs, rt / rd
const string ADDFP = "A"; //rs, rt / rd
const string MULTIFP = "M"; //rs, rt / rd
const string LOAD = "L"; //rs / rt
const string STORE = "S"; //rs, rt / --
const string BRANCH = "B"; //rs, rt / --
