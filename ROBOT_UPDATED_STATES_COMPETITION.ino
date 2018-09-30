#include "PIDClass.h"
#include "ObjectDetection.h"
#include "Claws.h"
#include "FrontEdgeDetection.h"
#include "IRClass.h"
#include "Tilt.h"
#include "EdgeNavigation.h"
#include "NewPing.h"

#include <TINAH.h>
////////////////////////////////////////////
//GLOBALS
#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1

constexpr int shutDownPinRight = 31;
constexpr int shutDownPinLeft = 35;



TINAH::HBridge leftMotorBridge(LEFT_MOTOR);
TINAH::HBridge rightMotorBridge(RIGHT_MOTOR);
TINAH::BufferedLCD LCD;

//CONSTANTS:
constexpr int knob_1 = 6; //k_d
constexpr int knob_2 = 7; //k_p


/////////////////////////////////////////////

enum CourseState {
  FIRSTSEC,
  SECONDEWOK,
  IRSEC,
  EDGEEND,
  THIRDEWOK,
  TILTSEC,
  SECONDEDGE,
  SECONDEDGEDROP,
  NEWSECONDEDGEDROP,
  FOURTHEWOK,
  EDGENAVIGATE,
  TESTQRD,
  THIRDEDGE,
  END
};

CourseState cS = CourseState::FIRSTSEC;
//CourseState cS = CourseState::THIRDEWOK;
//CourseState cS = CourseState::IRSEC;
//CourseState cS = CourseState::TILTSEC;
//CourseState cS = SECONDEDGE;
//CourseState cS = EDGEEND;
//CourseState cS = TESTQRD;


Adafruit_VL53L0X lox = Adafruit_VL53L0X();
int trigPin = 8;
int echoPin = 7 ;
int currentTimeSED = millis();



boolean startTape = false;
unsigned long sonarEdgeMillis;
long sonarWaiting = 10;
boolean verifySonarEdge = false;

int thEdge = 10;



PIDClass PidController;
ObjectDetection EwokDetection;
IRClass IRdet;
Claws EwokClaws;
FrontEdgeDetection EdgeObject;
Tilt TiltingObject;
EdgeNavigation EdgeNav;



void setup() {

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);


  pinMode(shutDownPinRight, OUTPUT);
  pinMode(shutDownPinLeft, OUTPUT);

  Serial.begin(9600);


  analogWrite(shutDownPinRight, 255);
  analogWrite(shutDownPinLeft, 255);

  // EdgeObject.StartPosition();


  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while (1);
  }


  // Serial.println("FINISHED SETUP");
}

//NewPing sonar(trigPin, echoPin, 40);
int clawStateVal;
int count = 0;
boolean firstplankFallen = false;
boolean secondplankFallen = false;
boolean first = true;

boolean tilting = true;
boolean secondedge = false;
boolean detected1K = false;


boolean start = false;

