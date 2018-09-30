//TAPE FOLLOW READINGS
#define QRD_LEFT 1
#define QRD_RIGHT 0



//LIBRARIES
#include "PIDClass.h"
#include "TINAH.h"


int thresholdSpeed = 115;
int stopThresholdSpeed = -200;
int stopCarThreshold = -45;
int minBlackTapeVoltage_Left = 100;
int minBlackTapeVoltage_Right = 100;
int reverseSpeed = -80;

unsigned long kMillis;
long timeWait = 2000;


extern constexpr int knob_1 = 6; //k_d
extern constexpr int knob_2 = 7; //k_p
extern TINAH::HBridge leftMotorBridge;
extern TINAH::HBridge rightMotorBridge;
extern TINAH::BufferedLCD LCD;

PIDClass::PIDClass()
{

  //Serial.println("PIDcontroller initialized");

  _thresholdSpeed = thresholdSpeed;
  _qrd_left = QRD_LEFT;
  _qrd_right = QRD_RIGHT;
  _minBlackTapeVoltage_Left = minBlackTapeVoltage_Left;
  _minBlackTapeVoltage_Right = minBlackTapeVoltage_Right;
  _error;
  _pidState = ON;
  _control;
  _lasterr;
  //ObjectDetection ewokDetection;

}




void PIDClass::tapeFollow() {
  //Serial.print("Speed: ");
  //Serial.println(_thresholdSpeed);

  _pidState = tapeFollowState::ON;
  int _k_p = 10;//15;//analogRead(knob_2)/4;
  int _k_d = 7;//15;//analogRead(knob_1)/4;

  errorCalc();




  float P = _k_p * _error;
  float D = _k_d * (_error - _lasterr);
  _control = P + D;

  leftMotorBridge.setOutput(_thresholdSpeed - _control);
  rightMotorBridge.setOutput(_thresholdSpeed + _control);
  _lasterr = _error;
  LCD.begin(true, false);
  LCD.clear();
  LCD.home();
  //LCD.setCursor(0, 0); LCD.print("Lasterr:") + LCD.print(_lasterr); + LCD.print(" Kd:") + LCD.print(_k_d)  ;
  LCD.setCursor(0, 0); LCD.print("Lasterr:") + LCD.print(_lasterr) + LCD.print(" D:") + LCD.print(D)  ;

  //LCD.setCursor(0, 1); LCD.print("e:") + LCD.print(_error) + LCD.print(" r:") + LCD.print(_thresholdSpeed - _control) + LCD.print(" l:") + LCD.print(_thresholdSpeed + _control);
  LCD.setCursor(0, 1); LCD.print("e:") + LCD.print(_error) + LCD.print(" t:") + LCD.print(_thresholdSpeed) + LCD.print(" c:") + LCD.print(_control);


  //Serial.print("Lasterr: ");
  //Serial.println(_lasterr);
  //Serial.print("D: ");
  //  Serial.println(D);


 LCD.flush();


};

void PIDClass:: goForwardFast(){
  leftMotorBridge.setOutput( _thresholdSpeed + 20);
  rightMotorBridge.setOutput( _thresholdSpeed + 20);

  }


void PIDClass::tapeFollowSpeed(int speedThreshold) {
  //Serial.print("Speed: ");
  //Serial.println(_thresholdSpeed);

  _pidState = tapeFollowState::ON;
  int _k_p = 10;//15;//analogRead(knob_2)/4;
  int _k_d = 7;//15;//analogRead(knob_1)/4;

  errorCalc();




  float P = _k_p * _error;
  float D = _k_d * (_error - _lasterr);
  _control = P + D;

  leftMotorBridge.setOutput(speedThreshold - _control);
  rightMotorBridge.setOutput(speedThreshold + _control);
  _lasterr = _error;
 /* LCD.begin(true, false);
  LCD.clear();
  LCD.home();
  //LCD.setCursor(0, 0); LCD.print("Lasterr:") + LCD.print(_lasterr); + LCD.print(" Kd:") + LCD.print(_k_d)  ;
  LCD.setCursor(0, 0); LCD.print("Lasterr:") + LCD.print(_lasterr) + LCD.print(" D:") + LCD.print(D)  ;

  //LCD.setCursor(0, 1); LCD.print("e:") + LCD.print(_error) + LCD.print(" r:") + LCD.print(_thresholdSpeed - _control) + LCD.print(" l:") + LCD.print(_thresholdSpeed + _control);
  LCD.setCursor(0, 1); LCD.print("e:") + LCD.print(_error) + LCD.print(" t:") + LCD.print(speedThreshold) + LCD.print(" c:") + LCD.print(_control);

*/
  //Serial.print("Lasterr: ");
  //Serial.println(_lasterr);
  //Serial.print("D: ");
  //  Serial.println(D);


  //LCD.flush();


};

