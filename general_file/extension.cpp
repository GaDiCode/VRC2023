#include "declaration.h"
int PWM_UP = 857;
int PWM_DOWN = 1880;
int PWM_STOP = 4000;
int buttonL1, buttonR1, buttonL2, buttonR2;
void ClimbUp() {
  pwm.setPWM(1, 0, PWM_UP);
  pwm.setPWM(7, 0, PWM_UP);
}
void ClimbDown() {
  pwm.setPWM(1, 0, PWM_DOWN);
  pwm.setPWM(7, 0, PWM_DOWN);
}
void ClimbUpL() {
  pwm.setPWM(1, 0, PWM_UP);
  pwm.setPWM(7, 0, PWM_STOP);
}
void ClimbUpR() {
  pwm.setPWM(1, 0, PWM_STOP);
  pwm.setPWM(7, 0, PWM_UP);
}
void ClimbDownL() {
  pwm.setPWM(1, 0, PWM_DOWN);
  pwm.setPWM(7, 0, PWM_STOP);
}
void ClimbDownR() {
  pwm.setPWM(1, 0, PWM_STOP);
  pwm.setPWM(7, 0, PWM_DOWN);
}
void StopClimbing() {
  pwm.setPWM(1, 0, PWM_STOP);
  pwm.setPWM(7, 0, PWM_STOP);
}
void extension_condition() {
  // INPUT_PULLUP --> return 0 when button is pressed 
  buttonL1 = digitalRead(25);
  buttonL2 = digitalRead(32);
  buttonR1 = digitalRead(250);
  buttonR2 = digitalRead(32); 
  if (ps2x.Button(PSB_GREEN) && buttonL1 == 1 && buttonR1 == 1) ClimbUp(); // Khi ấn nút đi lên và chưa chạm đỉnh
    
  if (ps2x.Button(PSB_BLUE) && buttonL2 == 1 && buttonR2 == 1) ClimbDown(); // khi ấn nút đi xuống và chưa kịch đáy

  if (ps2x.Button(PSB_GREEN) && buttonL1 == 1 && buttonR1 == 0) ClimbUpL();
    
  if (ps2x.Button(PSB_BLUE) && buttonL2 == 1 && buttonR2 == 0) ClimbDownL();

  if (ps2x.Button(PSB_GREEN) && buttonL1 == 0 && buttonR1 == 1) ClimbUpR();
    
  if (ps2x.Button(PSB_BLUE) && buttonL2 == 0 && buttonR2 == 1) ClimbDownR();

  // khi có 1 trong 3 cái: (2 nút cùng bị ấn hoặc nhả ra), (đã ở đỉnh và vẫn ấn đi lên), (đã ở đáy và vẫn ấn đi xuống)
  if ((ps2x.Button(PSB_GREEN) == ps2x.Button(PSB_BLUE)) or (buttonL1 == 0 && buttonR1 == 0 && ps2x.Button(PSB_GREEN)) or (buttonL2 == 0 && buttonR2 == 0 && ps2x.Button(PSB_BLUE))) StopClimbing();
}








