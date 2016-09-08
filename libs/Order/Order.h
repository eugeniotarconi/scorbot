#ifndef Order_h
#define Order_h
#include"Arduino.h"

#include <StandardCplusplus.h>
#include <serstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <iostream>

using namespace std;

class Order{	
	public:
	int who;
	string cmd;
	string args;	
	Order(){
		this->who = 0;
		this->cmd = "";
		this->args = "";
	}
	~Order(){};
	private:
	
};


#endif
