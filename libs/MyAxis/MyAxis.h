#ifndef MyAxis_h
#define MyAxis_h
#include"Arduino.h"

#include <StandardCplusplus.h>
#include <serstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <iostream>
using namespace std;

class MyAxis{
  public:
    MyAxis(){};	
	bool execute(string cmd, string args){return 0;};
	~MyAxis(){};
};
#endif