void loop() {

  while (start == false && digitalRead(TINAH::pins::startButton)) {


  }

  start = true;

  switch (cS) {
    case FIRSTSEC:

      clawStateVal = 1;

      // EdgeNav.edgeDetected();

      if (EwokDetection.objectDetect(clawStateVal, lox) == true) {
        PidController.stopCar();
        PidController.stopCar();

        EwokClaws.pickUpEwok(clawStateVal);

      }

      //else if (EdgeObject.EdgeDetected(sonar.ping_cm())) {
      else if (EdgeDetected()) {

        // else if(EdgeNav.edgeDetected()){

        //  PidController.stopCompletely();
        //delay(9000);
        /*PidController.stopCar();
          PidController.stopCar();
          PidController.stopCar();
          PidController.stopCar();*/
        // EdgeNav.edgeAlign();

        PidController.plankReverse();
        // delay(3000);

        if (!firstplankFallen) {
          EdgeObject.firstEdge();
          delay(2000);
          PidController.jerkCar();
          PidController.stopCompletely();
          delay(500);
          firstplankFallen = true;
          PidController.goForward();
          delay(1000);
          PidController.firstPlankCross();
          delay(600);
          PidController.searchTapeRight();
          EwokDetection.resetSensors(lox);
          cS = CourseState::SECONDEWOK;

        }
      }


      else {
        PidController.tapeFollow();
      }


      break;

    case SECONDEWOK:
      //  Serial.println("IM HERE");
      clawStateVal = 1;

      if (EwokDetection.objectDetect(clawStateVal, lox) == true) {
        PidController.stopCar();
        PidController.stopCar();
        EwokClaws.pickUpEwok(clawStateVal);

        cS = CourseState::IRSEC;
        // cS = CourseState::EDGEEND;

      } else {
        PidController.tapeFollowSpeed(75);
      }
      break;


    case IRSEC:



      if (IRdet.tenKfreqDetect() && !IRdet.oneKfreqDetect() ) {

        if (!detected1K) {
          PidController.stopCompletely();

          //PidController.stopCar();
        }
        else {
          cS = CourseState :: EDGEEND;
        }
      }
      /* while (!IRdet.oneKfreqDetect()) {
         PidController.stopCompletely();

        }
        while (!IRdet.tenKfreqDetect()) {
         PidController.stopCompletely();
        }
        cS = CourseState :: EDGEEND;*/


      else if (!IRdet.tenKfreqDetect() && IRdet.oneKfreqDetect()) {
        PidController.stopCompletely();
        //PidController.stopCar();
        detected1K = true;
        // while (!IRdet.tenKfreqDetect()) {
        // PidController.stopCompletely();
        //}
        //cS = CourseState :: EDGEEND;
      }

      else {
        // PidController.tapeFollow();
        PidController.tapeFollowSpeed(55);
        //PidController.tapeFollowSpeedingUp(60, first);
        first = false;
      }
      break;

    case EDGEEND:
      clawStateVal = 2;

      if (EdgeDetected()) {
        PidController.stopCar();
        EwokDetection.resetSensors(lox);

        cS = CourseState::THIRDEWOK;


      } else {
        PidController.tapeFollow();


      }

      break;

    case THIRDEWOK:
      clawStateVal = 2;
      //   Serial.print("THIRDEWOK STATE");
      if (EwokDetection.objectDetect(clawStateVal, lox) == true) {
        //PidController.stopCompletely();
        PidController.stopCarForward();
        EwokClaws.pickUpEwok(clawStateVal);

        /*  while (!EdgeDetected()) {
            PidController.goForward();
          }

          PidController.stopCar();*/

        cS = CourseState::THIRDEDGE;
      }

      else {
        //PidController.tapeFollow();
        PidController.reverseBoth();

      }
      break;

    case THIRDEDGE:

      if (EdgeDetected()) {
        //   if(EdgeNav.edgeDetected()){
        PidController.stopCar();
        cS = CourseState::TILTSEC;

      }

      else {
        PidController.goForward();
      }

      break;

    case TILTSEC:

      if (tilting) {

        PidController.stopCar();

        delay(2000);


        PidController.assToWall();
        PidController.stopCompletely();
        delay(1000);

        TiltingObject.reverseAndTilt();
        EwokClaws.DropBothClaws();
        TiltingObject.tiltServo();
        //EwokClaws.ReturnToHome();




        tilting = false;
        cS = CourseState::END;

      }

      break;

    case END:

      PidController.stopCompletely();
      break;

    case NEWSECONDEDGEDROP:
      clawStateVal = 2;

      if (EdgeDetected()) {
        PidController.stopCar();
        PidController.stopCar();
        EdgeObject.secondEdge();
        delay(2000);
        PidController.jerkCar();
        PidController.stopCompletely();
        delay(500);
        PidController.goForwardFast();
        delay(2000);

        /* int speedPlankTWO = 130;

          while(speedPlankTWO < 200 ){
           PidController.goForwardSpeed(speedPlankTWO);
           delay(100);
           speedPlankTWO += 5;

          }*/



        EwokDetection.resetSensors(lox);

        cS = CourseState::FOURTHEWOK;


      } else {
        PidController.goForward();


      }

      break;



    case FOURTHEWOK:
      clawStateVal = 2;
      while (EwokDetection.objectDetect(clawStateVal, lox) == false) {
        PidController.turnRight();
      }
      PidController.stopCompletely();
      EwokClaws.pickUpEwok(clawStateVal);
      cS = CourseState::EDGENAVIGATE;


      break;


    case EDGENAVIGATE:
      if (EwokDetection.objectDetect(clawStateVal, lox) == true) {
        PidController.stopCompletely();


      } else {
        EdgeNav.edgeNavigate();
      }

      break;



      /*    case TESTQRD:

            EdgeObject.EdgeDetectedQRD();
            break;

      */

  }
}



int dist() {

  digitalWrite(trigPin, LOW);
  //int currentTimedist = micros();
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds

  digitalWrite(trigPin, HIGH);
  //currentTimedist = micros();

  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  int distance = duration * 0.034 / 2;

  //Serial.print("Distance: ");
  //Serial.println(distance);
  return distance;


  /* int distance = sonar.ping_cm();
    Serial.println(distance);

    return sonar.ping_cm();*/
};

boolean EdgeDetected() {

  if (dist() > 10) {
    return true;
  }

  else {
    return false;
  }

  /*  if (!verifySonarEdge) {
      sonarEdgeMillis = millis();
      verifySonarEdge = true;
    }
    }
    else {
    sonarEdgeMillis = -1;

    }

    if (millis() > (sonarEdgeMillis + sonarWaiting)) {
    verifySonarEdge = false;
    if ( dist() > thEdge) {
      return true;
    }

    } else {
    //  Serial.println(" out of range ");
    return false;
    }*/
};
