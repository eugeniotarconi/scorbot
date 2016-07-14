/*
 * scorbot_arduino - control scorbot-ER 4PC
 *
 * control an joint of a scorbot-ER 4PC from an external interface via serial communication
 *
 *   - PAY ATTENTION: input message must end with a character LF for proper operation
 *
 * copyright (c) 2016 marnie & mark
 *
 * GNU General Public License
 *
 * references:
 *   - http://totaki.com/poesiabinaria/2010/12/separar-palabras-de-una-cadena-de-caracteres-en-un-array-c/
 *   - http://www.dyadica.co.uk/simple-serial-string-parsing/ [0.2]
 *   - http://www.arduino.cc/en/Tutorial/SerialEvent
 *   - http://forum.arduino.cc/index.php?topic=209407.0
 *   - http://arduino.cc/en/Tutorial/AnalogInOutSerial
 *   - http://playground.arduino.cc/Main/RotaryEncoders
 *   - http://playground.arduino.cc/Code/Timer1
 *
 * version history
 *   0.8, 2016,06,13, m&m: again from scratch, just for a single joint
 *   0.7, 2016.06.06, m&m: start from scratch
 *   0.6, 2016.05.25, m&m: concactString, a diferent function to reply each command
 *   0.5, 2016.05.25, m&m:
 *   0.4, 2016.05.25, m&m: parseString (thanks gaspar fernandez)
 *   0.3, 2016.05.25, m&m: isValidNumber (thanks hbx2013)
 *   0.2, 2016.05.25, m&m: strtok_r for parsing a string (thanks dyadica)
 *   0.1, 2016.05.24, m&m: Serial.readString (thaks vicente arevalo)
 *   0.0, 2016.05.24, m&m: alfa release
 */

/*
------------------------------------------------------------------------------------------------
0         1         2         3         4         5         6         7         8         9
012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345
------------------------------------------------------------------------------------------------
*/

// INCLUDE LIBRARIES
//#include <TimerOne.h>

// MACROS
#define limit(x,minimum,maximum) (min(max(x,minimum),maximum))

// USER TYPES

// CONSTANTS
#define FIRMWARE_VERSION "scorbot_arduino_0_8 2016.06.18"
#define MAX_ARGS  10

// DIGIAL INPUTS
#define phaseAPin  2 // external interrupt #0 for encoder phase A signal
#define phaseBPin  3 // external interrupt #1 for encoder phase B signal
#define homePin    4 // join origin signal
boolean homeValue = false;

// DIGITAL OUTPUTS
#define motorPin    5 // PWM output for motor driver (LMD18200 - H-Bridge)
#define brakePin    6 // brake output for motor driver (LMD18200 - H-Bridge)
#define dirPin      7 // direction output for motor driver (LMD18200 - H-Bridge)
#define homeLedPin 13 // led for display home state
boolean brakeValue = true;
boolean dirValue = false;
int motorValue = 0;

// execution parameters
float sampleTime = 10e-3; // pid control loop time cycle [sec]
float cycleTime = 10;  // loop function delay [ms]

// SCORBOT-ER 4PC A1 join parameters
const int encoderSlots = 20;   // encoder disk slots
const int countingRatio = 4;   // quadrature X4 logic
const float gearRatio = 127.1; // motor gear ratio (127.1:1)
const float joinRatio = 5;     // join gear ration (24:120)
const float joinRange = 310;   // join rotation range [degrees] (322,99)
const float joinMin = -180;    // join minimum position [degrees] (-178,68)
const float joinMax = 140;     // join maximum position [degrees] (144,30)
const int pwmMinimum = 30;     // below this minimum value the motor doesn't work


// GLOBAL VARIABLES
// compute motor encoder parameters
float PPR = encoderSlots * countingRatio * gearRatio * joinRatio; // pulses per rev.
float RES = 360.0 / PPR;             // resolution (degrees per encoder pulse)
float PPD = 1 / RES;                 // encoder pulses per degree
long encoderRange = PPD * joinRange; // join rotation range [pulses]
long encoderMin = PPD * joinMin;     // join minimum position [pulses]
long encoderMax = PPD * joinMax;     // join maximum position [pulses]

// variables used at ISR functions
volatile long encoderValue = 0;     // current encoder count value [pulses]
volatile boolean clockwise = false; // motor direction ---- REMOVE????

