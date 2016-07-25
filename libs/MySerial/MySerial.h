#ifndef MySerial_h
#define MySerial_h
#include"Arduino.h"


class MySerial{

  public:
    MySerial(){};
    ~MySerial(){};
    int parseString(String s, String token, int max_args, String args[]); 

    
  private:
    
};


#endif
