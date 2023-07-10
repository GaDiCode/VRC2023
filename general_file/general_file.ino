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
//Motor leftWheel(12,13);

//Motor rightWheel(14,15);
//Motor shooter(8,9);
//Motor intake(10,11);
Servo shooterServo(5);
Servo extensionServo(3);

void setup() {
  pinMode(25, INPUT_PULLUP);
  pinMode(32, INPUT_PULLUP);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(240);
  Wire.setClock(400000);
  Serial.begin(115200);
  Serial.print("Ket noi voi tay cam PS2:");
  for (int i = 0; i < 5; i++) // thử kết nối với tay cầm ps2 trong 10 lần
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



  ESPUI.setVerbosity(Verbosity::VerboseJSON);
  // Set hostname
  #if defined(ESP32)
      WiFi.setHostname(hostname);
  #else
      WiFi.hostname(hostname);
  #endif

  // try to connect to existing network
  WiFi.begin(ssid, password);
  Serial.print("\n\nTry to connect to existing network");

  {
    uint8_t timeout = 10;

    // Wait for connection, 5s timeout
    do
    {
      delay(500);
      Serial.print(".");
      timeout--;
    } while (timeout && WiFi.status() != WL_CONNECTED);

    // not connected -> create hotspot
    if (WiFi.status() != WL_CONNECTED)
    {
      Serial.print("\n\nCreating hotspot");

      WiFi.mode(WIFI_AP);
      WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
      WiFi.softAP(ssid);

      timeout = 5;

      do
      {
        delay(500);
        Serial.print(".");
        timeout--;
      } while (timeout);
    }
  }

  dnsServer.start(DNS_PORT, "*", apIP);

  Serial.println("\n\nWiFi parameters:");
  Serial.print("Mode: ");
  Serial.println(WiFi.getMode() == WIFI_AP ? "Station" : "Client");
  Serial.print("IP address: ");
  Serial.println(WiFi.getMode() == WIFI_AP ? WiFi.softAPIP() : WiFi.localIP());

  ESPUI.addControl(ControlType::Switcher, "Reverse", "", ControlColor::Turquoise, Control::noParent, &Reverse);
  ESPUI.addControl(ControlType::Slider, "Speed", "0", ControlColor::Alizarin, Control::noParent, &Speed_Control);
  ESPUI.addControl(ControlType::Number, "Motor:", "1", ControlColor::Wetasphalt, Control::noParent, &NumberMotor);

  /*
     .begin loads and serves all files from PROGMEM directly.
     If you want to serve the files from SPIFFS use ESPUI.beginSPIFFS
     (.prepareFileSystem has to be run in an empty sketch before)
  */

  // Enable this option if you want sliders to be continuous (update during move) and not discrete (update on stop)
  ESPUI.sliderContinuous = true;

  /*
     Optionally you can use HTTP BasicAuth. Keep in mind that this is NOT a
     SECURE way of limiting access.
     Anyone who is able to sniff traffic will be able to intercept your password
     since it is transmitted in cleartext. Just add a string as username and
     password, for example begin("ESPUI Control", "username", "password")
  */
  //  motorSlider a(18, 19, "acnv");
  ESPUI.begin("ESPUI Control");
  _t = millis();
}

void loop() {
  ps2x.read_gamepad(false, false);
  dnsServer.processNextRequest();
  overall_intake();
  movement_condition();
  shooter_condition();
  shooter_run_servo();
}
