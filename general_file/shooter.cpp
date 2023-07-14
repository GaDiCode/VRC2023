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
float shooterSpeed=2100;

long unsigned int PreTimer = 0;
long unsigned int ShooterTimer = 0;
bool ShooterServoCondition = false;
void shooter_break() {
  FinalSpeed = 0;
  PID_Shooter();
  if(cur_speed <FinalSpeed){
    pwm.setPWM(8, 0, 4095);
    pwm.setPWM(9, 0, 4095);
  }
  else {
    pwm.setPWM(9, 0, 0);
    pwm.setPWM(8, 0, cur_speed);
  }
  delay(10);
}

void shooter() {
  //FinalSpeed = 2100;
  FinalSpeed = shooterSpeed;
  PID_Shooter();
  pwm.setPWM(9, 0, 0);
  pwm.setPWM(8, 0, cur_speed);
  if(cur_speed < FinalSpeed/2) delay(30);
}

void PID_Shooter() {
  er = FinalSpeed - cur_speed;
  i += er*dt;
  d = (er-pre_er)*dt;
  cur_speed = (Kp*er) + (Ki*i) + (Kd*d);
  if(cur_speed > 4095) cur_speed = FinalSpeed;
  if(cur_speed < 0) cur_speed = 0;
}

void shooter_condition(){
  //*
  if(!ps2x.Button(PSB_R1)) {
  //if(dem_shooter%2==0) {
    shooter_break(); 
  }
  else {
    shooter();
  }
  
  //if(ps2x.ButtonPressed(PSB_R1)) dem_shooter++;
  //dem_shooter%2==0 ? shooter_break() : shooter();
}

int firstState = 0;
int secondState = 950;

void shooter_run_servo(){
  Serial.println(shooterServo.getState());
  if (cur_speed < (FinalSpeed - 100)) ShooterTimer = millis();
  //millis() - ShooterTimer > 2000 ? ShooterServoCondition = true : ShooterServoCondition = false;
  ShooterServoCondition = millis() - ShooterTimer > 2000;
  Serial.println(millis() - ShooterTimer);
  Serial.print("curspeed: "); Serial.println(cur_speed);
  
  if(ps2x.ButtonPressed(PSB_CIRCLE) and ShooterServoCondition){
    shooterServo.run(500);
    PreTimer = millis();
    Serial.println("Closed");
  }
  if(millis() - PreTimer > 500) {
    shooterServo.run(1850);
    Serial.println("opened");
  }
}

void shooterSpeedMod(){
  if(ps2x.ButtonReleased(PSB_PAD_UP) && !ps2x.ButtonReleased(PSB_PAD_DOWN)){
    shooterSpeed += 25;  
  }
  else if(!ps2x.ButtonReleased(PSB_PAD_UP) && ps2x.ButtonReleased(PSB_PAD_DOWN)){
    shooterSpeed -= 25;
  }
  else if(ps2x.ButtonPressed(PSB_SQUARE)){
    shooterSpeed = 2100;  
  }
  Serial.print("shooter max speed: "); Serial.println(shooterSpeed);
}
