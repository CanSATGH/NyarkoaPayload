#include <Arduino.h>
#include <NyarkoaPayload.h>

NyarkoaPayload::NyarkoaPayload() {}

NyarkoaPayload::~NyarkoaPayload() {}

/**
 * Print debugging information.
 *
 * This method allows you to print debugging information to the serial monitor.
 *
 * @param text The text to print as a string.
 * @param newline Whether to add a newline character. If true, a newline
 * character will be added to the end of the printed text; if false, no newline
 * character will be added.
 *
 * @note To view the debugging information, ensure that the Serial Monitor is
 * correctly initialized and opened in your Arduino IDE.
 */
void NyarkoaPayload::debug(String text, bool newline) {
  if (DEBUG) {
    Serial.print(text + String(newline ? "\n" : ""));
  }
}

/**
 * Activate development mode for debugging.
 *
 * This method activates development mode, which enables debugging output.
 * When in development mode, debugging information will be printed to the
 * Serial Monitor for troubleshooting and testing purposes.
 */
void NyarkoaPayload::activateDevMode() { DEBUG = true; }

/**
 * Activate production mode to disable debugging.
 *
 * This method activates production mode, which disables debugging output.
 * In production mode, debugging information will not be printed to the
 * Serial Monitor, ensuring normal operation without debug messages.
 */
void NyarkoaPayload::activateProdMode() { DEBUG = false; }

/**
 * Check if a string contains a substring.
 *
 * This method checks if the given `str` contains the specified `substr`.
 *
 * @param str The string to search in.
 * @param substr The substring to search for.
 * @return true if the `substr` is found within the `str`; otherwise, false.
 */
bool NyarkoaPayload::contains(String str, String substr) {
  return str.indexOf(substr) != -1;
}

/**
 * Generate a simple hash for the given data.
 *
 * This method computes a simple hash for the provided data by summing up the
 * ASCII values of its characters. The hash is represented as a string
 * containing information about the data length, the ASCII value of the first
 * character, the hash sum, and a checksum byte.
 *
 * @param data The data to hash.
 * @return The computed hash as a string.
 */
String NyarkoaPayload::simpleHash(String data) {
  unsigned long hashSum = 0;
  for (byte i = 0; i < data.length(); i++) {
    hashSum += int(data[i]);  // Compute the hash sum
  }

  byte checksum = byte(hashSum % 256);  // Calculate a simple checksum byte

  return String(data.length()) + String(int(data[0])) + String(hashSum) +
         String(int(data[data.length() - 1])) + String(checksum);
}

/**
 * Compare a data string with a hash.
 *
 * This method compares the provided data string with a hash to check for
 * equality.
 *
 * @param data The data string to compare.
 * @param hash The hash to compare against.
 * @return true if the data and hash match; otherwise, false.
 */
bool NyarkoaPayload::compareHash(String data, String hash) {
  return simpleHash(data) == hash;
}

/**
 * Clear the serial communication buffer.
 *
 * This method reads and discards any available data from the serial
 * communication buffer.
 */
void NyarkoaPayload::clearSerial() {
  while (commSerial->available()) {
    commSerial->read();
  }
}

/**
 * Execute a command and handle the response.
 *
 * @param cmd The command to execute.
 * @return A Response object with success status and message.
 */
Response NyarkoaPayload::executeCmd(String cmd) {
  byte attempts = 0;
  while (attempts <= 3) {
    transmit(cmd);
    String response = receive();

    debug("RCVD: " + response);
    if (compareHash(cmd, response)) {
      debug("Trans OK");
      return {.isOk = true, .message = "OK"};
    }
    attempts++;
  }
  return {.isOk = false, .message = "Req. failed"};
}

/**
 * Send a request and process the response.
 *
 * @param req The request to send.
 * @return A Response object with success status and message.
 *
 * This method sends a request to the communication module and processes the
 * response. It constructs the request message by appending the provided 'req'
 * parameter to "REQ:", then sends it. After receiving the response, it verifies
 * the hash of the request to ensure data integrity. If the response hash
 * matches the expected hash, it returns a Response object with 'isOk' set to
 * true, and the message is the payload received. If the response hash does not
 * match, it will make up to three attempts to send the request. If all attempts
 * fail or if the hash doesn't match, it returns a Response object with 'isOk'
 * set to false, and a message indicating failure.
 */
