
/*
------------------------------------------------------------------------------------------------
0         1         2         3         4         5         6         7         8         9
012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345
------------------------------------------------------------------------------------------------
*/

#ifndef config_h
#define config_h

#include <MySerial.h>



// Serial communication variables
char token = ' ';              // token for separate arguments
int SerialBaud = 9600; 
int MaxSentenceComponents = 10;


/**  GLOBAL VARIABLES ------------------------------------------------------------------------*/
MySerial    mySerial   = MySerial(SerialBaud,token,MaxSentenceComponents);
bool        serialError= false; 



#endif
