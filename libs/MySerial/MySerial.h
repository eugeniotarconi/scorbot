#ifndef MySerial_h
#define MySerial_h
#include"Arduino.h"

#include <StandardCplusplus.h>
#include <serstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <iostream>
#include <ctype.h>

#include <Order.h>

using namespace std;

class MySerial{
	
  public:
  
  	/** STATUS:V  ||	DEFAULT CONSTRUCTOR */
    MySerial(long baud, char token, short MAX_ARGS);
	
	/** STATUS:V  ||	INIT THE SERIAL COMMUNICATION */
	void init();

	
// -------------------- SETTERS GETTERS & PRINTS --------------------
	
	
	/** STATUS:V  ||	GET COMPONENTS OF AN INPUT SENTENCE. OBTAINED BY SERIAL PORT */
	vector<string> getSentenceComponents();
	
	/** STATUS:V  ||	GET THE INPUT SENTENCE */
	string getInputSentence();
	
	/** STATUS:IC ||	CHECK IF SENTENCE IS COMPLETE */
	bool sentenceComplete();
	
	/** STATUS:IC ||	CHECK IF SENTENCE IS COMPLETE */
	void printSentenceComponents();
	
	/** STATUS:IC ||	CHECK IF SENTENCE IS COMPLETE */
	void printSentenceOrders();
	
// --------------------      FUNCTIONALITIES     --------------------

	
	/** STATUS:IC ||	PARSE THE INPTUT SENTENCE TO GET THE COMPONENTS */
    int parseSentenceByComponents();
	
	/** STATUS:IC ||	PARSE THE INPUT SENTENCE BY ORDERS */
    int	parseSentenceByOrders();
	
	/** STATUS:V  ||	PROCEDURE TO SERIAL EVENT ARDUINO'S DEFAULT FUNCTION 
	*	 hay que meter el log en la clase serial y terminar de probar los errores
	*    cuando la cadena es sólo un \n y cuando excede el buffer
	*    hay que poner un ... como caracter clave de fin de linea que indica que 
	*    es una Sentence a trozos
	*/	
    bool mySerialEvent();
	
	/** STATUS:V  ||	CLEAR THE PREVIOUS SENTENCE TO GET ANOTHER ONE */
	void flush();
	
	
// --------------------    SUPPORT FUNCTIONS     --------------------	

	int parseTool(string stringToParse, char token, vector<string> &stringParsed);
	
	/** STATUS:V  ||	DEFAULT DESTRUCTOR */
    ~MySerial(){}; 
	
	
  private:
	
	// Sentence variables
		string         inputSentence;        // a string to hold incoming data
		boolean        sentenceIsComplete;   // whether the string is complete
		char           separatorToken;       // token for separate arguments
		char           endOfSentence;
		vector<string> sentenceComponents; 
	// orders variables
		vector<Order>  orders;
		int			   fetchOrderTurn;
	// Serial communication variables	
		long           serialBaud;
		short 		   SERIAL_BUFFER_SIZE;
		short          MAX_ARGS;             
};


#endif