Response NyarkoaPayload::request(String req) {
  clearSerial();
  byte attempts = 0;
  while (attempts <= 3) {
    transmit("REQ:" + req);
    String response = receive();

    byte nPos = response.indexOf(':');
    String respHash = response.substring(0, nPos);
    String payload = response.substring(nPos + 1);

    if (compareHash(req, respHash)) {
      debug("Trans OK");
      return {.isOk = true, .message = payload};
    }
    attempts++;
  }
  return {.isOk = false, .message = "FAILED"};
}

/**
 * Transmit data through the serial communication.
 *
 * @param data The data to transmit.
 *
 * This method sends the provided 'data' over the serial communication channel.
 * It first clears the serial communication buffer to ensure that no residual
 * data is present. Then, it writes the 'data' followed by a newline character
 * to the communication module. A delay of 1000 milliseconds (1 second) is added
 * to allow for data transmission. Use this method to send commands or data to
 * the communication module.
 */
void NyarkoaPayload::transmit(String data) {
  clearSerial();
  commSerial->println(data);
  delay(1000);
}

/**
 * Receive data from the serial communication.
 *
 * @return The received data as a string.
 *
 * This method reads and collects data received through the serial communication
 * channel. It waits until data becomes available, ensuring that no data is
 * missed. If a timeout of 10 seconds (or the duration specified by
 * SERIAL_TIMEOUT) is exceeded without data reception, it returns "TIMEOUT" as a
 * string. Otherwise, it reads the received data, trims any leading or trailing
 * whitespace, and returns it as a string. Use this method to retrieve responses
 * or data from the communication module.
 */
String NyarkoaPayload::receive() {
  unsigned long startTime = millis();
  String data;

  while (!commSerial->available()) {
    if (millis() - startTime >= SERIAL_TIMEOUT) {
      return "TIMEOUT";
    }
  }
  data = commSerial->readString();
  commSerial->read();
  data.trim();
  return data;
}

/**
 * Connect to the communication module.
 *
 * @return A Response object with success status and message.
 *
 * This method initiates a connection to the communication module by sending the
 * "AT?" command. It waits for a response from the module and checks for success
 * or timeout conditions. If a timeout of 30 seconds (or the duration specified
 * by CONNECT_SERIAL_TIMEOUT) is exceeded without a response, it returns a
 * response object with "TIMEOUT" as the message. If a response is received, it
 * checks if the response contains "OK" to ensure a successful connection. If
 * "OK" is found, it returns a response object with "System Online" as the
 * message to indicate a successful connection. If the response doesn't contain
 * "OK," it returns a response object with "CRC Error." Use this method to
 * establish a connection with the communication module.
 */
Response NyarkoaPayload::connect() {
  clearSerial();
  commSerial->println("AT?");
  delay(1000);

  unsigned long startTime = millis();
  byte recallCount{1};
  debug("Waiting for comm.", false);

  while (!commSerial->available()) {
    if (millis() - startTime >= CONNECT_SERIAL_TIMEOUT) {
      return {.isOk = false, .message = "TIMEOUT"};
    }

    if (recallCount++ % 50 == 0) {
      debug("\nResending...");
      commSerial->println("AT?");
    }
    debug(".", false);
    delay(100);
  }

  // this is an acknowledgment (returns the number of characters received)
  String response = commSerial->readString();
  commSerial->read();

  if (!contains(response, "OK")) return {.isOk = false, .message = "CRC Error"};
  return {.isOk = true, .message = "\nSystem Online"};
}

/**
 * Start the communication module and connect to it.
 *
 * @return A Response object with success status and message.
 *
 * This method initializes the communication module by creating a SoftwareSerial
 * instance with specified Tx and Rx pins. It sets the communication module's
 * baud rate to the value defined by UART_BAUD_RATE. After initializing the
 * module, it attempts to establish a connection using the `connect` method. The
 * `connect` method will handle the connection process and return a response
 * object with details. Use this method to start the communication module and
 * connect to it.
 */
Response NyarkoaPayload::connectCommModule() {
  // keep sending AT? to the communication module;
  commSerial = new SoftwareSerial(commUARTPins.Tx, commUARTPins.Rx);
  commSerial->begin(UART_BAUD_RATE);
  return connect();
}

/**
 * Check if a pin is a special pin that requires special handling.
 *
 * @param pin The pin to check.
 * @return true if the pin is not special; otherwise, false.
 *
 * This method checks whether a specified pin is a special pin that requires
 * special handling. Special pins include those used for SPI, I2C communication,
 * and analog pins. If the pin is special, it will log a message indicating its
 * special status. For communication UART pins (Rx and Tx), the method returns
 * false to indicate they are not special. Use this method to determine if a pin
 * requires special handling.
 */
