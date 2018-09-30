#ifndef edgenav
#define edgenav

#include "Arduino.h"
#include "TINAH.h"


class EdgeNavigation {

  public:
    EdgeNavigation();
    void edgeNavigate();
    boolean edgeDetected();
    void edgeAlign();

  private:
    void edgeErrorCalc();
    int _speed;
    int _errorEdge;
    int _lastErrorEdge;
    int _qrdClose;
    int _controlEdge;
    int _qrdFar;
    boolean _doneAligning;



};



#endif