void PIDClass::tapeFollowSpeedingUp(int speedThreshold, boolean start) {
  //Serial.print("Speed: ");
  //Serial.println(_thresholdSpeed);

  _pidState = tapeFollowState::ON;
  int _k_p = 10;//15;//analogRead(knob_2)/4;
  int _k_d = 7;//15;//analogRead(knob_1)/4;

  errorCalc();




  float P = _k_p * _error;
  float D = _k_d * (_error - _lasterr);
  _control = P + D;

if(start){
  kMillis = millis();
  }

   if (millis() > (kMillis + timeWait)) {
    speedThreshold = _thresholdSpeed;

      }

  leftMotorBridge.setOutput(speedThreshold - _control);
  rightMotorBridge.setOutput(speedThreshold + _control);
  _lasterr = _error;
 /* LCD.begin(true, false);
  LCD.clear();
  LCD.home();
  //LCD.setCursor(0, 0); LCD.print("Lasterr:") + LCD.print(_lasterr); + LCD.print(" Kd:") + LCD.print(_k_d)  ;
  LCD.setCursor(0, 0); LCD.print("Lasterr:") + LCD.print(_lasterr) + LCD.print(" D:") + LCD.print(D)  ;

  //LCD.setCursor(0, 1); LCD.print("e:") + LCD.print(_error) + LCD.print(" r:") + LCD.print(_thresholdSpeed - _control) + LCD.print(" l:") + LCD.print(_thresholdSpeed + _control);
  LCD.setCursor(0, 1); LCD.print("e:") + LCD.print(_error) + LCD.print(" t:") + LCD.print(speedThreshold) + LCD.print(" c:") + LCD.print(_control);


  //Serial.print("Lasterr: ");
  //Serial.println(_lasterr);
  //Serial.print("D: ");
  //  Serial.println(D);


  LCD.flush(); */


};

void PIDClass::stopCar() {

  leftMotorBridge.setOutput(stopCarThreshold);
  rightMotorBridge.setOutput(stopCarThreshold);
  delay(250);
  TINAH::HBridge::allOff();
  errorCalc();
  _lasterr = _error;

  Serial.print("Last Error: ");
  Serial.println(_lasterr);

};


void PIDClass::stopCarForward(){
  leftMotorBridge.setOutput(-stopCarThreshold);
  rightMotorBridge.setOutput(-stopCarThreshold);
  delay(250);
  TINAH::HBridge::allOff();
  errorCalc();
  _lasterr = _error;

}

void PIDClass::reverseAndStop() {
  leftMotorBridge.setOutput(stopCarThreshold);
  rightMotorBridge.setOutput(stopCarThreshold);
  delay(1200);
  TINAH::HBridge::allOff();
  // errorCalc();
  // _lasterr = _error;

  //Serial.print("Last Error: ");
  //Serial.println(_lasterr);



};

void PIDClass::stopCompletely() {
  TINAH::HBridge::allOff();
  errorCalc();
  _lasterr = _error;
}

void PIDClass::goForward() {
  leftMotorBridge.setOutput( _thresholdSpeed - 20);
  rightMotorBridge.setOutput( _thresholdSpeed - 20);


}




