#include "ObjectDetection.h"
#include "TINAH.h"
#include "Adafruit_VL53L0X.h"

 

extern constexpr int shutDownPinRight = 35;

extern constexpr int shutDownPinLeft = 31;

unsigned long currMillis;
long waitTime = 5;




ObjectDetection::ObjectDetection() {
  /*lox = Adafruit_VL53L0X();
    if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
    }*/
}

VL53L0X_RangingMeasurementData_t measure;

boolean verify = false;
boolean ObjectDetection::objectDetect(int courseState, Adafruit_VL53L0X lox) {
  //Adafruit_VL53L0X lox = Adafruit_VL53L0X();
  /* if (!lox.begin()) {
     //Serial.println(F("Failed to boot VL53L0X"));
     while(1);
    }*/

  /* switch (courseState) {
     case 1:
       analogWrite(SHUTDOWNRight, HIGH);
       analogWrite(SHUTDOWNLeft, LOW);
       break;
     case 2:
       analogWrite(SHUTDOWNRight, LOW);
       analogWrite(SHUTDOWNLeft, HIGH);
       break;
    }*/

  if(courseState == 1){
    analogWrite(shutDownPinRight, 255);
    analogWrite(shutDownPinLeft, 0);
    
  }else if(courseState == 2){
    analogWrite(shutDownPinRight, 0);
    analogWrite(shutDownPinLeft, 255);
  } 

  //Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    //Serial.print("Distance (mm): ");
    Serial.println(measure.RangeMilliMeter);


    if (measure.RangeMilliMeter < 120) {
      //Serial.print("EWOOOOKKKK");
      
      if(!verify){
        currMillis = millis();
        verify = true;
      }
    }
    else {
      currMillis = -1;
      
    }

    if (millis() > (currMillis + waitTime)) {
      verify = false;
      if (measure.RangeMilliMeter < 120) {
        return true;
      }
      
    }


    //  if(verify>1){
    //  verify = 0;
    //return true;
    //}

    //}else{
    //verify = 0;
    //}
  } else {
    Serial.println(" out of range ");
    return false;
  }




  return false;
};

void ObjectDetection::resetSensors(Adafruit_VL53L0X lox){
  
   analogWrite(shutDownPinLeft, 0);
      analogWrite(shutDownPinRight, 0);
      delay(10);
      analogWrite(shutDownPinLeft, 255);
      analogWrite(shutDownPinRight, 255);
      delay(10);
      if (!lox.begin()) {
       // Serial.println(F("Failed to boot VL53L0X"));
        while (1);
      }
      
     
};

