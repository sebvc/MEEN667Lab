#include <Arduino.h>
#include "ComponentDrivers.h"

dynStepper::dynStepper(uint8_t _pin0, uint8_t _pin1, uint8_t _pin2, uint8_t _pin3){
  pinSet[0] =  _pin0;
  pinSet[1] =  _pin1;
  pinSet[2] =  _pin2;
  pinSet[3] =  _pin3;

  for(size_t ii=0; ii<4; ii++){
    pinMode(pinSet[ii], OUTPUT);
    digitalWrite(pinSet[ii], LOW);
  }
}   

void dynStepper::update(uint16_t loopTime){
  currWait += loopTime;
  
  if(currWait < stepDelay) return; // Do not step if too soon

  currWait -= stepDelay;
  if(currWait > stepDelay/4) currWait = 0; // if delay has been long for some reason don't go too fast and miss steps

  if(currentPos < targetPos){
    digitalWrite(pinSet[(unsigned int)currentPos % 4], LOW);
    currentPos += 1;
    digitalWrite(pinSet[(unsigned int)currentPos % 4], HIGH);
  }
  else if(currentPos > targetPos){
    digitalWrite(pinSet[(unsigned int)currentPos % 4], LOW);
    currentPos -= 1;
    digitalWrite(pinSet[(unsigned int)currentPos % 4], HIGH);
  }
  else{
    digitalWrite(pinSet[(unsigned int)currentPos % 4], LOW);
  }
}