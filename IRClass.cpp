#define voltageConversion 0.00488758553275

//LIBRARIES
#include "FrontEdgeDetection.h"
#include "IRClass.h"
#include "TINAH.h"


extern TINAH::BufferedLCD LCD;

float diffThresh = 0.1;
int tenK = 6;
int oneK = 7;

IRClass::IRClass() {};

boolean IRClass::tenKfreqDetect() {

  if ((analogRead(tenK) - analogRead(oneK)) * (voltageConversion) > diffThresh) {

    LCD.begin(true, false);
    LCD.setCursor(0, 0);
    LCD.println("GO");
    LCD.flush();
    LCD.clear();

    return true;
  }
  else
    return false;
};


boolean IRClass::oneKfreqDetect() {
  if ((analogRead(oneK) - analogRead(tenK)) * (voltageConversion) > diffThresh) {

    LCD.begin(true, false);
    LCD.setCursor(0, 0);
    LCD.println("STOP");
    LCD.flush();
    LCD.clear();

    return true;
  }
  else
    return false;
};
