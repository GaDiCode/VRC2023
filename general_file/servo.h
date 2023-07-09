#pragma once

class Servo{
  private:
    int pin;
    int state;
  public:
    Servo(int _pin);

    void run(int pos);
    void stop();
    int getState();
    void setState(int state);

};
