#ifndef Axis_h
#define Axis_h

#include"Arduino.h"
#include <StandardCplusplus.h>
#include <serstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <iostream>

#include <MySerial.h>
#include <Order.h>

using namespace std;

class Axis{
	
	private:
		MySerial *mySerial;
		short id;
		short brakePin;
		
	public:
	
		/** STATUS:V  ||	DEFAULT CONSTRUCTOR */
		Axis(MySerial *newMySerial);	
		
		/** STATUS:V  ||	DEFAULT DESTRUCTOR */
		~Axis(){};

		void setId(short newId);

		short getId();

		void setBrakePin(short newBrakePin);

		/** STATUS:IC */
		int processOrder(Order newOrder);

		void brake(Order::ARG brakeMode);

		bool str2Int(string toConvert,int &converted);

};


#endif