bool NyarkoaPayload::pinInfo(byte pin) {
  // List of pins with special handling and their corresponding messages
  static const byte specialPins[] = {
      spiPins.CS,    spiPins.MISO,  spiPins.MOSI,    spiPins.SCK,
      i2cPins.SDA,   i2cPins.SCL,   commUARTPins.Rx, commUARTPins.Tx,
      analogPins.A0, analogPins.A1, analogPins.A2,   analogPins.A3};
  const char* analog{"Analog"};
  static const char* specialMessages[] = {
      "SPI CS",  "SPI MISO", "SPI MOSI", "SPI SCK", "I2C SDA", "I2C SCL",
      "Comm Rx", "Comm Tx",  analog,     analog,    analog,    analog};

  for (size_t i = 0; i < sizeof(specialPins) / sizeof(specialPins[0]); i++) {
    if (pin == specialPins[i]) {
      debug("Pin #" + String(pin) + " is special: " + specialMessages[i]);
      if (pin == commUARTPins.Rx || pin == commUARTPins.Tx) {
        return false;
      } else {
        break;
      }
    }
  }
  return true;
}

/**
 * Set the mode of a pin.
 *
 * @param pin The pin to set the mode for.
 * @param mode The mode to set (INPUT or OUTPUT).
 *
 * This method sets the mode (INPUT or OUTPUT) for the specified pin. Before
 * setting the mode, it checks whether the pin is special using the `pinInfo`
 * method. Special pins, such as those used for SPI, I2C, or communication UART,
 * may require specific handling and shouldn't have their modes changed through
 * this method. In such cases, the method returns without making any changes.
 *
 * @param pin The pin number to set the mode for.
 * @param mode The mode to set, which can be either INPUT or OUTPUT.
 */
void NyarkoaPayload::setPinMode(byte pin, bool mode) {
  if (!pinInfo(pin)) return;
  pinMode(pin, mode);
}

/**
 * Write a digital value to a pin.
 *
 * @param pin The pin to write to.
 * @param state The state to set (HIGH or LOW).
 *
 * This method writes a digital value (HIGH or LOW) to the specified pin. It
 * provides a convenient way to set the digital state of a pin without directly
 * using the `digitalWrite` function. Before performing the write operation, it
 * checks whether the pin is special using the `pinInfo` method. Special pins,
 * such as those used for SPI, I2C, or communication UART, may require specific
 * handling and shouldn't have their states changed through this method. In such
 * cases, the method returns without making any changes.
 *
 * @param pin The pin number to write to.
 * @param state The state to set, which can be either HIGH or LOW.
 */
void NyarkoaPayload::digitalWrite(byte pin, bool state) {
  if (!pinInfo(pin)) return;
  digitalWrite(pin, state);
}

/**
 * Set an analog value on a PWM (pulse-width modulation) pin.
 *
 * @param pin The PWM pin to set the value for.
 * @param value The value to set (0 to 255).
 *
 * This method sets an analog value (0 to 255) on a PWM (pulse-width modulation)
 * pin. It provides a convenient way to set the analog value for the specified
 * pin. Before performing the operation, the method checks whether the pin is a
 * valid PWM pin. If the pin is not a valid PWM pin, it prints a debugging
 * message, indicating that the pin lacks PWM capability, and does not make any
 * changes.
 *
 * @param pin The PWM pin number to set the value for.
 * @param value The analog value to set (ranging from 0 to 255).
 */
void NyarkoaPayload::setAnalogValue(byte pin, int value) {
  // List of valid PWM pins
  static const byte validPins[] = {pwmPin.D3, pwmPin.D6,  pwmPin.D7,
                                   pwmPin.D9, pwmPin.D10, pwmPin.D11};

  for (byte validPin : validPins) {
    if (pin == validPin) {
      analogWrite(pin, value);
      return;  // Valid PWM pin, set the value and return
    }
  }

  // If the function reaches here, it's an invalid PWM pin
  debug("Pin D" + String(pin) + " lacks PWM capability.");
}

