
/*
------------------------------------------------------------------------------------------------
0         1         2         3         4         5         6         7         8         9
012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345
------------------------------------------------------------------------------------------------
*/

#ifndef config_h
#define config_h

#define FIRMWARE_VERSION "scorbotArduino Version 1.0.0 - 2016/09/11"

#include <Order.h>
#include <MySerial.h>
#include <MyArduino.h>

// Serial communication variables
char    token                 = ' ';              // token for separate arguments
int     SerialBaud            = 9600; 
int     MaxSentenceComponents = 10;

/**  GLOBAL VARIABLES ------------------------------------------------------------------------*/

bool          iAmMaster    = true;
vector<int>   axisId;
MySerial      mySerial     = MySerial(SerialBaud,token,MaxSentenceComponents);
MyArduino     myArduino    = MyArduino();
vector<Order> orders;
vector<Order> orders2Slaves;
bool          serialError  = false; 





#endif
