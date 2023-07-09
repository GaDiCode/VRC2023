#include "declaration.h"
#include "servo.h"

Servo::Servo(int _pin): pin(_pin), state(0){}

void Servo::run(int pos){
  pwm.setPWM(pin,0,pos);
}

void Servo::stop(){
  run(4095);
}

int Servo::getState(){
  return state;
}

void Servo::setState(int newState){
  state = newState;
}
