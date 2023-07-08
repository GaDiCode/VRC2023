#pragma once


class Motor{
  private:
    int forward_pin;
    int backward_pin;
  public:
    Motor(int forth, int back);

    void run_forward(int speed);

    void run_backward(int speed);

    void brake();
};