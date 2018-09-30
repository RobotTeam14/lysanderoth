#ifndef IR
#define IR

#include "Arduino.h"
#include "TINAH.h"

class IRClass {
  public:

    IRClass();
    boolean tenKfreqDetect();
    boolean oneKfreqDetect();

};

#endif
