#include "MySerial.h"

int MySerial::parseString(String s, String token, int max_args, String args[]){
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
    };