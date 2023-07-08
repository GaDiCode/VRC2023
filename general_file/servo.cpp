#include "declaration.h"
#include "servo.h"

Servo::Servo(int _pin): pin(_pin), state(false){}

void Servo::run(int pos){
  pwm.setPWM(pin,0,pos);
}

void Servo::stop(){
  run(4095);
}

bool Servo::getState(){
  return state;
}

void Servo::setState(bool newState){
  state = newState;
}