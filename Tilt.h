#ifndef Tilter
#define Tilter





#include "Arduino.h"
#include "TINAH.h"

class Tilt {
  public:
    Tilt();
    void reverseAndTilt();
    void tiltServo();

  private:
    boolean debounceButton(int switchPin);
    boolean _doneTilting;


};















#endif
