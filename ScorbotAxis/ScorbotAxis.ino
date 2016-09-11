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
  vector<Order> orders;
/** 1- READ ALL DIGITAL INPUTS; ACTUAL STATE. ACTUAL IMAGE OF STATE MACHINE */    
/** 2- IF: CURRENT ARDUINO HAS BEEN SETED LIKE MASTER THEN EXECUTE THE MASTER ROUTINES (SEND ORDERS) ELSE: ?? */  
  if(iAmMaster){
    // check the serial port and process
    if(mySerial.sentenceComplete()){            
      orders = mySerial.getOrders();    
      //mySerial.printSentenceComponents();
      mySerial.printSentenceOrders();  
      mySerial.flush();
    };     
    // send by I2C information
      // check whos and if one order is to an axis that no owned, then sends to another arduino      
  }else{
     // check I2C entry communications
     // orders = myI2C.getOrders();
  } 
/** 4- EXECUTE COMANDS: TYPE? ARD OR AXES*/ 

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
    mySerial.flush();
  }  
}



