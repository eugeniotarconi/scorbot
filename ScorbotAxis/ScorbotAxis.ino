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
    // mejorar esta inicialización de los ejes
    axisId.push_back(0);      
    axisId.push_back(1);
    axisId.push_back(2);
    myArduino.setAxes(axisId);
/*
    // Inicializate and Attach Timer internal interrupt
    Timer1.initialize(SampleTime); 
    Timer1.attachInterrupt(timerFuncion);
    // Begin Wire Comunication
    Wire.begin(MyID);  
    if(!iAmMaster){
      Wire.onRequest(Request_Routine);  
      Wire.onReceive(Receive_Routine); 
    }
*/
}

/**LOOP FUNCTION */
void loop() {  

/** 1- READ ALL DIGITAL INPUTS; ACTUAL STATE. ACTUAL IMAGE OF STATE MACHINE */ 
/** 2- IF: CURRENT ARDUINO HAS BEEN SETED LIKE MASTER THEN EXECUTE THE MASTER ROUTINES (SEND ORDERS) ELSE: ?? */  
    if(myArduino.getMasterFlag()){
        myArduino.serialCommunications();
        //myArduino.filterMyOrders();
        //myArduino.sendOrders2Slaves();     
    }else{
        myArduino.I2CCommunications();   
    }   
/** 4- PROCESS THE ORDERS */ 
    myArduino.processOrders(); 
/** 5- ALL THE LOG WILL BE SHOWN */     
/** 6- UPDATE IMAGE VARIABLES OF STATE MACHINE  */
/** 7- PREPARE FOR ANOTHER LOOP  */   
    delay(2500);        
}

/*
*------------------------------------------------------------------------------------------------
*  FUNCTIONS INTERRUPT ROUTINES
*------------------------------------------------------------------------------------------------
*/

// Serial interruption
void serialEvent(){
  serialError =  mySerial.mySerialEvent();
  if(serialError){
    mySerial.error("\n\n\n ---> Error: exceed Serial buffer size \n\n");
    mySerial.flush();
  }  
}


/*
// Timer routine
void timerFunction() {
// calcula SÓLO EL PWM: si lo está usando para homing, para llegar a una posición o no lo usa ya depende del estado de la instancia axis
  myArduino.axesControl();
}

// I2C Routines
void Request_Routine(){
  I2Cerror =  myI2C.myI2CRequest();
  if(I2Cerror){
    Serial.println("\n\n\n ---> Error I2C request \n\n");
    mySerial.flush();
  }  
};

void Receive_Routine(int nDat){
  I2Cerror =  myI2C.myI2CRecieve();
  if(I2Cerror){
    Serial.println("\n\n\n ---> Error I2C receive \n\n");
    mySerial.flush();
  }  
};


*/


