#ifndef MyArduino_h
#define MyArduino_h
#include"Arduino.h"

#include <StandardCplusplus.h>
#include <serstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <iostream>

#include <Order.h>
#include <Axis.h>

using namespace std;

class MyArduino{
	public:
	
		/** STATUS:V  ||	DEFAULT CONSTRUCTOR */
		MyArduino();	
		
		MyArduino( vector<int> axisId );
		
		/** STATUS:V  ||	DEFAULT DESTRUCTOR */
		~MyArduino(){};
		
		
		
// -------------------- SETTERS GETTERS & PRINTS --------------------

		/** STATUS:IC  ||	set axis istances with id axisId */
		void setAxes( vector<int> axisId );


// --------------------     FUNCTIONALITIES      --------------------

		void processOrders( vector<Order> orders2Process );
		int  processOrder( Order order );
		void readStateMachine();
		void updateStateMachine();
		vector<Order> filterMyOrders( vector<Order> &orders );
		

// --------------------    SUPPORT FUNCTIONS     --------------------
	private:
		vector<Axis> axis;
// --------------------     PRIVATE METHODS      --------------------

};
#endif
