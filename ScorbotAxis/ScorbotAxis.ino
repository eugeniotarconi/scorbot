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
MySerial    mySerial   = MySerial(9600,token,40);
MyI2C       myI2C      = MyI2C();
MyAxis      axis1      = MyAxis();
Logging     Log        = Logging();




/**SETUP FUNCTION */
void setup() {   
    Log.Init(1,9600);
}

void loop() { 
   
  int numberOfOrders=0;
  int actualOrder=0;
  int error=0;
  
/** 1- READ ALL DIGITAL INPUTS; ACTUAL STATE. ACTUAL IMAGE OF STATE MACHINE */
  
/** 2- IF: CURRENT ARDUINO HAS BEEN SETED LIKE MASTER THEN EXECUTE THE MASTER ROUTINES */ 
  if(iAmMaster){       
    if(mySerial.sentenceComplete()){
      // esta sentencia devuelve un vector de orders que es un struct que está definido dentro de la clase MySerial
      auto myOrders = mySerial.parseSentenceByOrders();      
    };
  }  
/** 3- ELSE: ONLY REED I2C CONNECTION TO GET A NEW COMMAND TO EXECUTE */ 
  else{  
    if(myI2C.sentenceComplete()){
      auto myOrders = myI2C.parseSentenceByOrders();      
    };
  }   
   
/** 4- IF A NEW POSITION HAS BEEN RECIEVED TO ACHIEVE BY COMMAND; CALCULATE PID ACTUATION.
 *  Cada clase debe tener su metodo para escribir en sus pines Los de control de los ejes deben ser escrituras temporizadas
*/     
     
  for(actualOrder;actualOrder<=numberOfOrders;actualOrder++){
      switch(myOrders[actualOrder].who){
        case 0: 
          error = axis0.execute(myOrders[actualOrder].cmd,myOrders[actualOrder].args); // ejecutan el comando que les corresponda
        break; 
        default:
          // error
        break;
      }
  }          
/** 5- ALL THE LOG WILL BE SHOWN BY LOG */
  
/** 6- UPDATE IMAGE VARIABLES OF STATE MACHINE  */ 

/** 7- PREPARE FOR ANOTHER LOOP  */ 
  mySerial.flushSentence(); 
  delay(1000);        
}



/*
*------------------------------------------------------------------------------------------------
*  OTHERS FUNCTIONS
*------------------------------------------------------------------------------------------------
*/

void serialEvent(){
  mySerial.mySerialEvent();
}



