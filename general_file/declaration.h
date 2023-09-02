#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <PS2X_lib.h>
#include "motor.h"
#include "servo.h"

extern int PS2_DAT;
extern int PS2_CMD;
extern int PS2_SEL;
extern int PS2_CLK;
extern bool pressures;
extern bool rumble;
extern PS2X ps2x;

extern Adafruit_PWMServoDriver pwm;
extern int Ry, Ly;
extern int speed;
extern int lim_up, lim_down; 
extern int lim_joy_1, lim_joy_2;
extern int dem_intake;
extern int dem_output;
extern int dem_shooter;
void joystick_controller();
void motor_break();
void intake();
void intake_break();
void output ();
void intake_condition();
void output_condition();
void movement_condition();
extern int intake_state;
void overall_intake();

void shooter_break();
void PID_Shooter();
void shooter();
void shooter_condition();
extern int error ;
extern float er, pre_er, cur_speed, FinalSpeed, Kp, Ki, Kd;
extern float OriginalSpeed;
extern float p, i, d, dt;

extern Motor leftWheel;
extern Motor rightWheel;
extern Motor shooterMotor;
extern Motor intakeMotor;
extern Servo shooterServo;
extern Servo extensionServo;

extern Servo cascadeUp;
extern Servo cascadeHand;

void shooter_run_servo();
void extension_run_servo_hand();
void extension_run_servo_auto();
void extension_run_servo_hold();

extern unsigned long _t;

extern long unsigned int PreTimer, ShooterTimer;
extern bool ShooterServoCondition;
extern float shooterSpeed;

void shooterSpeedMod();

float kalman_filter(float cur);
extern float kalman_gain;
extern float err_measure;
extern float err_estimate;
extern float q;
extern float current_estimate;
extern float last_estimate;

void pad_controller();

extern bool shooterIsHeld;
extern bool shooterIsRunning;
void shooterHoldCondition();
extern unsigned long prevShooterTime;
extern int shooterCounter;
extern long maxSpeed;
extern unsigned long cascadeTime;

void cascade_go_up();
void cascade_move_hand();
void cascade();

