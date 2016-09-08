
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
#include <MySerial.h>
#include <MyI2C.h>
#include <MyAxis.h>
#include "Order.h"

using namespace std;
bool        iAmMaster  = true;
// serial communication variables
char token = ' ';              // token for separate arguments
int SerialBaud = 9600; 
int MaxSentenceComponents = 10;


#endif
