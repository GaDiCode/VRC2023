#include "declaration.h"

int Ry, Ly;
int speed = 3500;
int lim_up, lim_down; 
int lim_joy_1 = 2065;
int lim_joy_2 = 2035;


void joystick_controller() {
  Ly = ps2x.Analog(PSS_LY);
  Ry = ps2x.Analog(PSS_RY);
  
  
  if(Ry > 128) {
    //rightWheel.run_backward(map(Ry, 128, 255, 500, speed));
    pwm.setPWM(12, 0, 0);
    pwm.setPWM(13, 0, map(Ry, 128, 255, 500, speed));
  }
  else if(Ry < 127) {
    //rightWheel.run_forward(map(Ry, 127, 0, 500, speed));
    pwm.setPWM(12, 0, map(Ry, 127, 0, 500, speed));
    pwm.setPWM(13, 0, 0);
  }
  else {
    //rightWheel.brake();
    pwm.setPWM(12, 0, 4095);
    pwm.setPWM(13, 0, 4095);
  }
  
  
  if(Ly > 128) {
    //leftWheel.run_backward(map(Ly, 128, 255, 500, speed));
    pwm.setPWM(14, 0, 0);
    pwm.setPWM(15, 0, map(Ly, 130, 255, 500, speed));
  }
  else if(Ly < 127) {
    //leftWheel.run_forward(map(Ly, 127, 0, 500, speed));
    pwm.setPWM(14, 0, map(Ly, 127, 0, 500, speed));
    pwm.setPWM(15, 0, 0);
  }
  else {
    //leftWheel.brake();
    pwm.setPWM(14, 0, 4095);
    pwm.setPWM(15, 0, 4095);
  }
}

void motor_break(){
    //rightWheel.brake();
    //leftWheel.brake();
    pwm.setPWM(12, 0, 4095);
    pwm.setPWM(13, 0, 4095);
    pwm.setPWM(14, 0, 4095);
    pwm.setPWM(15, 0, 4095);
}

void movement_condition(){
  if(ps2x.Button(PSB_R2)) motor_break();
  else
  {
    joystick_controller();
  }
}
