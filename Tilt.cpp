#include "Tilt.h"
#include "PIDClass.h"

#define LIMITSWITCH_RIGHT 6
#define LIMITSWITCH_LEFT 5

extern PIDClass PidController;

TINAH::Servo tiltServoMotor(10);
int tiltServoStart = 95;
int tiltServoEnd = 0;
int delayTimeTilt = 2000;

Tilt::Tilt() {
  _doneTilting = false;
}


void Tilt::reverseAndTilt() {

  while (!_doneTilting) {
    if (!debounceButton(LIMITSWITCH_RIGHT) && !debounceButton(LIMITSWITCH_LEFT)) {
      PidController.reverseBoth();
    }

    else if (!debounceButton(LIMITSWITCH_RIGHT) && debounceButton(LIMITSWITCH_LEFT)) {
      PidController.reverseRight();
    }

    else if (debounceButton(LIMITSWITCH_RIGHT) && !debounceButton(LIMITSWITCH_LEFT)) {
      PidController.reverseLeft();
    }

    else if (debounceButton(LIMITSWITCH_RIGHT) && debounceButton(LIMITSWITCH_LEFT)) {
      PidController.stopCompletely();
      // tiltServo();
      _doneTilting = true;

    }
  }


};

boolean Tilt::debounceButton(int switchPin)
{
  int debounceTime  = 40;
  if (digitalRead(switchPin) == HIGH) return false;
  delay(debounceTime);
  return !digitalRead(switchPin);


};

void Tilt::tiltServo() {

  for (int pos = tiltServoEnd; pos <= tiltServoStart; pos += 5) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    tiltServoMotor.write(pos);              // tell servo to go to position in variable 'pos'
    delay(100);                       // waits 15ms for the servo to reach the position


  }



  delay(delayTimeTilt);

  for (int i = 0; i < 5; i++) {
    tiltServoMotor.write(75);
    delay(200);
    tiltServoMotor.write(95);
    delay(200);
  }




  /*
    for (int pos = tiltServoStart; pos >= tiltServoEnd; pos -= 5) { // goes from 180 degrees to 0 degrees
      tiltServoMotor.write(pos);              // tell servo to go to position in variable 'pos'
      delay(70);                       // waits 15ms for the servo to reach the position
    }
  */

  tiltServoMotor.detach();
  delay(500);
}





