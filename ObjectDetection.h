#ifndef objDec
#define objDec

#include "Arduino.h"
#include "TINAH.h"
#include "Adafruit_VL53L0X.h"

class ObjectDetection{
  public:
    ObjectDetection();
    boolean objectDetect(int courseState, Adafruit_VL53L0X lox);
    void resetSensors(Adafruit_VL53L0X lox);

  private:
      
   //Adafruit_VL53L0X lox;
  
};







#endif

