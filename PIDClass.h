#ifndef PID_h
#define PID_h

#include "Arduino.h"
#include "TINAH.h"
#include "ObjectDetection.h"



class PIDClass
{

  public:
    PIDClass();
    void tapeFollow();
    void tapeFollowSpeed(int speedThreshold);
    void stopCar();
    void reverseAndStop();
    void goForward();
    void stopCompletely();
    void turn();
    void turnRight();
    
    void reverseBoth();
    void reverseRight();
    void reverseLeft();
    void plankReverse();
    void searchTapeRight();
    void assToWall();
    void goForwardSlow();
    void tapeFollowSpeedingUp(int speedTh, boolean first);
    void goForwardFast();
    void firstPlankCross();
    void goForwardSpeed(int speedForward);

    void turnRightEdge();
    void turnLeftEdge();
    void stopCarForward();
    void jerkCar();

    
    enum tapeFollowState
    {
      ON,
      STOP
    };

    void SetPIDState( PIDClass::tapeFollowState pidState)
    {
      _pidState = pidState;
    }

    PIDClass::tapeFollowState getPidState() const
    {
      return _pidState;
    }

  private:
    int _thresholdSpeed;
    int _qrd_left;
    int _qrd_right;
    int _minBlackTapeVoltage_Left;
    int _minBlackTapeVoltage_Right;
    int _error;
    int _control;
    int _lasterr;
    
    

    PIDClass::tapeFollowState _pidState;
    void errorCalc();
    
};
#endif