/**
 * Contact the ground station with a command and payload.
 *
 * @param cmd The command to send.
 * @param payload The payload to send.
 * @return true if the operation was successful; otherwise, false.
 *
 * This method sends a command and payload to the ground station by forming a
 * request string with the specified command and payload. It then sends the
 * request to the communication module, receives the response, and checks if the
 * response contains "GS_OK" to determine the success of the operation. If
 * "GS_OK" is found in the response, the method returns true, indicating a
 * successful operation; otherwise, it returns false.
 *
 * @param cmd The command to send to the ground station.
 * @param payload The payload to include in the request.
 * @return true if the operation was successful; otherwise, false.
 */
bool NyarkoaPayload::contactGroundStation(String cmd, String payload) {
  String req = +"GS::" + cmd + "::" + payload;
  debug("TRANS: " + req);
  String resp = requestAction(req);
  return contains(resp, "GS_OK");
}

/**
 * Perform a communication module action.
 *
 * @param cmd The command to execute.
 *
 * This method performs a communication module action by executing the specified
 * command and sending the corresponding response message to the ground station.
 * It calls the `executeCmd` method to execute the command and retrieve the
 * response. If the response is successful (isOk is true), the message "OK" is
 * sent to the ground station using the `contactGroundStation` method. If the
 * response is not successful, the message "FAILED" is sent to the ground
 * station.
 *
 * @param cmd The command to execute using the communication module.
 */
void NyarkoaPayload::commAction(String cmd) {
  Response response = executeCmd(cmd);
  String message = response.isOk ? "OK" : "FAILED";
  contactGroundStation(cmd, message);
}

/**
 * Send a request action to the communication module.
 *
 * @param cmd The request command to send.
 * @return The response message if the request is successful; otherwise, an
 * empty string.
 *
 * This method sends a request command to the communication module and waits for
 * a response. If the response is successful (isOk is true), the response
 * message is returned. If the request is unsuccessful, an empty string is
 * returned. The method internally uses the `request` method to send the request
 * command and handle the response.
 *
 * @param cmd The request command to send to the communication module.
 * @return The response message from the communication module, or an empty
 * string if the request failed.
 */
String NyarkoaPayload::requestAction(String cmd) {
  Response response = request(cmd);
  return response.isOk ? response.message : "";
}

/**
 * Eject the balloon and report the result to the ground station.
 *
 * This method initiates the balloon ejection process by sending the "AT_EJECT"
 * command to the payload module. It then checks the response to determine if
 * the ejection was successful and sends a corresponding status message to the
 * ground station.
 *
 * The method starts by constructing the "AT_EJECT" command and then uses the
 * `commAction` method to execute the command. The `commAction` method handles
 * the communication with the communication module and sends a status message to
 * the ground station, indicating whether the ejection was successful or not.
 */
void NyarkoaPayload::ejectBalloon() {
  String action = "AT_EJECT";
  debug("\nCMD: " + action);
  commAction(action);
}

/**
 * Trigger an alert with sound and light.
 *
 * This method triggers an alert with both sound and light to indicate a
 * specific event or condition. The alert consists of a sound and light signal,
 * which can be customized by specifying the duration of the alert.
 *
 * @param duration The duration of the alert in milliseconds (default: 100ms).
 * You can customize the duration to control the length of the alert signal.
 * Shorter durations create shorter alerts, while longer durations result in
 * longer alerts.
 */
void NyarkoaPayload::alert(unsigned long duration) {
  String action = "AT_ALERT:" + String(duration);
  debug("\nCMD: " + action);
  commAction(action);
}

/**
 * Enable the beacon.
 *
 * This method activates the beacon, allowing it to transmit signals or data for
 * tracking or identification purposes. Enabling the beacon can be useful in
 * scenarios where the payload module needs to be located or identified.
 */
void NyarkoaPayload::enableBeacon() {
  String action = "AT_EN_BEC:";
  debug("\nCMD: " + action);
  commAction(action);
}

/**
 * Disable the beacon.
 *
 * This method deactivates the beacon, stopping it from transmitting signals or
 * data. Disabling the beacon is useful when the payload module no longer needs
 * to be tracked or identified and should remain silent.
 */
void NyarkoaPayload::disableBeacon() {
  String action = "AT_DIS_BEC:";
  debug("\nCMD: " + action);
  commAction(action);
}

/**
 * Request the date from the communication module.
 *
 * This method sends a request to the communication module to obtain the current
 * date. It then returns the date string received from the communication module,
 * allowing the payload module to synchronize its date information.
 *
 * @return The date string received from the communication module.
 */
String NyarkoaPayload::getDate() {
  String request = "AT_DATE";
  debug("\nREQ: " + request);
  return requestAction(request);
}

