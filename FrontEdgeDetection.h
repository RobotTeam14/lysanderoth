#ifndef frontEdge
#define frontEdge

#include "Arduino.h"
#include "TINAH.h"

class FrontEdgeDetection {
  public:

    FrontEdgeDetection();
    //boolean EdgeDetected(int dist);
    //boolean EdgeDetectedLow(int dist);
    void firstEdge();
    void secondEdge();
    void thirdEdge();
    int distanceCalc();
    boolean EdgeDetectedQRD();
    void StartPosition();

  private:


    int _thDistance;

};







#endif

