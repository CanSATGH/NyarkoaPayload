#ifndef NYARKOA_PAYLOAD_H
#define NYARKOA_PAYLOAD_H
#include <Arduino.h>
#include <SoftwareSerial.h>

struct Response {
  bool isOk;
  String message;
};

struct AnalogPins {
  byte A0;
  byte A1;
  byte A2;
  byte A3;
};

struct I2CPins {
  byte SDA;
  byte SCL;
};

struct SPIPins {
  byte CS;
  byte MOSI;
  byte MISO;
  byte SCK;
};

struct DigitalPins {
  byte D2;
  byte D3;
  byte D6;
  byte D7;
  byte D8;
  byte D9;
  byte D10;
  byte D11;
  byte D12;
  byte D13;
};

struct InterruptPins {
  byte D2;
  byte D3;
};

struct PWMPins {
  byte D3;
  byte D6;
  byte D7;
  byte D9;
  byte D10;
  byte D11;
};

struct CommUART {
  byte Rx;
  byte Tx;
};

struct MPUData {
  float accelX;
  float accelY;
  float accelZ;
  float gyroX;
  float gyroY;
  float gyroZ;
  float temp;
};

struct MPLData {
  float pressure;
  float altitude;
  float temperature;
};

struct GPSData {
  String nSats;
  String lat;
  String lon;
  String date;
  String time;
  String speed;
  String distanceFromHome;
};

class NyarkoaPayload {
 private:
  SoftwareSerial *commSerial = nullptr;

  // Generic variable declarations
  bool DEBUG{true};
  const unsigned long SERIAL_TIMEOUT{10000};
  const unsigned long CONNECT_SERIAL_TIMEOUT{30000};

  const int UNASSIGNED_PIN{-1};
  CommUART commUARTPins = {.Rx = 5, .Tx = 4};

  bool pinInfo(byte pin);
  void clearSerial();
  Response executeCmd(String cmd);
  Response request(String req);
  void transmit(String data);
  String receive();
  Response connect();
  // unsigned int readADC(byte pin);

 public:
   const unsigned long UART_BAUD_RATE{115200};
  NyarkoaPayload();
  // Pin declarations
  const byte LED{13};
  const byte BTN{12};

  AnalogPins analogPins = {.A0 = A0, .A1 = A1, .A2 = A2, .A3 = A3};
  I2CPins i2cPins = {.SDA = A4, .SCL = A5};
  SPIPins spiPins = {.CS = 10, .MOSI = 11, .MISO = 12, .SCK = 13};
  DigitalPins digitalPins = {.D2 = 2,
                             .D3 = 3,
                             .D6 = 6,
                             .D7 = 7,
                             .D8 = 8,
                             .D9 = 9,
                             .D10 = 10,
                             .D11 = 11,
                             .D12 = 12,
                             .D13 = 13};
  PWMPins pwmPin = {.D3 = 3, .D6 = 6, .D7 = 7, .D9 = 9, .D10 = 10, .D11 = 11};
  GPSData gpsData = {.nSats = "",
                     .lat = "",
                     .lon = "",
                     .date = "",
                     .time = "",
                     .speed = "",
                     .distanceFromHome = ""};

  ~NyarkoaPayload();

  // Delete copy constructor
  NyarkoaPayload(const NyarkoaPayload &obj) = delete;
  static NyarkoaPayload getInstance();

  // utility functions
  void debug(String text, bool newline = true);
  bool contains(String str, String substr);
  String simpleHash(String data);
  bool compareHash(String data, String hash);
  void activateDevMode();
  void activateProdMode();
  void (*resetPayload)(void) = 0;

  // Wrapper functions
  void setPinMode(byte pin, bool mode);
  void digitalWrite(byte pin, bool mode);
  void setAnalogValue(byte pin, int value);

  // Transmission functions
  Response connectCommModule();

  // Action Methods
  void commAction(String cmd);
  String requestAction(String cmd);
  bool contactGroundStation(String cmd, String payload);

  void ejectBalloon();
  void alert(unsigned long duration = 100);
  void enableBeacon();
  void disableBeacon();
  String getDate();
  String getTime();
  String getTimestamp();
  String getTimeAfter(int sec = 30, int mins = 0, int hours = 0, int days = 0);
  MPUData getMPUData();
  MPLData getMPLData();
  GPSData getGPSData();
};

#endif