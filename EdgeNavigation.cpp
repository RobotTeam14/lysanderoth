#define QRD_CLOSE 4
#define QRD_FAR 5
#define SPEED 70;

#define QRD_RIGHTEDGE 4
#define QRD_LEFTEDGE 6

#include "TINAH.h"
#include "EdgeNavigation.h"
#include "PIDClass.h"

extern PIDClass PidController;
extern TINAH::HBridge leftMotorBridge;
extern TINAH::HBridge rightMotorBridge;

int _minBlackTapeVoltage = 100;

int edgeThreshold = 800;

EdgeNavigation::EdgeNavigation() {

_doneAligning = false;
  _qrdClose = QRD_CLOSE;
  _qrdFar = QRD_FAR;
  _speed = SPEED;
  _errorEdge;
  _lastErrorEdge;
  _controlEdge;



}

void EdgeNavigation::edgeNavigate() {
  int edge_kp = 10;
  edgeErrorCalc();


  _controlEdge =  edge_kp * _errorEdge;

  leftMotorBridge.setOutput(_speed - _controlEdge);
  rightMotorBridge.setOutput(_speed + _controlEdge);
  _lastErrorEdge = _errorEdge;
};


void EdgeNavigation::edgeErrorCalc() {
  float closeSensor = analogRead(_qrdClose);
  float farSensor = analogRead(_qrdFar);

  Serial.println(analogRead(_qrdClose));
  Serial.println(analogRead(_qrdFar));


  if (farSensor > _minBlackTapeVoltage && closeSensor > _minBlackTapeVoltage) {
    _errorEdge = 1;
  }
  else if (farSensor > _minBlackTapeVoltage && closeSensor < _minBlackTapeVoltage) {
    _errorEdge = 0;
  }
  else if (farSensor < _minBlackTapeVoltage && closeSensor < _minBlackTapeVoltage) {
    _errorEdge = -1;
  }



};


boolean EdgeNavigation:: edgeDetected() {

   Serial.print(" RIGHT:"); Serial.print(analogRead(QRD_RIGHTEDGE)); Serial.print("  LEFT: "); Serial.println(analogRead(QRD_LEFTEDGE));

  if (analogRead(QRD_RIGHTEDGE) > edgeThreshold || analogRead(QRD_LEFTEDGE) > edgeThreshold) {
    return true;
  }

  else {
    return false;
  }


};

void EdgeNavigation:: edgeAlign() {

 while (!_doneAligning) {
  
 float right = analogRead(QRD_RIGHTEDGE);
 float left = analogRead(QRD_LEFTEDGE);
    if (right<edgeThreshold && left<edgeThreshold) {
      PidController.goForwardSlow();
    }

    else if (right>edgeThreshold && left<edgeThreshold) {
      PidController.turnRightEdge();
    }

    else if (right<edgeThreshold && left>edgeThreshold) {
      PidController.turnLeftEdge();
    }

    else if (right>edgeThreshold && left>edgeThreshold) {
      _doneAligning = true;

    }

}

};


