#ifndef COMPONENTDIVER_H
#define COMPONENTDIVER_H

#include <Arduino.h>

// Dynamically controlled stepper
class dynStepper{
  private:
    uint32_t stepDelay = 1000; // Delay between steps, in microseconds
    // uint16_t rampTime = 0;  // Time to ramp up to full speed
    uint8_t pinSet[4];; //Defined output pins

    int32_t currentPos = 0;
    int32_t targetPos = 0;

    uint32_t currWait = 0;

  public:
    dynStepper(){};
    dynStepper(uint8_t _pinA, uint8_t _pinB, uint8_t _pinC, uint8_t _pinD);
    void update(uint16_t loopTime);
    void setTarget(long int _target){targetPos = _target;}
    int32_t getError(void){return currentPos-targetPos;}
    void setStepDelay(uint16_t _stepDelay){stepDelay = _stepDelay;}
    void setZero(){currentPos = 0; targetPos = 0;}
};


#endif // COMPONENTDIVER_H
