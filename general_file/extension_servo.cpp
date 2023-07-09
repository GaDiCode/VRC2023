#include "declaration.h"
#include "servo.h"

const int CLOSED =0;
const int OPENED = 2;
const int OPENING = 1;
const int CLOSING = 3;

const int open_value = 0;  // giá trị để extension mở ra
const int close_value = 0; // giá trị để extension đóng lại
const int stop_value = 0; // giá trị để ngừng servo

void extension_run_servo_hand(){
  if(ps2x.ButtonPressed(PSB_SQUARE)){
    if(extensionServo.getState() == CLOSED){
      // nếu đang đóng hoàn toàn, mở ra đặt là đang mở
      extensionServo.run(open_value);
      extensionServo.setState(OPENING);
      
    }
    else if(extensionServo.getState() == OPENING){
      //nếu đang mở, dừng lại, đặt là đã mở hoàn toàn
      extensionServo.run(stop_value);
      extensionServo.setState(OPENED);
    }
    else if(extensionServo.getState() == OPENED){
      // nếu đang mở hoàn toàn, bắt đầu quay, đặt là đang đóng
      extensionServo.run(close_value);
      extensionServo.setState(CLOSING);
    }
    else if(extensionServo.getState() == CLOSING){
      // nếu đang đóng, dừng lại, đặt là đóng hoàn toàn
      extensionServo.run(stop_value);
      extensionServo.setState(CLOSED);
    }
  }
}


const int time_to_open = 0 ;//thời gian để mở hoàn toàn extension, đo bằng tay?
const int time_to_close = 0; // thời gian để đóng hoàn toàn extension, đo bằng tay?

void extension_run_servo_auto(){
  if(ps2x.ButtonPressed(PSB_SQUARE)){
    if(extensionServo.getState() == CLOSED){
      // nếu đang đóng hoàn toàn, mở ra. đặt là đang mở
      extensionServo.run(open_value);
      extensionServo.setState(OPENING);
      _t = millis();
    }
    else if(extensionServo.getState() == OPENED){
      //nếu đang mở hoàn toàn, quay, đặt là đang đóng
      extensionServo.run(close_value);
      extensionServo.setState(OPENED);
      _t = millis();
    }
  }
  else{
    if(extensionServo.getState()==OPENING){
      // nếu đang mở, đến khoảng thời gian định trước, dừng lại, đặt là đã mở hoàn toàn
      if((unsigned long)(millis() - _t) > time_to_open){
        extensionServo.run(stop_value);
        extensionServo.setState(OPENED);
      }
    }
    else if(extensionServo.getState() == CLOSING){
      // nếu đang đóng, đến khoảng thời gian định trước, dừng lại, đặt là đã đóng hoàn toàn
      if((unsigned long)(millis() - _t) > time_to_close){
        extensionServo.run(stop_value);
        extensionServo.setState(CLOSED);
      }
    }
  }
}
