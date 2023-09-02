#include "declaration.h"
#include "servo.h"

int climb_up_value = 857;
int climb_down_value = 1880;
int stop_value = 0;
int hand_catch = 400;
int hand_mid = 850;
int hand_release = 2000;
unsigned long cascadeTime = 0;

void cascade_go_up(){
  if(ps2x.Button(PSB_PAD_UP) && !ps2x.Button(PSB_PAD_DOWN)){
    cascadeUp.run(climb_up_value);
    Serial.println("cascade going up");
  }

  else if(ps2x.Button(PSB_PAD_DOWN) && !ps2x.Button(PSB_PAD_UP)){
    cascadeUp.run(climb_down_value);
    //pwm.setPWM(2,0,1880);
    Serial.println("cascade going down");
  }

  else{
    cascadeUp.run(stop_value);
    //pwm.setPWM(2,0,4095);
    
    Serial.println("stop");
  }
}



void cascade_move_hand(){
  if(ps2x.Button(PSB_R1)){
    cascadeHand.run(hand_mid);
  }
  else{
    if(ps2x.ButtonPressed(PSB_CIRCLE)){
      cascadeHand.run(hand_release);
      Serial.println("cascade released");
      cascadeTime = millis(); 
    }
    else if(millis() - cascadeTime > 2000){
      cascadeHand.run(hand_catch);
      Serial.println("cascade caught");
    }
  }
}