// motor parameters
boolean motorStall = false; // motor stall flag
boolean goHome = false;     // homing command
boolean homed = false;      // join has been homed
boolean stall = false;      // stall condition
int homingState = 0;        // state of homing sequence
long stallDelay = 20;      // delay time for motor stall
long startTime = 0;         // startTime for stall flag
float overtake = 10 * PPD;  // overtake home position factor [pulses]
float joinSpeed = 0;      // join speed [%] 

// pid control parameters
boolean pidEnabled = false;
float targetPoint = 0;   // position reference (set point) [degrees]
float currentPoint;      // process varible (position) [degree]
float currentSpeed;      // [rpm]
float pidOutput = 0;     // manipulated variable
float error;             // position error [degrees]
float kp = 2;            // proportional gain
float ki = 0.5;          // integral gain
float kd = 0.1;          // derivative gain  

// serial communication variables
String inputString = "";         // a string to hold incoming data
String token = " ";              // token for separate arguments
boolean stringComplete = false;  // whether the string is complete
boolean verboseMode = true;
boolean echoMode = true;

// image variables
long _encoderValue = 0;     
boolean _clockwise = false; 
boolean _homeValue = false; 
boolean _stall = false;
int _motorValue = 0;

// STRUCTURE FUNCTIONS
/*
 * setup - system initialize 
 */