/**
 * Request the time from the communication module.
 *
 * This method sends a request to the communication module to obtain the current
 * time. It then returns the time string received from the communication module,
 * allowing the payload module to synchronize its time information.
 *
 * @return The time string received from the communication module.
 */
String NyarkoaPayload::getTime() {
  String request = "AT_TIME";
  debug("\nREQ: " + request);
  return requestAction(request);
}

/**
 * Request the timestamp from the communication module.
 *
 * This method sends a request to the communication module to obtain the current
 * timestamp. It then returns the timestamp string received from the
 * communication module, allowing the payload module to obtain synchronized
 * timestamp information.
 *
 * @return The timestamp string received from the communication module.
 */
String NyarkoaPayload::getTimestamp() {
  String request = "AT_TSTAMP";
  debug("\nREQ: " + request);
  return requestAction(request);
}

/**
 * Request the time after a specific duration.
 *
 * This method sends a request to the communication module to calculate the time
 * after adding a specified number of seconds, minutes, hours, and days to the
 * current time. The request includes the durations to be added in each unit,
 * and the method returns the updated time string as received from the
 * communication module.
 *
 * @param sec The seconds to add.
 * @param mins The minutes to add.
 * @param hours The hours to add.
 * @param days The days to add.
 * @return The updated time string.
 */
String NyarkoaPayload::getTimeAfter(int sec, int mins, int hours,
                                        int days) {
  String request = "AT_F_TIME:" + String(sec) + "," + String(mins) + "," +
                   String(hours) + "," + String(days);
  debug("\nREQ: " + request);
  return requestAction(request);
}

/**
 * Request MPU (Motion Processing Unit) sensor data.
 *
 * This method sends a request to the communication module to retrieve data from
 * the MPU sensor, including accelerometer, gyroscope, and temperature data. It
 * then parses the received payload and returns the data in an MPUData struct.
 *
 * @return An MPUData struct containing accelerometer, gyro, and temperature
 * data.
 */
MPUData NyarkoaPayload::getMPUData() {
  String request = "AT_MPU";
  debug("\nREQ: " + request);
  String payload = requestAction(request);
  float values[7];
  String val;
  for (byte i = 0; i < 7; i++) {
    val = payload.substring(0, payload.indexOf(','));
    values[i] = val.toFloat();
    payload = payload.substring(payload.indexOf(',') + 1);
  }
  return {.accelX = values[0],
          .accelY = values[1],
          .accelZ = values[2],
          .gyroX = values[3],
          .gyroY = values[4],
          .gyroZ = values[5],
          .temp = values[6]};
}

/**
 * Request MPL (Motion Processing Library) sensor data.
 *
 * This method sends a request to the communication module to retrieve data from
 * the MPL sensor, including pressure, altitude, and temperature data. It then
 * parses the received payload and returns the data in an MPLData struct.
 *
 * @return An MPLData struct containing pressure, altitude, and temperature
 * data.
 */
MPLData NyarkoaPayload::getMPLData() {
  String request = "AT_MPL";
  debug("\nREQ: " + request);
  String payload = requestAction(request);
  float values[3];
  String val;
  for (byte i = 0; i < 3; i++) {
    val = payload.substring(0, payload.indexOf(','));
    values[i] = val.toFloat();
    payload = payload.substring(payload.indexOf(',') + 1);
  }
  return {
      .pressure = values[0], .altitude = values[1], .temperature = values[2]};
}

/**
 * Request GPS (Global Positioning System) sensor data.
 *
 * This method sends a request to the communication module to retrieve data from
 * the GPS sensor, including the number of satellites, latitude, longitude,
 * date, time, speed, and distance from the home location. It then parses the
 * received payload and returns the data in a GPSData struct.
 *
 * @return GPSData struct containing satellite count, latitude, longitude, date,
 * time, speed, and distance from home.
 */
GPSData NyarkoaPayload::getGPSData() {
  String request = "AT_GPS";
  debug("\nREQ: " + request);
  String payload = requestAction(request);
  const byte SIZE = 7;
  String values[SIZE];
  String val;
  for (byte i = 0; i < SIZE; i++) {
    values[i] = payload.substring(0, payload.indexOf(','));
    payload = payload.substring(payload.indexOf(',') + 1);
  }
  return {.nSats = values[0],
          .lat = values[1],
          .lon = values[2],
          .date = values[3],
          .time = values[4],
          .speed = values[5],
          .distanceFromHome = values[6]};
}
