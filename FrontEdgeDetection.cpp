//LIBRARIES
#include "FrontEdgeDetection.h"
#include "TINAH.h"

#define QRD_EDGE 6


TINAH::Servo plankServo(TINAH::pins::servo[1]);
//TINAH::Servo secondPlankServo(TINAH::pins::servo[2]);
extern TINAH::BufferedLCD LCD;



/*

  bool edgeVerify = false;
  int edgeVerifynum = 0;
  int maxVerifynum = 3;
*/
//unsigned long cMillis;
//long wait = 10;

int firstPlankStart = 0;//0;
int firstPlankEnd = 170;
int secondPlankStart = 88;
int secondPlankEnd = 170;//120;

unsigned long edgeMillis;
long waiting = 10;
boolean verifyEdge = false;

int thEdgeDistance = 800;



FrontEdgeDetection::FrontEdgeDetection() {
  _thDistance = 10;

};

void FrontEdgeDetection:: StartPosition () {
  plankServo.write(firstPlankStart);
  delay(150);
  plankServo.detach();
  }

/*boolean FrontEdgeDetection::EdgeDetected(int dist) {

  int thresholdDistance = 12;
    if (dist > thresholdDistance) {
      //Serial.print("EWOOOOKKKK");

      /*if(!edgeVerify){
        cMillis = millis();
        edgeVerify = true;
        }*/

/* if (edgeVerifynum == 0) {
   cMillis = millis();
   edgeVerifynum++;

  }
  }
  else {
  cMillis = -1;
  edgeVerifynum = 0;

  }

  if (millis() > (cMillis + wait)) {
  edgeVerify = false;
  //edgeVerifynum = 0;
  if (dist > thresholdDistance) {
   edgeVerifynum++;
   cMillis = millis();

   if (edgeVerifynum == maxVerifynum) {
  //   Serial.print("Edge Detected");
   //  Serial.print("edge distance");
     //Serial.println(dist);
     return true;
   }

  }


  }
  };
*/

void FrontEdgeDetection::firstEdge() {

  for (int pos = firstPlankStart; pos <= firstPlankEnd; pos += 5) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    plankServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }

  delay(250);
  plankServo.detach();

};


void FrontEdgeDetection::secondEdge() {

  for (int pos = secondPlankStart; pos <= secondPlankEnd; pos += 5) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    plankServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }

  delay(250);
  plankServo.detach();

  //plankServo.write(0);

};

/*
  boolean FrontEdgeDetection::EdgeDetectedLow(int dist) {

  int thresholdDistance = 6;
    if (dist > thresholdDistance) {
      //Serial.print("EWOOOOKKKK");

      /*if(!edgeVerify){
        cMillis = millis();
        edgeVerify = true;
        }*/

/* if (edgeVerifynum == 0) {
   cMillis = millis();
   edgeVerifynum++;

  }
  }
  else {
  cMillis = -1;
  edgeVerifynum = 0;

  }

  if (millis() > (cMillis + wait)) {
  edgeVerify = false;
  //edgeVerifynum = 0;
  if (dist > thresholdDistance) {
   edgeVerifynum++;
   cMillis = millis();

   if (edgeVerifynum == maxVerifynum) {
  //   Serial.print("Edge Detected");
   //  Serial.print("edge distance");
     //Serial.println(dist);
     return true;
   }

  }


  }
  };
*/

boolean FrontEdgeDetection::EdgeDetectedQRD() {
  //LCD.begin(true, false);
  //LCD.clear();
 // int qrdReading = analogRead(QRD_FAR);

  if (analogRead(QRD_EDGE) > thEdgeDistance) {

    if (!verifyEdge) {
      edgeMillis = millis();
      verifyEdge = true;
    }
  }
  else {
    edgeMillis = -1;

  }

  if (millis() > (edgeMillis + waiting)) {
    verifyEdge = false;
    if ( analogRead(QRD_EDGE > thEdgeDistance)) {
      return true;
    }

  } else {
    //  Serial.println(" out of range ");
    return false;
  }

  //Serial.println(qrdReading);


  // LCD.home();
  //LCD.setCursor(0, 0); LCD.print(qrdReading);
  //LCD.flush();


};



