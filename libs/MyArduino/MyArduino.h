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
		
		/** STATUS:IC  ||	CONSTRUCTOR SETTING AXES */
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
		bool checkIfAxisIsMine(int who);

		
// --------------------    SUPPORT FUNCTIONS     --------------------


	private:
		vector<Axis> axes;
		
		
// --------------------     PRIVATE METHODS      --------------------

};
#endif
