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
#include <MySerial.h>

using namespace std;

class MyArduino{
	private:
		MySerial *mySerial;
		bool masterFlag;
		vector<Axis> axes;
		vector<Order> orders;
		vector<Order> orders2Slaves;
		
	public:
	
		/** STATUS:V  ||	DEFAULT CONSTRUCTOR */
		MyArduino(MySerial *newMySerial, bool newMasterFlag);	
		
		/** STATUS:IC  ||	CONSTRUCTOR SETTING AXES */
		MyArduino( vector<int> axisId , bool newMasterFlag);
		
		/** STATUS:V  ||	DEFAULT DESTRUCTOR */
		~MyArduino(){};
		
// -------------------- SETTERS GETTERS & PRINTS --------------------

		/** STATUS:IC  ||	set axis istances with id axisId */
		void setAxes( vector<int> axisId );

		bool getMasterFlag();

// --------------------     FUNCTIONALITIES      --------------------

		// Communications
		void serialCommunications();
		void I2CCommunications();
		void filterMyOrders();
		void sendOrders2Slaves();
		
		// ProcessOrders
		void processOrders();
		int  processOrder( Order order );
		void readStateMachine();
		void updateStateMachine();
		bool checkIfAxisIsMine(int who);


};
#endif
