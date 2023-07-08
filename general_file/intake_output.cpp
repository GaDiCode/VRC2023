#include "declaration.h"
int dem_intake = 0;
int dem_output = 0;
int intake_state = 0;

void intake(){
    Serial.println("Intaking");
    pwm.setPWM(10, 0, 4095);
    pwm.setPWM(11, 0, 0);
}

void output(){
  Serial.println("Outputing");
  pwm.setPWM(10, 0, 0);
  pwm.setPWM(11, 0, 4095);
}

void intake_break(){
  Serial.println("Broken :(");
    pwm.setPWM(10, 0, 4095);
    pwm.setPWM(11, 0, 4095);
}

void intake_condition(){
  if (ps2x.ButtonPressed(PSB_L1) && !ps2x.ButtonPressed(PSB_L2)) dem_intake++;
  if (dem_intake%2!=0 && dem_output==0) intake();
  else {
    intake_break();
    dem_intake=0;
  }
}

void output_condition(){
  if (ps2x.ButtonPressed(PSB_L2) && !ps2x.ButtonPressed(PSB_L1)) dem_output++;
  if (dem_output%2!=0 && dem_intake==0) output();
  else {
    intake_break();
    dem_output=0;
  }
}


void overall_intake(){
  // 0: dừng
  // 1: intake
  // -1: output
  if (ps2x.ButtonPressed(PSB_L1) && !ps2x.ButtonPressed(PSB_L2)){
    if(intake_state == 0) intake_state = 1;
    else if (intake_state == 1) intake_state = 0;
  }
  else if (ps2x.ButtonPressed(PSB_L2) && !ps2x.ButtonPressed(PSB_L1)){
    if (intake_state == 0) intake_state = -1;
    else if (intake_state == -1) intake_state = 0;
  }
  //else intake_state = 0;

  switch(intake_state){
    case 0:
      intake_break();
      break;
    case 1:
      intake();
      break;
    case -1:
      output();
      break;
  }
}