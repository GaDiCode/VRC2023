#include "declaration.h"

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 10, 1);

DNSServer dnsServer;

#if defined(ESP32)
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
const char *ssid = "DC controller";
const char *password = "12345678";
const char *hostname = "Dras";
bool dir = 0;
int MotorOrd = 0;
int pin1, pin2;

void setPWM(int chan1, int chan2, bool state, uint16_t val)
{
  Serial.println(val);
  if (state)
  {
    pwm.setPWM(chan1, 0, val);
    pwm.setPWM(chan2, 4096, 0);
  }
  else
  {
    pwm.setPWM(chan2, 0, val);
    pwm.setPWM(chan1, 4096, 0);
  }
}

void Speed_Control(Control *sender, int type)
{
  Serial.print("Slider: ID: ");
  Serial.print(sender->id);
  Serial.print(", Value: ");
  uint16_t val;
  if (sender->value)
    val = (sender->value).toInt() * 40.95;
  else
    val = 0;
  Serial.println(val);
  setPWM(pin1, pin2, dir, 4095 - val);
}

void Reverse(Control *sender, int value)
{
  switch (value)
  {
  case S_ACTIVE:
    Serial.print("Active:");
    dir = 1;
    break;

  case S_INACTIVE:
    Serial.print("Inactive");
    dir = 0;
    break;
  }

  Serial.print(" ");
  Serial.println(sender->id);
}

void NumberMotor(Control* sender, int type)
{
    Serial.println(sender->value);
    uint8_t Motor_N = (sender->value).toInt();
    switch (Motor_N)
    {
      case 1:
        pin1 = 8;
        pin2 = 9;
        break;
      case 2:
        pin1 = 10;
        pin2 = 11;
        break;
      case 3:
        pin1 = 12;
        pin2 = 13;
        break;
      case 4:
        pin1 = 14;
        pin2 = 15;
        break;
    }
}
