/*
------------------------------------------------------------------------------------------------
0         1         2         3         4         5         6         7         8         9
012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345
------------------------------------------------------------------------------------------------
*/

// Configuration files
#include "config.h"  

/**SETUP FUNCTION */
void setup() {   
      mySerial.init();
}

/**LOOP FUNCTION */
void loop() {    
  
/** 1- READ ALL DIGITAL INPUTS; ACTUAL STATE. ACTUAL IMAGE OF STATE MACHINE */  
/** 2- IF has been recieved anything then procesed */
  if(mySerial.sentenceComplete()){            
        mySerial.parseSentenceByComponents();   
        mySerial.printSentenceComponents();   
        mySerial.flushSentence();
  };
/** 2- IF: CURRENT ARDUINO HAS BEEN SETED LIKE MASTER THEN EXECUTE THE MASTER ROUTINES (SEND ORDERS) ELSE: ?? */     
/** 4- AXIS EXECUTE COMANDS */ 
/** 5- ALL THE LOG WILL BE SHOWN */  
/** 6- UPDATE IMAGE VARIABLES OF STATE MACHINE  */ 
/** 7- PREPARE FOR ANOTHER LOOP  */   
  delay(2000);        
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



