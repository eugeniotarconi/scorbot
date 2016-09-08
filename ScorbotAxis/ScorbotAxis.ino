/*
------------------------------------------------------------------------------------------------
0         1         2         3         4         5         6         7         8         9
012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345
------------------------------------------------------------------------------------------------
*/
// Configuration files
#include "config.h"    
// GLOBAL VARIABLES 
short       debugMode  = LOG_LEVEL_NOOUTPUT;
MyAxis      axis1      = MyAxis();
MySerial    mySerial   = MySerial(SerialBaud,token,MaxSentenceComponents);// ponerle un init para ponerlo en setup
MyI2C       myI2C      = MyI2C();  
bool        serialError= false; 
/**SETUP FUNCTION */
void setup() {   
      
}

void loop() {    
  int numberOfOrders=0;
  int actualOrder=0;
  int error = 0;

/** 1- READ ALL DIGITAL INPUTS; ACTUAL STATE. ACTUAL IMAGE OF STATE MACHINE */  
/** 2- IF has been recieved anything then procesed */
  if(mySerial.sentenceComplete()){            
      Serial.println(mySerial.getInputSentence().c_str());      
      mySerial.flushSentence();
  };
/** 2- IF: CURRENT ARDUINO HAS BEEN SETED LIKE MASTER THEN EXECUTE THE MASTER ROUTINES (SEND ORDERS) ELSE: ?? */ 
  if(iAmMaster){}else{}      
/** 4- AXIS EXECUTE COMANDS */ 
/** 5- ALL THE LOG WILL BE SHOWN */  
/** 6- UPDATE IMAGE VARIABLES OF STATE MACHINE  */ 
/** 7- PREPARE FOR ANOTHER LOOP  */   
  delay(1500);        
}
/*
*------------------------------------------------------------------------------------------------
*  OTHERS FUNCTIONS
*------------------------------------------------------------------------------------------------
*/

void serialEvent(){
  serialError =  mySerial.mySerialEvent();
  if(serialError){
    Serial.println("\n\n\n ---> Error: exceed Serial buffer size \n\n");
    mySerial.flushSentence();
  }
  
}



