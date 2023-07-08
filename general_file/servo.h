#pragma once

class Servo{
  private:
    int pin;
    bool state;
  public:
    Servo(int _pin);

    void run(int pos);
    void stop();
    bool getState();
    void setState(bool state);

};