void setup() {
  // configure inputs
  pinMode(phaseAPin, INPUT_PULLUP);
  pinMode(phaseBPin, INPUT_PULLUP);
  pinMode(homePin, INPUT_PULLUP);

  // configure output
  pinMode(brakePin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(homeLedPin, OUTPUT);

  // encoder signals setup
  attachInterrupt(0, doEncoderA, CHANGE);
  attachInterrupt(1, doEncoderB, CHANGE);

  // timer interrupts configuration
//  Timer1.initialize(long(1e6 * sampleTime)); // set control loop timer interval
//  Timer1.attachInterrupt(pidControl);  // control function interrupt
  
  // start serial port at 9600 bps
  Serial.begin(9600);
}

/*
 *   loop - execute commands receive via serial port and control a scorbot join
 */
 void loop() {
  static String args[MAX_ARGS];
  int errorCode;
  int nargs;

  // read digital inputs
  homeValue = !digitalRead(homePin);

  // execute received command
  if (stringComplete) {
    inputString.toUpperCase();

    // parse inputString
    if (inputString != " ")
      nargs = parseString(inputString, token, MAX_ARGS, args);

    // execute the command
    errorCode = doCommand(args);

    // send echo
    if (echoMode) {
      Serial.println(concatString(args, token));
      if (errorCode == -1)
        Serial.println("ERROR #1: WRONG_PARAMETER");
      else if (errorCode == -2)
        Serial.println("ERROR #2: WRONG_CMD " + args[0]);
    }

    // reset communication variables
    inputString = "";
    stringComplete = false;
  }

  // find join home microswitch
  if (goHome) 
    doHoming();

  if (pidEnabled)
    pidControl();

  // calculate motor stall
  stall = (motorValue >= pwmMinimum) && (_encoderValue == encoderValue);
  if (!_stall && stall) {
    startTime = millis();
    Serial.println("trigger motor stall timer");
  }
  if (stall) {
    if ((millis() - startTime) >= stallDelay) {
      brakeValue = true;
      Serial.println("motor stall");
    }
  }
  
  // write pwm outputs
  if (pidEnabled) {
    dirValue = (pidOutput < 0);
    motorValue = brakeValue ? 0 : limit(abs(pidOutput), 0, 255);
  }
  else
    motorValue = brakeValue ? 0 : map(joinSpeed, 0, 100, pwmMinimum, 255);
  analogWrite(motorPin, motorValue);

  // write digital outputs
  digitalWrite(brakePin, brakeValue);
  digitalWrite(dirPin, dirValue);
  digitalWrite(homeLedPin, homeValue);
  
  // send changes
  if (verboseMode) {
    if (_encoderValue != encoderValue)
      Serial.println("POSITION" + token + String(RES * encoderValue) + " [" + String(encoderValue) + "]");
    if (_clockwise != clockwise)
      Serial.println("DIRECTION" + token + BOOL_TO_STRING(clockwise));
    if (_homeValue != _homeValue)
      Serial.println("HOME" + token + BOOL_TO_STRING(homeValue));
    if (pidEnabled)
      Serial.println("pid (current:target:error:output), = " + String(currentPoint)+ ":" + String(targetPoint) + ":" + String(error) + ":" + String(pidOutput));
  }

  // update image variables
  _encoderValue = encoderValue;
  _clockwise = clockwise;
  _homeValue = homeValue;
  _motorValue = motorValue;
  _stall = stall;
  
  delay(cycleTime);
}

// USERS FUNCTIONS

/*
 * pidControl
 */
void pidControl() {
  static float errorSum;      // accumulated error
  static float _error;        // error previous value
  static float _currentPoint; // process variable previous value 
  float derror;               // derivative error

  currentPoint = RES * encoderValue;
  error = targetPoint - currentPoint;
  errorSum += (error * sampleTime);
  derror = (error - _error) / sampleTime;
  pidOutput = kp * error + ki * errorSum + kd * derror;

  if (abs(error) < 2) {
    pidEnabled = false;
    brakeValue = true;
    dirValue = false;
    errorSum = 0;
    pidOutput = 0;
  }
  
  // register previous data
  _error = error;
  _currentPoint = currentPoint;
}
 
/*
 * doHoming - find home join position
 */
void doHoming() {
  static int preSpeed;
  
  switch (homingState) {
    case 0: // ready
      if (goHome) {
        preSpeed = joinSpeed;
        joinSpeed = 100;
        dirValue = true; // ccw
        brakeValue = false;
        homingState = 1;
        Serial.println("buscando home rapido");
      }
      break;
    case 1: // go quickly towards home micro-switch 
      if (homeValue) {
        encoderValue = 0;
        homingState = 2;
        Serial.println("sobrepasando home");
      }
      else if (brakeValue) { // motor stall because join limit has been reached
        dirValue = false; // cw
        brakeValue = false;
        homingState = 5;
        Serial.println("tope alcanzado, cambio de direccion");
      }
      break;
    case 2: // overtaking home micro-switch
      if (abs(encoderValue) >= overtake) {
        joinSpeed = 50;
        dirValue = false; // cw
        homingState = 3; 
        Serial.println("cambio de direccion, buscando home lento");
      }
      break;
    case 3: // go slowly backwards home micro-switch
      if (homeValue) {
        encoderValue = 0;
        joinSpeed = preSpeed;
        brakeValue = true;
        homed = true;
        goHome = false;
        homingState = 0;
        Serial.println("homming finalizado");
      }
      break;

    case 5: // motor stall, go quickly backwards home micro-switch
      if (homeValue) {
        encoderValue = 0;
        homingState = 6;
        Serial.println("sobrepasando home en contra-direccion");
      }
      break;
    case 6: // overtaking home micro-switch 
      if (abs(encoderValue) >= overtake) {
        dirValue = true; // ccw
        homingState = 1;
        Serial.println("buscando home rapido");
      }
      break;
  }
}

/*
 * BOOL_TO_STRING - 
 */
String BOOL_TO_STRING(boolean b) {
  return (b ? "ON" : "OFF");
}

/*
 * doCommmand - execute commands
 */
int doCommand(String args[]) {
  int errorCode = 0;
  int n;

  if (args[0] == "VERBOSE")
    errorCode = setBoolVar(&verboseMode, args[1]);

  else if (args[0] == "ECHO")
    errorCode = setBoolVar(&echoMode, args[1]);

  else if (args[0] == "VERSION")
    Serial.println(FIRMWARE_VERSION);

  else if (args[0] == "DIR")
    errorCode = setBoolVar(&dirValue, args[1]);
    
  else if (args[0] == "BRAKE")
    errorCode = setBoolVar(&brakeValue, args[1]);

  else if (args[0] == "START")
    errorCode = setBoolVar(&brakeValue, "OFF");

  else if (args[0] == "STOP")
    errorCode = setBoolVar(&brakeValue, "ON");

  else if (args[0] == "HOME")
    if (args[1] == "?")
      Serial.println(BOOL_TO_STRING(homed));
    else
      errorCode = setBoolVar(&goHome, "ON");

  else if (args[0] == "MOTOR")
    Serial.println("Motor value = " + String(motorValue));
    
  else if (args[0] == "RESET") {
    joinSpeed = 0;
    brakeValue = true;
    dirValue = false;
    homingState = 0;
    goHome = false;
    pidEnabled = false;
  }
    
  else if (args[0] == "SPEED")
    if ((args[1] == "?") || (args[1] == NULL))
      Serial.println(String(joinSpeed));
    else if (args[1] == "+")
      joinSpeed = limit(2 * joinSpeed, 0, 100);
    else if (args[1] == "-")
      joinSpeed = limit(joinSpeed / 2, 0, 100);
    else if (isValidNumber(args[1]))
      joinSpeed = limit(args[1].toFloat(), 0, 100);
    else
      errorCode = -1;

  else if (args[0] == "COUNTER")
    if ((args[1] == NULL) || (args[1] == "?"))
      Serial.println(String(encoderValue));
    else if (args[1] == "RESET")
      encoderValue = 0;
    else
      errorCode = -1;

  else if (args[0] == "POSITION")
    if ((args[1] == NULL) || (args[1] == "?"))
      Serial.println(String(RES * encoderValue));
    else
      errorCode = -1;

  else if (args[0] == "GO") {
    if (isValidNumber(args[1])) {
      targetPoint = limit(args[1].toFloat(), joinMin, joinMax);
      pidEnabled = true;
      brakeValue = false;
      Serial.println("pid enabled, go to : " + String(targetPoint) + " [degrees]");
    }
    else
      errorCode = -1;
  }
    

  else
    errorCode = -2;

  return errorCode;
}

/*
 * doEncoderA - ISR function for encoder phase A external interrupt
 *
 * If pinA and pinB are both high or both low, it is spinning
 * forward. If they're different, it's going backward.
 */
void doEncoderA () {
  if (digitalRead(phaseAPin) == digitalRead(phaseBPin)) {
    encoderValue++;
    clockwise = true;
  }
  else {
    encoderValue--;
    clockwise = false;
  }
}

/*
 * doEncoderB - ISR function for encoder phase B external interrupt
 *
 * If pinA and pinB are one high and the other low, it is spinning
 * forward. If they're equal, it's going backward.
*/
void doEncoderB () {
  if (digitalRead(phaseAPin) != digitalRead(phaseBPin)) {
    encoderValue++;
    clockwise = true;
  }
  else {
    encoderValue--;
    clockwise = false;
  }
}

/*
 * SerialEvent - get a message from serial RX
 *
 * thanks to Tom Igoe
 *
 * retrieved from: https://www.arduino.cc/en/Tutorial/SerialEvent
 *
 * SerialEvent occurs whenever a new data comes in the
 * hardware serial RX.  This routine is run between each
 * time loop() runs, so using delay inside loop can delay
 * response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n')
      stringComplete = true;
    else
      // add it to the inputString:
      inputString += inChar;
  }
}

/*
 * parseString - split a string into words
 *
 * based on "void ParseSerialData()" (dyadica)
 *
 * retrieved from: http://www.dyadica.co.uk/simple-serial-string-parsing/
 */
int parseString(String s, String token, int max_args, String args[]) {
  char *str;
  char *p;
  String tmp;
  int count;

  tmp = s;

  // get words from a string
  p = &tmp[0];
  count = 0;
    while ((str = strtok_r(p, &token[0], &p)) != NULL) {
    // Add chunk to array
    args[count] = str;
    // Increment data count
    count++;
    if (count > max_args)
      return count - 1;
  }
  args[count] = "";

  return count;
}

/*
 * concatString - concatenate words in a single string
 */

String concatString(String args[], String token) {
  String s;
  int i = 1;

  s = args[0];

  if (s != "")
    while (args[i] != "")
      s = s + token + args[i++];

  return s;
}

/*
 * isValidNumber - check if a string is a valid number
 *
 * IMPORTANTE: es necesario mejorar el orden en el que aparecen los caracteres especiales
 * e incluir la verificacion de reales con e
 *
 * thanks to "hbx2013"
 *
 * retrieved from: http://forum.arduino.cc/index.php?topic=209407.0
 */
boolean isValidNumber(String str) {
  boolean isNum = false;
  for (byte i = 0; i < str.length(); i++)
  {
    isNum = isDigit(str.charAt(i)) || str.charAt(i) == '+' || str.charAt(i) == '.' || str.charAt(i) == '-';
    if (!isNum) return false;
  }
  return isNum;
}

/*
 * setBoolVar - set/get the value of an boolean variable
 */
int setBoolVar (boolean *b, String cmd) {
  int errorCode = 0;

  if (cmd == "?")
    Serial.println(BOOL_TO_STRING(*b));
  else if (cmd == NULL)
    *b = !*b;
  else if (cmd == "ON")
    *b = true;
  else if (cmd == "OFF")
    *b = false;
  else
    errorCode = -1;

  return errorCode;
}


