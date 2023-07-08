#include "declaration.h"
#include "motor.h"

Motor::Motor(int forth, int back)
:forward_pin(forth), backward_pin(back)
{}

void Motor::run_forward(int speed){
  pwm.setPWM(forward_pin,0,speed);
  pwm.setPWM(backward_pin,0,0);
}

void Motor::run_backward(int speed){
  pwm.setPWM(forward_pin,0,0);
  pwm.setPWM(backward_pin,0,speed);
}

void Motor::brake(){
  pwm.setPWM(forward_pin,0,4095);
  pwm.setPWM(backward_pin,0,4095);
}