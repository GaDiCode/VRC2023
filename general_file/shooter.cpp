#include "declaration.h"

int dem_shooter=0;
float OriginalSpeed = 50.0;
float cur_speed = OriginalSpeed;
float er, pre_er;
float Kp = 5;
float Ki = 1.2;
float Kd = 0.1;
float dt = 0.1;
float p, i, d;
float FinalSpeed=2500;
long unsigned int PreTimer = 0;
void shooter_break() {
  FinalSpeed = 0;
  PID_Shooter();
  if(cur_speed <FinalSpeed){
    pwm.setPWM(8, 0, 4095);
    pwm.setPWM(9, 0, 4095);
  }
  else {
    pwm.setPWM(8, 0, 0);
    pwm.setPWM(9, 0, cur_speed);
  }
  delay(10);
}

void shooter() {
  FinalSpeed = 2700;
  PID_Shooter();
  pwm.setPWM(8, 0, 0);
  pwm.setPWM(9, 0, cur_speed);
  if(cur_speed < FinalSpeed/2) delay(30);
}

void PID_Shooter() {
  er = FinalSpeed - cur_speed;
  i += er*dt;
  d = (er-pre_er)*dt;
  cur_speed = (Kp*er) + (Ki*i) + (Kd*d);
  if(cur_speed > 4095) cur_speed = 4095;
  if(cur_speed < 0) cur_speed = 0;
}

void shooter_condition(){
  if(ps2x.ButtonPressed(PSB_R1)) dem_shooter++;
  // Serial.println(dem);

  if(!ps2x.Button(PSB_R1)) {
  //if(dem_shooter%2==0) {
    shooter_break(); 
  }
  else {
    shooter();
  }
  //Serial.println(cur_speed);
}

int firstState = 0;
int secondState = 950;

void shooter_run_servo(){
  Serial.println(shooterServo.getState());
  if(ps2x.ButtonPressed(PSB_CIRCLE)){
    shooterServo.run(1250);
    PreTimer = millis();
    Serial.println("Closed");
  }
  if(millis() - PreTimer > 500) {
    shooterServo.run(350);
    Serial.println("opened");
  }
}
