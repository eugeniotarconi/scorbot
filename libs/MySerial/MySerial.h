#ifndef MySerial_h
#define MySerial_h
// include arduino's libraries
#include"Arduino.h"
// include extern libraries
#include <inttypes.h>
#include <stdarg.h>
#include <StandardCplusplus.h>
#include <serstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <iostream>
#include <ctype.h>
// include serf libraries
#include <Order.h>

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
//#include "pins_arduino.h"
extern "C" {
  #include <avr/io.h>
}

#define CR "\r\n"

/*!
* <li><b>\%s</b>	replace with an string (char*)</li>
* <li><b>\%c</b>	replace with an character</li>
* <li><b>\%d</b>	replace with an integer value</li>
* <li><b>\%l</b>	replace with an long value</li>
* <li><b>\%x</b>	replace and convert integer value into hex</li>
* <li><b>\%X</b>	like %x but combine with <b>0x</b>123AB</li>
* <li><b>\%b</b>	replace and convert integer value into binary</li>
* <li><b>\%B</b>	like %x but combine with <b>0b</b>10100011</li>
* <li><b>\%t</b>	replace and convert boolean value into <b>"t"</b> or <b>"f"</b></li>
* <li><b>\%T</b>	like %t but convert into <b>"true"</b> or <b>"false"</b></li>
* <tr><td>0</td><td>LOG_MODE_NOOUTPUT</td><td>no output </td></tr>
* <tr><td>1</td><td>LOG_MODE_ERRORS</td><td>only errors </td></tr>
* <tr><td>2</td><td>LOG_MODE_INFOS</td><td>errors and info </td></tr>
* <tr><td>3</td><td>LOG_MODE_DEBUG</td><td>errors, info and debug </td></tr>
* <tr><td>4</td><td>LOG_MODE_VERBOSE</td><td>all </td></tr>
* <h1>History</h1><br>
*/

using namespace std;

class MySerial {
	private:
		// Sentence variables
		string         inputSentence;        // String to hold incoming data
		boolean        sentenceCompleteFlag;   // whether the string is complete
		char           separatorToken;       // token for separate Components
		char           endOfSentence;		 // character to indicate end of Sentence
		vector<string> sentenceComponents; 	 // Hold sentence components
		// orders variables
		Order		   order;
		vector<Order>  orders;               // Hold the incoming orders
		// Serial communication variables	
		long           serialBaud;           // frecuency of serial communication
		short 		   SERIAL_BUFFER_SIZE;   // size of hardwareSerial buffer 64
		// Logger variables
		bool logMode[5]; 	
		
	public:

		/** STATUS:V  ||	DEFAULT CONSTRUCTOR */
		MySerial();

		/** STATUS:V  ||	DEFAULT CONSTRUCTOR */
		MySerial(long newSerialBaud, char newSeparaToken,Order newOrder, string newLogMode);

		/** STATUS:V  ||	DEFAULT DESTRUCTOR */
		~MySerial(){}; 

		/** STATUS:V  ||	INIT THE ARDUINO'S SERIAL COMMUNICATION */
		void init();

		/** STATUS:V  ||	INIT THE ARDUINO'S SERIAL COMMUNICATION */
		void init(long newSerialBaud);	

		// --------------------      SETS      --------------------

		/** STATUS:IC  || */
		void setLogMode(Order::ARG newLogMode, Order::ARG  newStatus);

		// --------------------      GETS      --------------------

		int getArrayPositionOfThisMode(Order::ARG mode);
		
		/** STATUS:V  ||	GET COMPONENTS OF AN INPUT SENTENCE. OBTAINED BY SERIAL PORT */
		vector<string> getSentenceComponents();

		/** STATUS:V  ||	GET THE INPUT SENTENCE */
		string getInputSentence();	

		/** STATUS:V ||	CHECK IF SENTENCE IS COMPLETE */
		bool getSentenceCompleteFlag();

		/** STATUS:V || Parse sentence by orders and return these orders */
		vector<Order> MySerial::getOrders();

		// --------------------      LOGS      --------------------

		/** STATUS:V ||	Show by console the actual sentence components */
		void logSentenceComponents();

		/** STATUS:V ||	Show by console the actual orders */
		void logSentenceOrders();

		/** STATUS:IC  || */
		void error(const char* msg, ...);

		/** STATUS:IC  || */
		void info(const char* msg, ...);

		/** STATUS:IC  || */
		void debug(const char* msg, ...);

		/** STATUS:IC  || */
		void verbose(const char* msg, ...);

			
		// --------------------      FUNCTIONALITIES     --------------------

			
		/** STATUS:IC ||	PARSE THE INPTUT SENTENCE TO GET THE COMPONENTS 
		*   parse the input sentence in components
		* 
		*  Devuelve el numero de componentes que tiene la Sentencia
		*
		*  Mejoras propuestas:
		*---
		*  Hay que ponerlo a prueba de sentencias con varios espacios en blanco seguidos
		*  O sentencias que sean enteras en blanco
		*  hay que decidir si se excede el numero de componenetes permitidos que ocurre con los
		*  componentes que se habían conseguido, si se borran o se quedan
		*/
		int parseSentenceByComponents();
		
		/** STATUS:IC ||	PARSE THE INPUT SENTENCE BY ORDERS */
		int	parseSentenceByOrders();
		
		/** STATUS:V  ||	PROCEDURE TO SERIAL EVENT ARDUINO'S DEFAULT FUNCTION 
		*	 errores 
		*      cuando la cadena es sólo un \n 
		*      cuando excede el buffer
		*      ... como caracter clave de Sentence a trozos
		*/	
		bool mySerialEvent();
		
		/** STATUS:V  ||	CLEAR THE PREVIOUS SENTENCE TO GET ANOTHER ONE */
		void flush();	
		
	private:		
		
		void print(const char *format, va_list args);
			
		bool shouldPrint(Order::ARG mode);

		/** STATUS:IC ||	PARSE THE INPUT SENTENCE BY ORDERS */
		int fillOrders(string cmdType, string cmd, vector<string> whos, vector<string> args);

		/** STATUS:IC ||	PARSE THE INPUT SENTENCE BY ORDERS */
		bool verifyWhos(vector<string> whos, vector<int> &whosInt);
			
		/** STATUS:V  ||	DEFAULT DESTRUCTOR */
		int parseTool(string stringToParse, char token, vector<string> &stringParsed);
		
};


#endif
