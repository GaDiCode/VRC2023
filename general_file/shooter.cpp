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
float FinalSpeed;
float shooterSpeed=2100;
long maxSpeed = 3000;

long unsigned int PreTimer = 0;
long unsigned int ShooterTimer = 0;
bool ShooterServoCondition = false;
unsigned long prevShooterTime = 0;
void shooter_break() {
  FinalSpeed = 0;
  //PID_Shooter();
  //cur_speed = kalman_filter(cur_speed);
  cur_speed = 0;
  if(cur_speed <FinalSpeed){
    shooterMotor.brake();
    //pwm.setPWM(8, 0, 4095);
    //pwm.setPWM(9, 0, 4095);
  }
  else {
    shooterMotor.run_forward(cur_speed);
    //pwm.setPWM(9, 0, 0);
    //pwm.setPWM(8, 0, cur_speed); 
  }
  delay(10);
}

void shooter() {
  //FinalSpeed = 2100;
  FinalSpeed = shooterSpeed;
  //PID_Shooter();

  Serial.print("deltat: "); Serial.println(millis() - prevShooterTime);

  if(millis() - prevShooterTime <= 1000) cur_speed = maxSpeed;
  else cur_speed = shooterSpeed;

  //if(cur_speed<FinalSpeed) cur_speed+=200;
  //else cur_speed = FinalSpeed;
  
  //cur_speed = kalman_filter(cur_speed);
  
  pwm.setPWM(9, 0, 0);
  pwm.setPWM(8, 0, cur_speed);
  if(cur_speed < FinalSpeed/2) delay(30);
}

void PID_Shooter() {
  er = FinalSpeed - cur_speed;
  i += er*dt;
  d = (er-pre_er)*dt;
  cur_speed = (Kp*er) + (Ki*i) + (Kd*d);
  if(cur_speed > FinalSpeed) cur_speed = FinalSpeed;
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
  //Serial.println(shooterServo.getState());

  
  //if (cur_speed < (FinalSpeed - 100)) ShooterTimer = millis();
  //millis() - ShooterTimer > 2000 ? ShooterServoCondition = true : ShooterServoCondition = false;
  ShooterServoCondition = millis() - ShooterTimer > 7000;
  //Serial.println(millis() - ShooterTimer);
  Serial.print("curspeed: "); Serial.println(cur_speed);
  
  if(ps2x.ButtonPressed(PSB_CIRCLE) and ShooterServoCondition){
    shooterServo.run(500);
    PreTimer = millis();
    //Serial.println("Closed");
  }
  if(millis() - PreTimer > 500) {
    shooterServo.run(1850);
    //Serial.println("opened");
  }
  

  /*
  if(ps2x.ButtonPressed(PSB_CIRCLE)){
    shooterServo.run(500);
    PreTimer = millis();
    Serial.println("closed");
  }
  if(millis() - PreTimer > 500){
    shooterServo.run(1850);
    Serial.println("opened");
  }
  */
}

void shooterSpeedMod(){
  if(ps2x.ButtonReleased(PSB_PAD_UP) && !ps2x.ButtonReleased(PSB_PAD_DOWN)){
    shooterSpeed += 25;  
  }
  else if(!ps2x.ButtonReleased(PSB_PAD_UP) && ps2x.ButtonReleased(PSB_PAD_DOWN)){
    shooterSpeed -= 25;
  }
  else if(ps2x.ButtonReleased(PSB_SQUARE)){ shooterSpeed = 2100; }
  Serial.print("shooter max speed: "); Serial.println(shooterSpeed);
}

float kalman_gain=0;
float err_measure=2;
float err_estimate=2;
float q = 0.01;
float current_estimate=0;
float last_estimate=0;

float kalman_filter(float cur){
  kalman_gain = err_estimate/(err_estimate + err_measure);
  current_estimate = last_estimate + kalman_gain * (cur - last_estimate);
  err_estimate = (1.0f - kalman_gain) * err_estimate + fabsf(last_estimate - current_estimate)*q;
  last_estimate = current_estimate;
  return current_estimate;    
}


bool shooterIsHeld = false;
bool shooterIsRunning = false;
int shooterCounter = 0;
//long maxSpeed = 3000;

void shooterHoldCondition(){
  if(ps2x.ButtonPressed(PSB_R1)){
    shooterCounter++;
  }

  if((shooterCounter % 2 ==1 || ps2x.Button(PSB_R1))){
    if(!shooterIsRunning){
      prevShooterTime = millis();
      ShooterTimer = millis();
      shooterIsRunning = true;
    }
    shooter();
  }
  else{
    shooterIsRunning = false;
    shooter_break();
  }
}