

/*
 * Esquema del programa para controlar 3 ejes del scorbot, como master o como slave
 */
/*
------------------------------------------------------------------------------------------------
0         1         2         3         4         5         6         7         8         9
012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345
------------------------------------------------------------------------------------------------
*/

// INCLUDE LIBRARIES
#include <String.h>
    // Github libraries 
    #include <Logging.h>
    // Project files
    #include "config.h"
    // Own libraries
    #include <MySerial.h>

    
// GLOBAL VARIABLES esto en config
bool        iAmMaster  = true;
short       debugMode  = LOG_LEVEL_NOOUTPUT;
MySerial    mySerial   = MySerial();
Logging     Log        = Logging();


void setup() {
  
  // ver si hay que hacer un if( iammaster)
  Log.Init(debugMode,9600);
  Log.Info(CR "******************************************" CR);
  Log.Info("EMPIEZA SESIÓN");
  Log.Info(CR "******************************************" CR);
}


void loop() {  
  String args[MAX_ARGS];
  int nargs;
  int error;
/* 
 *  READ ALL DIGITAL INPUTS; ACTUAL STATE. 
*/
  //homeValue = !digitalRead(homePin);
  //...

/* 
 *  IF: CURRENT ARDUINO HAS BEEN SETED LIKE MASTER THEN EXECUTE THE MASTER ROUTINES 
*/ 
  if(iAmMaster){   
      if(stringComplete){
        nargs = mySerial.parseString( inputString,  token,  MAX_ARGS,  args); 
        // MyMaster master = MyMaster(); es una instancia de la clase MyMaster.
        // la función master.order() procesa la información recibida, envía las consignas a los slaves y se queda con el comando que debe ejecutar en los ejes a su cargo
          //nargs = master.order(args,nargs); 
      };
  }
/* 
 *  ELSE: ONLY REED I2C CONNECTION TO GET A NEW COMMAND TO EXECUTE
*/  
  else{
    //myI2C.read();
  }
/* 
 *  EXECUTE COMMAND. ONLY ACTUALIZATE THE STATE OF GLOBAL VARIABLES; DOESNT IMPLY ACT( NO DIGITAL WRITES)
*/

   error = doCommand(args);
  
/* 
 *  IF A NEW POSITION HAS BEEN RECIEVED TO ACHIEVE BY COMMAND; CALCULATE PID ACTUATION.
*/
    // MyAxis axis1 = new MyAxis(); son instancias de la clase MyAxis
    // axis1.positionControl(MOVE,POSITION); si se ha dicho que se mueva además de decir una nueva posición
    // axis2.positionControl();
    // axis3.positionControl();
/* 
 *  EXECUTE STATE MACHINE FOR SEARCHING HOME IF COMMAND HAS BEEN ACTIVATED. CALCULATE PID ACTUATION
*/
    // axis1.homming(MOVE);
    // axis2.homming();
    // axis3.homming();
  
/* 
 *  All new values of actuations wil be set in theirs pins
*/    
  //digitalWrite(brakePin, brakeValue);
  //digitalWrite(dirPin, dirValue);
  //digitalWrite(homeLedPin, homeValue);
  
/* 
 *   ALL THE LOG WILL BE SHOWN.
 *  
 *  La respuesta será un array de string compuesto por el string de cada modo: error, info, debug,verbose y se mostrará según el modo en el que se encuentre el programa
*/
    Log.Error(CR "is this an real error? %d" CR, error);
    Log.Info(CR "have fun with this Log. error code: %d\n" CR ,error);
    Log.Debug(CR "only will be showed if debug mode is set %d\n" CR ,error);
    Log.Verbose(CR "only will be showed if verbose mode is set %d\n" CR ,error);
    
    inputString = "";
    stringComplete = false;
    memset(args,'\0',MAX_ARGS);


/* 
 * UPDATE IMAGE VARIABLES
*/ 
    /* 
    _encoderValue = encoderValue;
    _clockwise = clockwise;
    _homeValue = homeValue;
    _motorValue = motorValue;
    _stall = stall;
    */ 

  delay(1000);        
}



/*------------------------------------------------------------------------------------------------
 *  OTHERS FUNCTIONS
 *------------------------------------------------------------------------------------------------
*/

int doCommand(String args[]) {
  int errorCode = 0;
  int n;
  if(args[0] == "DEBUG_MODE"){
    // Comprobar que el args1 está bien puesto por seguridad
        // 0 ninguna salida
        // 1 solo los errores
        // 2 errores y información
        // 3 error info y debug
        // 4 todo
    Log.Init((int)args[1].toFloat(),9600);
  }
  else
    errorCode = -2;

  return errorCode;
}

void serialEvent(){
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n')
      stringComplete = true;
    else{
      // add it to the inputString:
      inputString += inChar;
      }      
  }
  inputString.toUpperCase();
}

