#include "TINAH.h"
#include "Claws.h"

#define COURSESTATE1 1
#define COURSESTATE2 2
#define switchRight 6
#define switchLeft 5

//TINAH::Servo rightArm(TINAH::pins::servo[1]);
TINAH::Servo leftArm(12);
TINAH::Servo rightArm(15);//right arm

TINAH::Servo rightGrab(14);
TINAH::Servo leftGrab(13);

int clawArmLiftStartRight = 180;//160;
int clawArmLiftEndRight = 30;//20;


int clawGrabGripStartRight = 180;//160;
int clawGrabGripEndRight = 45;//65;


int homeRight = 165;



int clawArmLiftStartLeft = 15;//160;
int clawArmLiftEndLeft = 180;//20;
int homeLeft = 30;


int clawGrabGripStartLeft = 0;//160;
int clawGrabGripEndLeft = 95;//75;

int delayTime = 1000;


Claws::Claws() {



}

boolean Claws::pickUpEwok(int courseState) {
  int count = 0;
  switch (courseState) {
    case 1:

      rightGrab.write(clawGrabGripEndRight);
      delay(delayTime);

      rightArm.write(clawArmLiftEndRight);
      delay(delayTime);



      rightGrab.write(clawGrabGripStartRight);
      delay(delayTime);

      rightArm.write(clawArmLiftStartRight);
      delay(delayTime);

      rightGrab.write(clawGrabGripEndRight);
      delay(delayTime);



      rightArm.write(homeRight);
      delay(delayTime);

      rightArm.write(clawArmLiftStartRight);
      delay(350);
      rightArm.write(homeRight);
      delay(350);

      rightGrab.detach();
      rightArm.detach();
      break;
    //leftArm.write(clawArmLiftStartRight);
    //leftGrab.write(clawGrabGripStartRight);
    //break;

    case 2:
      // Serial.println("In state 2");
      leftGrab.write(clawGrabGripEndLeft);
      delay(delayTime);

      leftArm.write(clawArmLiftEndLeft);
      delay(delayTime);



      leftGrab.write(clawGrabGripStartLeft);
      delay(delayTime);

      leftArm.write(clawArmLiftStartLeft);
      delay(delayTime);

      leftGrab.write(clawGrabGripEndLeft);
      delay(delayTime);

      leftArm.write(homeLeft);

      leftArm.write(clawArmLiftStartLeft);
      delay(350);
      leftArm.write(homeLeft);
      delay(350);

      delay(delayTime);
      leftGrab.detach();
      leftArm.detach();
      break;

  }



};

void Claws::DropBothClaws() {

  rightArm.write(clawArmLiftStartRight);
  delay(350);
  rightArm.write(homeRight);
  delay(350);
  rightArm.write(clawArmLiftStartRight);
  delay(350);
  rightArm.write(homeRight);
  delay(350);

  rightArm.write(clawArmLiftEndRight);
  delay(delayTime);


  leftArm.write(clawArmLiftStartLeft);
  delay(350);
  leftArm.write(homeLeft);
  delay(350);
  leftArm.write(clawArmLiftStartLeft);
  delay(350);
  leftArm.write(homeLeft);
  delay(350);


  leftArm.write(clawArmLiftEndLeft);
  delay(delayTime);



  rightArm.detach();
  leftArm.detach();

};

void Claws::ReturnToHome() {
  rightArm.write(homeRight);
  delay(delayTime);


  leftArm.write(homeLeft);
  delay(delayTime);

  rightArm.detach();
  leftArm.detach();



}



/*boolean debounceButton(int switchPin)
  {
  int debounceTime  = 40;
  if (digitalRead(switchPin) == HIGH) return false;
  delay(debounceTime);
  return !digitalRead(switchPin);


  };*/




