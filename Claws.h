#ifndef claws
#define claws


#include "Arduino.h"

class Claws{
  public:
    Claws();
    boolean pickUpEwok(int courseState);
    void DropBothClaws();
    void ReturnToHome();
    
    
  private:
    //boolean debounceButton(int switchPin);
   
  
};



#endif








