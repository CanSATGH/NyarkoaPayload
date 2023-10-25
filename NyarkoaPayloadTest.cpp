#include <Arduino.h>
#include <NyarkoaPayloadTest.h>

NyarkoaPayloadTest::NyarkoaPayloadTest() {}

NyarkoaPayloadTest::~NyarkoaPayloadTest() {}

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
void NyarkoaPayloadTest::debug(String text, bool newline) {
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
void NyarkoaPayloadTest::activateDevMode() { DEBUG = true; }

/**
 * Activate production mode to disable debugging.
 *
 * This method activates production mode, which disables debugging output.
 * In production mode, debugging information will not be printed to the
 * Serial Monitor, ensuring normal operation without debug messages.
 */
void NyarkoaPayloadTest::activateProdMode() { DEBUG = false; }

/**
 * Check if a string contains a substring.
 *
 * This method checks if the given `str` contains the specified `substr`.
 *
 * @param str The string to search in.
 * @param substr The substring to search for.
 * @return true if the `substr` is found within the `str`; otherwise, false.
 */
bool NyarkoaPayloadTest::contains(String str, String substr) {
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
String NyarkoaPayloadTest::simpleHash(String data) {
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
bool NyarkoaPayloadTest::compareHash(String data, String hash) {
  return simpleHash(data) == hash;
}

/**
 * Clear the serial communication buffer.
 *
 * This method reads and discards any available data from the serial
 * communication buffer.
 */
void NyarkoaPayloadTest::clearSerial() { debug("Serial cleared"); }

/**
 * Execute a command and handle the response.
 *
 * @param cmd The command to execute.
 * @return A Response object with success status and message.
 */
Response NyarkoaPayloadTest::executeCmd(String cmd) {
  return {.isOk = true, .message = "OK"};
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
Response NyarkoaPayloadTest::request(String req) {
  return {.isOk = true, .message = "Sample Response"};
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
void NyarkoaPayloadTest::transmit(String data) { debug("Transmitting data."); }

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
String NyarkoaPayloadTest::receive() { return "Received data."; }

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
Response NyarkoaPayloadTest::connect() {
  // Simulated response on success
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
Response NyarkoaPayloadTest::connectToCommModule(bool generateError) {
  // Simulate an error if needed
  if (generateError) {
    debug("ERROR: Unable to start communication module.");
    return {.isOk = false, .message = "ERROR"};
  }

  // Simulated response on success
  return {.isOk = true, .message = "OK"};
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
bool NyarkoaPayloadTest::pinInfo(byte pin) {
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
      if (pin == commUARTPins.Rx || pin == commUARTPins.Tx) {
        debug("ERROR: Pin #" + String(pin) +
              " is special: " + specialMessages[i]);
        return false;
      } else {
        debug("WARNING: Pin #" + String(pin) +
              " is special: " + specialMessages[i]);
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
void NyarkoaPayloadTest::setPinMode(byte pin, bool mode) {
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
void NyarkoaPayloadTest::digitalWrite(byte pin, bool state) {
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
void NyarkoaPayloadTest::setAnalogValue(byte pin, int value) {
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
bool NyarkoaPayloadTest::contactGroundStation(String cmd, String payload,
                                              bool generateError) {
  if (generateError) {
    debug("ERROR: Communication with ground station failed.");
    return false;
  }
  return true;
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
void NyarkoaPayloadTest::commAction(String cmd, bool generateError) {
  Response response;
  if (generateError) {
    response.isOk = false;
    response.message = "ERROR: Communication action failed.";
  }

  if (response.isOk) {
    debug("OK");
  }
}

/**
 * Read an analog value from the specified pin and return a random unsigned
 * integer.
 *
 * @param pin The analog pin to read.
 * @return An unsigned integer (0 to 65535) representing the value read from the
 * adc.
 */
unsigned int NyarkoaPayloadTest::readADC(byte pin) {
  randomSeed(analogRead(A0));
  return random(65535);
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
String NyarkoaPayloadTest::requestAction(String cmd, bool generateError) {
  if (generateError) {
    debug("ERROR: Request action failed.");
    return "ERROR";
  }
  return "action requested";
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
void NyarkoaPayloadTest::ejectBalloon() { debug("Balloon ejected."); }

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
void NyarkoaPayloadTest::alert(unsigned long duration) {
  // Simulated success message
  debug("Alert triggered for " + String(duration) + " ms.");
}

/**
 * Enable the beacon.
 *
 * This method activates the beacon, allowing it to transmit signals or data for
 * tracking or identification purposes. Enabling the beacon can be useful in
 * scenarios where the payload module needs to be located or identified.
 */
void NyarkoaPayloadTest::enableBeacon() {
  // Simulated success message
  debug("Beacon enabled successfully.");
}

/**
 * Disable the beacon.
 *
 * This method deactivates the beacon, stopping it from transmitting signals or
 * data. Disabling the beacon is useful when the payload module no longer needs
 * to be tracked or identified and should remain silent.
 */
void NyarkoaPayloadTest::disableBeacon() {
  // Simulated success message
  debug("Beacon disabled successfully.");
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
String NyarkoaPayloadTest::getDate(bool generateError) {
  if (generateError) {
    return "ERROR";
  }

  // Simulated sample data (current date)
  // This is just an example, you can replace it with your desired date format
  return "2023-10-23";
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
String NyarkoaPayloadTest::getTime(bool generateError) {
  if (generateError) {
    debug("ERROR: Unable to retrieve the time.");
    return "ERROR";
  }

  // Simulated sample data (current time)
  // This is just an example, you can replace it with your desired time format
  String time = "14:30:00";
  return time;
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
String NyarkoaPayloadTest::getTimestamp(bool generateError) {
  if (generateError) {
    debug("ERROR: Unable to retrieve the timestamp.");
    return "ERROR";
  }

  // Simulated sample data (current timestamp)
  // This is just an example, you can replace it with your desired timestamp
  // format
  String timestamp = "2023-10-23 14:30:00";

  return timestamp;
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
String NyarkoaPayloadTest::getTimeAfter(int sec, int mins, int hours, int days,
                                        bool generateError) {
  if (generateError) {
    debug("ERROR: Unable to calculate time after the specified duration.");
    return "ERROR";
  }

  // Simulated sample data (current time plus the specified duration)
  // This is just an example, you can replace it with your desired time
  // calculation
  int currentSec = 0;    // Current seconds
  int currentMin = 0;    // Current minutes
  int currentHour = 12;  // Current hour in 24-hour format
  int currentDay = 1;    // Current day

  currentSec += sec;
  if (currentSec >= 60) {
    currentSec %= 60;
    currentMin += 1;
  }

  currentMin += mins;
  if (currentMin >= 60) {
    currentMin %= 60;
    currentHour += 1;
  }

  currentHour += hours;
  if (currentHour >= 24) {
    currentHour %= 24;
    currentDay += 1;
  }

  currentDay += days;  // Adjusting the day

  // Format the calculated time
  String result = String(currentDay) + ":" + String(currentHour) + ":" +
                  String(currentMin) + ":" + String(currentSec);

  return result;
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
MPUData NyarkoaPayloadTest::getMPUData(bool generateError) {
  if (generateError) {
    debug("ERROR: MPU data not available.");
    return {.accelX = -1000.0,
            .accelY = -1000.0,
            .accelZ = -1000.0,
            .gyroX = -1000.0,
            .gyroY = -1000.0,
            .gyroZ = -1000.0,
            .temp = -1000.0};
  }

  // Simulated sample data
  float accelX = 0.0;   // Acceleration in X-axis
  float accelY = 0.0;   // Acceleration in Y-axis
  float accelZ = 9.81;  // Acceleration in Z-axis (1g)
  float gyroX = 0.0;    // Angular velocity in X-axis
  float gyroY = 0.0;    // Angular velocity in Y-axis
  float gyroZ = 0.0;    // Angular velocity in Z-axis
  float temp = 25.0;    // Temperature in Celsius

  return {.accelX = accelX,
          .accelY = accelY,
          .accelZ = accelZ,
          .gyroX = gyroX,
          .gyroY = gyroY,
          .gyroZ = gyroZ,
          .temp = temp};
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
MPLData NyarkoaPayloadTest::getMPLData(bool generateError) {
  if (generateError) {
    debug("ERROR: MPL data not available.");
    return {.pressure = -1.0, .altitude = -1.0, .temperature = -1.0};
  }

  // Simulated sample data
  float pressure = 1013.25;  // Pressure in hPa
  float altitude = 500.0;    // Altitude in meters
  float temperature = 25.0;  // Temperature in Celsius

  return {
      .pressure = pressure, .altitude = altitude, .temperature = temperature};
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
GPSData NyarkoaPayloadTest::getGPSData(bool generateError) {
  if (generateError) {
    // Generate random error data for testing
    return {
        .nSats = "ERR_NOSATS",
        .lat = "ERR_LAT",
        .lon = "ERR_LON",
        .date = "ERR_DATE",
        .time = "ERR_TIME",
        .speed = "ERR_SPEED",
        .distanceFromHome = "ERR_DISTANCE",
    };
  }

  // Generate random sample data
  return {
      .nSats = String(random(4, 15)),  // Random number of satellites
      .lat = String(random(400000, 500000) / 10000.0, 6),    // Random latitude
      .lon = String(random(-800000, -700000) / 10000.0, 6),  // Random longitude
      .date = "2023-10-25",                  // Static date for testing
      .time = "12:34:56",                    // Static time for testing
      .speed = String(random(0, 100), DEC),  // Random speed
      .distanceFromHome = String(random(0, 1000), DEC),  // Random distance
  };
}
