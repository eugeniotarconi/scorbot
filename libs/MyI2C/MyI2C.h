#ifndef MyI2C_h
#define MyI2C_h
#include"Arduino.h"

#include <StandardCplusplus.h>
#include <serstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <iostream>
using namespace std;

class MyI2C{
	
	struct order{
	  int who;
	  string cmd;
	  string args;
	}_order;
	
	public:
		MyI2C(){};	
		~MyI2C(){}; 	
	private:
	
};
#endif