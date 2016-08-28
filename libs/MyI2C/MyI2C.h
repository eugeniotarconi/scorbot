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
	public:
		MyI2C(){sentenceIsComplete =false;};
		bool sentenceComplete(){return sentenceIsComplete;};
		int parseSentenceByOrders(){return 0;};
	
		~MyI2C(){}; 	
	private:
		bool sentenceIsComplete;
};
#endif