void PIDClass::errorCalc() {
  float leftSensor = analogRead(_qrd_left);
  float rightSensor = analogRead(_qrd_right);

  if (leftSensor > _minBlackTapeVoltage_Left && rightSensor > _minBlackTapeVoltage_Right) {
    _error = 0;
  }
  else if (leftSensor > _minBlackTapeVoltage_Left && rightSensor < _minBlackTapeVoltage_Right) {
    _error = -1;
  }
  else if (leftSensor < _minBlackTapeVoltage_Left && rightSensor > _minBlackTapeVoltage_Right) {
    _error = 1;
  }
  else if (leftSensor < _minBlackTapeVoltage_Left && rightSensor < _minBlackTapeVoltage_Right) {
    if (_lasterr >= 0) {
      _error = 5;
    }
    else if (_lasterr < 0) {
      _error = -5;
    }
  }


};

void PIDClass::turn() {
  errorCalc();
  while (_error != -1) {
    errorCalc();
    leftMotorBridge.setOutput(0);
    rightMotorBridge.setOutput( _thresholdSpeed );

  }


};


void PIDClass::reverseBoth() {
  leftMotorBridge.setOutput(reverseSpeed);
  rightMotorBridge.setOutput(reverseSpeed);

};


void PIDClass::reverseRight() {
  leftMotorBridge.setOutput(-reverseSpeed/4 );
  rightMotorBridge.setOutput(reverseSpeed);

};

void PIDClass::reverseLeft() {
  rightMotorBridge.setOutput(-reverseSpeed/4);
  leftMotorBridge.setOutput(reverseSpeed);
};

void PIDClass::firstPlankCross(){
  leftMotorBridge.setOutput( _thresholdSpeed - 20);
  rightMotorBridge.setOutput( _thresholdSpeed - 25);
};

void PIDClass::plankReverse() {

  /*int leftSpeed = -100;
    int rightSpeed = -60;

    leftMotorBridge.setOutput( leftSpeed);
    rightMotorBridge.setOutput( rightSpeed );
    delay(900);
    TINAH::HBridge::allOff();

    errorCalc();
    _lasterr = _error;*/
  for (int i = 0; i < 3; i++) {
    leftMotorBridge.setOutput(stopCarThreshold);
    rightMotorBridge.setOutput(stopCarThreshold);
    delay(290);
    TINAH::HBridge::allOff();
    errorCalc();
    _lasterr = _error;
  }

};


void PIDClass::goForwardSpeed(int speedForward){
  leftMotorBridge.setOutput(speedForward);
  rightMotorBridge.setOutput(speedForward);
}


void PIDClass::jerkCar(){
  leftMotorBridge.setOutput(150);
  rightMotorBridge.setOutput(150);
  delay(150);
   leftMotorBridge.setOutput(-150);
  rightMotorBridge.setOutput(-150);
  delay(150);
}


void PIDClass::searchTapeRight() {
  leftMotorBridge.setOutput( 0);
  rightMotorBridge.setOutput( 0 );
  delay(1000);
  errorCalc();
  if (_error != 1 || _error != -1 || _error != 0 ) {
    _lasterr = 1;
  } else {
    _lasterr = _error;
  }
  /*
    int speedSearch = 50;
    errorCalc();
    //while(_error != 1 || _error != -1){
    rightMotorBridge.setOutput(speedSearch);
    leftMotorBridge.setOutput(0);
    delay(500);
    errorCalc();
    //delayMicroseconds(15);
    //errorCalc();
    //}*/
};

void PIDClass::assToWall() {
  rightMotorBridge.setOutput( -_thresholdSpeed+15);
  leftMotorBridge.setOutput(45);
  delay(1000);
};

void PIDClass::goForwardSlow() {
  leftMotorBridge.setOutput( 85);
  rightMotorBridge.setOutput(80);


};


void PIDClass::turnRight(){
  leftMotorBridge.setOutput( 80);
  rightMotorBridge.setOutput(-80);


};

void PIDClass::turnRightEdge(){
   leftMotorBridge.setOutput( 80);
  rightMotorBridge.setOutput(-30);
  };

void PIDClass::turnLeftEdge(){
   leftMotorBridge.setOutput( -30);
  rightMotorBridge.setOutput(80);
  };

