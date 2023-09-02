/**************************
pwm port(8,9): right motor
pwm port(14,15): left motor
pwm port(10,11): left motor
**************************/

#include "declaration.h"

int PS2_DAT = 12;
int PS2_CMD = 13;
int PS2_SEL = 15;
int PS2_CLK = 14;
int error = 0;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); 
PS2X ps2x;
unsigned long _t =0;
Motor leftWheel(14,15);
Motor rightWheel(12,13);
Motor shooterMotor(8,9);
Motor intakeMotor(10,11);
Servo shooterServo(5);
Servo extensionServo(3);


Servo cascadeUp(2);
Servo cascadeHand(4);

void setup() {
  pinMode(25, INPUT_PULLUP);
  pinMode(32, INPUT_PULLUP);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(240);
  Wire.setClock(400000);
  Serial.begin(115200);
  Serial.print("Ket noi voi tay cam PS2:");
  for (int i = 0; i < 10; i++) // thử kết nối với tay cầm ps2 trong 10 lần
  {
    delay(1000); // đợi 1 giây
    // cài đặt chân và các chế độ: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
    error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, false, false);
    Serial.print(".");
    switch (error) // kiểm tra lỗi nếu sau 10 lần không kết nối được
    {
    case 0:
      Serial.println(" Ket noi tay cam PS2 thanh cong");
      break;
    case 1:
      Serial.println(" LOI: Khong tim thay tay cam, hay kiem tra day ket noi vơi tay cam ");
      break;
    case 2:
      Serial.println(" LOI: khong gui duoc lenh");
      break;
    case 3:
      Serial.println(" LOI: Khong vao duoc Pressures mode ");
      break;
    }
  }
  _t = millis();
}

void loop() {
  ps2x.read_gamepad(false, false);
  overall_intake();
  movement_condition();
  shooterSpeedMod();
  //shooter_condition();
  shooterHoldCondition();
  shooter_run_servo();
  extension_run_servo_hold();
  //cascade_go_up();
  //cascade_move_hand();
}
