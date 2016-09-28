
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
int     serialBaud            = 9600; 

/**  GLOBAL VARIABLES ------------------------------------------------------------------------*/

bool          masterFlag    = true;
vector<int>   axisId;
//this instance of My serial is injected in myarduino instance as an agreggation
Order         injectedOrder = Order();
MySerial      mySerial = MySerial(serialBaud,token,injectedOrder,"DEBUG");
//delete(injectedOrder) ??
MyArduino     myArduino = MyArduino(&mySerial,masterFlag);
bool          serialError  = false; 

#endif
