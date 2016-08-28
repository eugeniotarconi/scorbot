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

using namespace std;

class MySerial{
    struct order{
	  int who;
	  string cmd;
	  string args;
	}_order;
  public:
  	/** STATUS:V  ||	DEFAULT CONSTRUCTOR	
	* 
	*  
	*/
    MySerial(long baud, char token, short MAX_ARGS);

	/** STATUS:V  ||	GET COMPONENTS OF AN INPUT SENTENCE. OBTAINED BY SERIAL PORT
	* 	
	*  
	*/
	vector<string> 	getSentenceComponents();
	
	/** STATUS:IC ||	PARSE THE INPTUT SENTENCE TO GET THE COMPONENTS
	* 
	*  
	*/
    int 			parseSentence();
	
	/** STATUS:IC ||	PARSE THE INPUNT SENTENCE BY ORDERS
	* 
	*/
    vector<MySerial::order>	parseSentenceByOrders();
	
	/** STATUS:V  ||	PROCEDURE TO SERIAL EVENT ARDUINO'S DEFAULT FUNCTION 
	* 
	*  
	*/	
    void 			mySerialEvent();
	
	/** STATUS:IC ||	CHECK IF SENTENCE IS COMPLETE
	* 
	*  
	*/
	bool 			sentenceComplete();
	
	/** STATUS:V  ||	CLEAR THE PREVIOUS SENTENCE TO GET ANOTHER ONE
	* 
	*  
	*/
	void 			flushSentence();
	
	/** STATUS:V  ||	DEFAULT DESTRUCTOR
	*/
    ~MySerial(){}; 
	
	
  private:

	string         inputSentence;        // a string to hold incoming data
	boolean        sentenceIsComplete;     // whether the string is complete
	char           separatorToken;       // token for separate arguments
	char           endOfSentence;
	int 		   numberOfOrders;
	vector<string> sentenceComponents; 
	vector<order> orders;
	
    long           serialBaud;
	short          MAX_ARGS;             // unused
};


#endif
