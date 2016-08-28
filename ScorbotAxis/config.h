
/*
------------------------------------------------------------------------------------------------
0         1         2         3         4         5         6         7         8         9
012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345
------------------------------------------------------------------------------------------------
*/

#ifndef config_h
#define config_h
#include"Arduino.h"

// INCLUDE LIBRARIES C/C++
#include <StandardCplusplus.h>
#include <serstream>
#include <string>
#include <vector>
#include <iterator>
#include <Wire.h>
// My libraries
#include <Logging.h>
#include <MySerial.h>
#include <MyI2C.h>
#include <MyAxis.h>

using namespace std;
// librerias de standarcpluplus no utilizadas
//#include <system_configuration.h>
//#include <unwind-cxx.h>
//#include <utility.h>
// MACROS
#define limit(x,minimum,maximum) (min(max(x,minimum),maximum))

// USER TYPES

// CONSTANTS
#define FIRMWARE_VERSION "scorbot_arduino_0_8 2016.06.18"

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


bool        iAmMaster  = true;



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
char token = ' ';              // token for separate arguments
boolean verboseMode = true;
boolean echoMode = true;

// image variables
long _encoderValue = 0;     
boolean _clockwise = false; 
boolean _homeValue = false; 
boolean _stall = false;
int _motorValue = 0;

#endif
