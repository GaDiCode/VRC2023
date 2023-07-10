#include <DNSServer.h>
#include <ESPUI.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <PS2X_lib.h>
//#include "motor.h"
#include "servo.h"

extern const byte DNS_PORT;
extern IPAddress apIP;
extern DNSServer dnsServer;
extern const char *ssid;
extern const char *password;
extern const char *hostname;
extern bool dir;
extern int MotorOrd;
extern int pin1, pin2;
void setPWM(int chan1, int chan2, bool state, uint16_t val);
void Speed_Control(Control *sender, int type);
void Reverse(Control *sender, int value);
void NumberMotor(Control* sender, int type);

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


// extension
extern int PWM_UP, PWM_DOWN, PWM_STOP, buttonL1, buttonR1, buttonL2, buttonR2;
void ClimbUp();
void ClimbDown();
void StopClimbing();
void extension_condition();

//extern Motor leftWheel;
//extern Motor rightWheel;
//extern Motor shooter;
//extern Motor intake;
extern Servo shooterServo;
extern Servo extensionServo;

void shooter_run_servo();
void extension_run_servo_hand();
void extension_run_servo_auto();

extern unsigned long _t;

extern long unsigned int PreTimer;
