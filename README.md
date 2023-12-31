# NyarkoaPayload Library

The NyarkoaPayload Library provides an interface for interacting with the Nyarkoa CanSAT module by sending commands to the Communication and Control Module. This library streamlines user interaction, allowing users to focus on the payload and mission. All integrated sensors and systems are accessible through simple function calls.

This documentation aims to instruct you on using the NyarkoaPayload library. It's essential to understand that this library serves as a simulation of the actual library, NyarkoaPayload, acting as a sandbox or testbed. Its purpose is to make it possible for users to work with the Nyarkoa Payload module, excluding other Nyarkoa CanSAT components. Once the programming is completed and tested, the user can switch from NyarkoaPayload library to the NyarkoaPayload library without many changes.

All control and communication requests will return a dummy response. Furthermore, the library provides an option to intentionally generate an error response by setting the `generateError` default parameter to true. Consequently, any method accepting the `generateError` argument can produce a sample error response.

## Installation

To install the library, follow these steps:

1. Download the latest release of the NyarkoaPayload library from the [GitHub repository](https://github.com/cansatghana/OpenCanSatGH).
2. Open the Arduino IDE.
3. In the Arduino IDE, go to the **Sketch** menu and select **Include Library > Add .ZIP Library...**.
4. Locate the downloaded NyarkoaPayload library ZIP file on your computer and select it.
5. The library will be installed.

### Verify Installation

To verify that the NyarkoaPayload library has been successfully installed, follow these steps:

1. Open the Arduino IDE.
2. Create a new sketch (or open an existing one).
3. Go to the **Sketch** menu and look for an entry with the name "NyarkoaPayload."
4. If you see "NyarkoaPayload," it means the library has been installed successfully.

Now you can start using the NyarkoaPayload library for your CanSAT projects in the Arduino IDE.

---

### Special Notes. Please, read the following carefully

#### Special Note: Using the NyarkoaPayload Library in Test and Live Environments

The NyarkoaPayload library offers the flexibility to work with both test and live environments, providing a valuable toolkit for developing your CanSAT projects. Understanding when to use the test class, NyarkoaPayloadTest, and when to switch to the live class, NyarkoaPayload, is essential.

#### Test Environment - NyarkoaPayloadTest

The test class, NyarkoaPayloadTest, is specifically designed for use in a controlled test environment. It is ideal when you are working on the payload component independently, without the complete Nyarkoa CanSAT shell. This mode allows you to simulate the entire CanSAT operation as if the full Nyarkoa CanSAT shell were present. Here's how NyarkoaPayloadTest is beneficial:

- **Prototype Anywhere**: NyarkoaPayloadTest enables you to prototype your CanSAT payload using any compatible Arduino-Uno-like microcontroller, not necessarily the Nyarkoa Payload Module. This versatility in development environments is valuable for testing and refining your payload code.
- **Dummy Data Generation**: In test mode, NyarkoaPayloadTest generates dummy data and responses. This functionality is crucial for emulating real-world scenarios without requiring the complete Nyarkoa CanSAT unit.

#### Simulating Error Responses

While using the NyarkoaPayloadTest class, several methods offer the ability to simulate error responses for testing purposes. These methods can accept an additional boolean argument, `generateError`, which, when set to `true`, triggers simulated error responses. These methods include:

- `Response connectToCommModule(bool generateError = false)`
- `void commAction(String cmd, bool generateError = false)`
- `String requestAction(String cmd, bool generateError = false)`
- `bool contactGroundStation(String cmd, String payload, bool generateError = false)`
- `String getDate(bool generateError = false)`
- `String getTime(bool generateError = false)`
- `String getTimestamp(bool generateError = false)`
- `String getTimeAfter(int sec = 30, int mins = 0, int hours = 0, int days = 0, bool generateError = false)`
- `MPUData getMPUData(bool generateError = false)`
- `MPLData getMPLData(bool generateError = false)`
- `GPSData getGPSData(bool generateError = false)`

These features are invaluable for testing and validation of your CanSAT payload and actions, ensuring that your code functions reliably in all scenarios, especially when working with the full Nyarkoa CanSAT device.

#### Sample Code: How to instantiate the NyarkoaPayloadTest

```cpp
#include <Arduino.h>
#include "NyarkoaPayloadTest.h"

void setup() {
  // Initialize the NyarkoaPayloadTest instance
  NyarkoaPayloadTest nyarkoa;

  // Your setup code here
}

void loop() {
  // Your loop code here
}
```

---

### Special `structs` Used in Library

#### Response

- **Description:** Represents a response object with a success status and message.
- **Fields:**
  - `isOk` (bool): Indicates whether the operation was successful (true) or not (false).
  - `message` (String): A message describing the response.

#### MPUData

- **Description:** Represents data from a Motion Processing Unit.
- **Fields:**
  - `accelX` (float): Acceleration in the X-axis.
  - `accelY` (float): Acceleration in the Y-axis.
  - `accelZ` (float): Acceleration in the Z-axis.
  - `gyroX` (float): Gyroscope reading in the X-axis.
  - `gyroY` (float): Gyroscope reading in the Y-axis.
  - `gyroZ` (float): Gyroscope reading in the Z-axis.
  - `temp` (float): Temperature reading.

#### MPLData

- **Description:** Represents data from a Micro Pressure and Temperature sensor.
- **Fields:**
  - `pressure` (float): Atmospheric pressure reading.
  - `altitude` (float): Altitude reading.
  - `temperature` (float): Temperature reading.

#### GPSData

- **Description:** Represents data from a Global Positioning System (GPS).
- **Fields:**
  - `nSats` (String): Number of visible satellites.
  - `lat` (String): Latitude coordinate.
  - `lon` (String): Longitude coordinate.
  - `date` (String): Date information.
  - `time` (String): Time information.
  - `speed` (String): Speed information.
  - `distanceFromHome` (String): Distance from a reference location.

### Constructors

#### NyarkoaPayload()

- **Description:** Constructor for the NyarkoaPayload class.
- **Details:** The constructor initializes an instance of the NyarkoaPayload class. When an object of this class is created, it sets up the necessary configurations and prepares the class for communication and control. This is the starting point for using the class, and it ensures that the necessary resources and parameters are properly configured for interaction with the Nyarkoa CanSAT hardware.

#### Sample Code: How to instantiate the NyarkoaPayload

```cpp
#include <Arduino.h>
#include "NyarkoaPayload.h"

void setup() {
  // Initialize the NyarkoaPayload instance
  NyarkoaPayload nyarkoa;
  nyarkoa.activateDevMode();
  nyarkoa.startCommunication();

  // Your setup code here
}

void loop() {
  // Your loop code here
}
```

### activateProdMode()

- **Description:** Activate production mode to disable debugging.
- **Details:** Certainly! Here's a brief description for the `activateDevMode` method:

  **Method - activateDevMode():**

  The `activateProdMode` method is used to enable production mode, which disables debugging. When called, it configures the `NyarkoaPayload` class to operate in a mode optimized for production use, suppressing debugging output. This is important when you want to deploy your code in a production environment, ensuring that debugging information does not interfere with the normal operation of the Nyarkoa Payload hardware.

- ### Sample Code: How to Use the `activateProdMode` Method

  ```cpp
  #include <Arduino.h>
  #include "NyarkoaPayload.h"

  void setup() {
    // Initialize the NyarkoaPayload instance
    NyarkoaPayload nyarkoa;

    // Activate production mode to disable debugging
    nyarkoa.activateProdMode();

    // Your setup code here
  }

  void loop() {
    // Your loop code here
  }
  ```

---

## Utility Functions

### resetPayload()

- **Description:** Perform a reset of the Nyarkoa Payload module.
- **Details:** The `resetPayload` method allows you to perform a reset of the Nyarkoa Payload module. It is especially useful when you need to reset the board programmatically, for example, after a specific event or condition. This method calls a reset function, which essentially restarts the Nyarkoa Payload module, bringing it back to its initial state.

- #### Sample Code: How to Use the `resetPayload` Method

  ```cpp
  #include <Arduino.h>
  #include "NyarkoaPayload.h"

  void setup() {
    // Initialize the NyarkoaPayload instance
    NyarkoaPayload nyarkoa;

    // Call the resetFunc method to reset the payload module
    nyarkoa.resetPayload();
  }

  void loop() {
    // Your loop code here
  }
  ```

### contains(String str, String substr)

- **Description:** Check if a string contains a specified substring.
- **Parameters:**

  - `str` (String): The main string to search within.
  - `substr` (String): The substring to look for.
- **Details:** The `contains` method is used to determine whether the given `str` contains the specified `substr`. It helps you search for a specific `substr` within a larger `str`, which can be valuable for tasks like data processing or validation. This method returns `true` if the `substr` is found within the `str`, indicating a successful match. Otherwise, it returns `false.

- #### Sample Code: How to Use the `contains` Method

  ```cpp
  #include <Arduino.h>
  #include "NyarkoaPayload.h"

  void setup() {
    // Initialize the NyarkoaPayload instance
    NyarkoaPayload nyarkoa;

    // Define the main string and substring to search for
    String mainString = "Hello, world!";
    String subString = "world";

    // Check if the main string contains the substring
    bool result = nyarkoa.contains(mainString, subString);

    // Output the result
    if (result) {
      Serial.println("The main string contains the substring.");
    } else {
      Serial.println("The main string does not contain the substring.");
    }

    // Your setup code here
  }

  void loop() {
    // Your loop code here
  }
  ```

### simpleHash(String data)

- **Description:** Generate a simple hash for the given data.
- **Parameters:**

  - `data` (String): The data to hash.
- **Details:** The `simpleHash` method is designed to create a simple hash for the provided `data`. It uses a basic hashing algorithm to generate a hash value as a string. This method is particularly useful when you need a lightweight and quick way to create hash values for data. The generated hash can be used for various purposes, such as data verification.

- #### Sample Code: How to Use the `simpleHash` Method

  ```cpp
  #include <Arduino.h>
  #include "NyarkoaPayload.h"

  void setup() {
    // Initialize the NyarkoaPayload instance
    NyarkoaPayload nyarkoa;

    // Define the data to be hashed
    String dataToHash = "Hello, world!";

    // Generate a simple hash
    String hash = nyarkoa.simpleHash(dataToHash);

    // Output the hash
    Serial.println("Generated Hash: " + hash);

    // Your setup code here
  }

  void loop() {
    // Your loop code here
  }
  ```

### compareHash(String data, String hash)

- **Description:** Compare a data string with a hash.
- **Parameters:**

  - `data` (String): The data string to compare.
  - `hash` (String): The hash to compare against.
- **Details:** The `compareHash` method allows you to compare a given `data` string with a specific `hash`. It's commonly used to verify the integrity of data by comparing a computed hash with a known hash. This method returns `true` if the data and hash match, indicating data integrity. Otherwise, it returns `false.
- **Return Type:** `bool` - `true` if the data and hash match; `false` otherwise.

- #### Sample Code: How to Use the `compareHash` Method

  ```cpp
  #include <Arduino.h>
  #include "NyarkoaPayload.h"

  void setup() {
    // Initialize the NyarkoaPayload instance
    NyarkoaPayload nyarkoa;

    // Define the data and the expected hash
    String data = "Hello, world!";
    String expectedHash = "123abc"; // Replace with the actual expected hash

    // Compare the data with the expected hash
    bool isDataValid = nyarkoa.compareHash(data, expectedHash);

    // Check the result
    if (isDataValid) {
      Serial.println("Data integrity is verified.");
    } else {
      Serial.println("Data integrity check failed.");
    }

    // Your setup code here
  }

  void loop() {
    // Your loop code here
  }
  ```

### connectToCommModule()

- **Description:** Establish a connection to the communication module.
- **Details:** The `connectToCommModule` method is responsible for establishing a connection to the communication module. This is a crucial step in enabling communication with external devices or systems.
- **Return Type:** `Response` - A `Response` object containing the success status and connection message.

- #### Sample Code: How to Establish a Connection to the Communication Module

  ```cpp
  #include <Arduino.h>
  #include "NyarkoaPayload.h"

  void setup() {
    // Initialize the NyarkoaPayload instance
    NyarkoaPayload nyarkoa;

    // Establish a connection to the communication module
    Response connectionResult = nyarkoa.connectToCommModule();

    // Check the connection status
    if (connectionResult.isOk) {
      Serial.println("Connection to the communication module successful.");
      Serial.println("Message: " + connectionResult.message);
    } else {
      Serial.println("Connection failed.");
      Serial.println("Error Message: " + connectionResult.message);
    }

    // Your setup code here
  }

  void loop() {
    // Your loop code here
  }
  ```

## Pin Handling

### setPinMode(byte pin, bool mode)

- **Description:** Set the mode of a digital pin (INPUT or OUTPUT).
- **Parameters:**

  - `pin` (byte): The digital pin number.
  - `mode` (bool): The mode to set, where `true` is OUTPUT and `false` is INPUT.
- **Details:** The `setPinMode` method allows you to set the mode of a specified digital pin to either INPUT or OUTPUT. This is commonly used when you need to control external devices or sensors connected to the digital pins. For example, you can configure a pin as OUTPUT to send signals to an LED or a motor, or as INPUT to read data from a sensor.
- **Return Type:** None (void).

- #### Sample Code: How to Use the `setPinMode` Method

  ```cpp
  #include <Arduino.h>
  #include "NyarkoaPayload.h"

  void setup() {
    // Initialize the NyarkoaPayload instance
    NyarkoaPayload nyarkoa;

    // Define the digital pin number and mode
    byte pinNumber = 8;
    bool isOutputMode = true;  // Set the pin as OUTPUT

    // Set the pin mode
    nyarkoa.setPinMode(pinNumber, isOutputMode);

    // Your setup code here
  }

  void loop() {
    // Your loop code here
  }
  ```

### digitalWrite(byte pin, bool mode)

- **Description:** Set the digital output value of a specified pin.
- **Parameters:**

  - `pin` (byte): The digital pin number.
  - `mode` (bool): The output mode, where `true` represents HIGH and `false` represents LOW.
- **Details:** The `digitalWrite` method is used to set the digital output value of a specified pin. You can provide the `pin` parameter to specify the digital pin number, and the `mode` parameter to set the output mode. Setting `mode` to `true` will set the pin to HIGH (5V), while setting it to `false` will set the pin to LOW (0V). This method is commonly used for controlling digital devices, such as LEDs or relays.
- **Return Type:** None

- #### Sample Code: How to Use the `digitalWrite` Method

  ```cpp
  #include <Arduino.h>
  #include "NyarkoaPayload.h"

  void setup() {
    // Initialize the NyarkoaPayload instance
    NyarkoaPayload nyarkoa;

    // Define the digital pin and mode
    byte pinNumber = 8;
    bool outputMode = true;

    // Set the digital output value
    nyarkoa.digitalWrite(pinNumber, outputMode);

    // Your setup code here
  }

  void loop() {
    // Your loop code here
  }
  ```

### setAnalogValue(byte pin, int value)

- **Description:** Set the analog output value of a specified pin.
- **Parameters:**

  - `pin` (byte): The analog pin number.
  - `value` (int): The analog output value, ranging from 0 to 255.
- **Details:** The `setAnalogValue` method is used to set the analog output value of a specified pin. You can provide the `pin` parameter to specify the analog pin number, and the `value` parameter to set the output value. The `value` should be an integer between 0 (minimum) and 255 (maximum). This method is commonly used for controlling analog devices, such as servos or dimmable LEDs.
- **Return Type:** None

- #### Sample Code: How to Use the `setAnalogValue` Method

  ```cpp
  #include <Arduino.h>
  #include "NyarkoaPayload.h"

  void setup() {
    // Initialize the NyarkoaPayload instance
    NyarkoaPayload nyarkoa;

    // Define the analog pin and output value
    byte pinNumber = A1;
    int outputValue = 128;  // Any value between 0 and 255

    // Set the analog output value
    nyarkoa.setAnalogValue(pinNumber, outputValue);

    // Your setup code here
  }

  void loop() {
    // Your loop code here
  }
  ```

## Actions

### commAction(String cmd)

- **Description:** Perform a communication action with a specified command.
- **Parameters:**

  - `cmd` (String): The command to perform.
- **Details:** The `commAction` method is used to perform a communication action with a specified command. You can provide the `cmd` parameter to specify the command to execute. This method is essential for establishing communication with external devices or systems by sending the appropriate command.
- **Return Type:** None

- #### Sample Code: How to Use the `commAction` Method

  ```cpp
  #include <Arduino.h>
  #include "NyarkoaPayload.h"

  void setup() {
    // Initialize the NyarkoaPayload instance
    NyarkoaPayload nyarkoa;

    // Define the command to perform
    String command = "CONNECT_DEVICE";

    // Perform the communication action
    nyarkoa.commAction(command);

    // Your setup code here
  }

  void loop() {
    // Your loop code here
  }
  ```

### requestAction(String cmd)

- **Description:** Send a request with a specified command and receive a response.
- **Parameters:**

  - `cmd` (String): The command to include in the request.
- **Details:** The `requestAction` method allows you to send a request with a specified command and receive a response. You can provide the `cmd` parameter to specify the command to include in the request. This method is useful for communicating with external devices or systems that require request-response interactions.
- **Return Type:** String - The response received as a string.

- #### Sample Code: How to Use the `requestAction` Method

  ```cpp
  #include <Arduino.h>
  #include "NyarkoaPayload.h"

  void setup() {
    // Initialize the NyarkoaPayload instance
    NyarkoaPayload nyarkoa;

    // Define the command for the request
    String requestCommand = "GET_DATA";

    // Send the request with the command and receive the response
    String response = nyarkoa.requestAction(requestCommand);

    // Process the response
    Serial.println("Response received: " + response);

    // Your setup code here
  }

  void loop() {
    // Your loop code here
  }
  ```

### ejectBalloon()

- **Description:** Activate the balloon ejection mechanism.
- **Details:** The `ejectBalloon` method is used to activate the balloon ejection mechanism. When called, it triggers the system to release the balloon, which can be essential in certain applications such as high-altitude balloon projects. This method should be used with caution and only in situations where balloon ejection is required.
- **Return Type:** None

- #### Sample Code: How to Use the `ejectBalloon` Method

  ```cpp
  #include <Arduino.h>
  #include "NyarkoaPayload.h"

  void setup() {
    // Initialize the NyarkoaPayload instance
    NyarkoaPayload nyarkoa;

    // Activate the balloon ejection mechanism
    nyarkoa.ejectBalloon();

    // Your setup code here
  }

  void loop() {
    // Your loop code here
  }
  ```

### alert(unsigned long duration = 100)

- **Description:** Trigger an alert for a specified duration.
- **Parameters:**

  - `duration` (unsigned long, optional): The duration of the alert in milliseconds (default is 100ms).
- **Details:** The `alert` method allows you to trigger an alert or signal for a specified duration. This can be useful for signaling events or getting attention in your applications. You can set the `duration` to control how long the alert lasts.
- **Return Type:** None

- #### Sample Code: How to Use the `alert` Method

  ```cpp
  #include <Arduino.h>
  #include "NyarkoaPayload.h"

  void setup() {
    // Initialize the NyarkoaPayload instance
    NyarkoaPayload nyarkoa;

    // Trigger a 500ms alert
    nyarkoa.alert(500);

    // Your setup code here
  }

  void loop() {
    // Your loop code here
  }
  ```

### enableBeacon()

- **Description:** Enable the beacon feature.
- **Details:** The `enableBeacon` method is used to enable the beacon feature in the NyarkoaPayload class. Beacons are signals or indicators used for various purposes, such as location tracking or communication. When you call this method, it activates the beacon functionality, allowing you to utilize this feature as needed in your application.
- **Return Type:** None

- #### Sample Code: How to Enable the Beacon

  ```cpp
  #include <Arduino.h>
  #include "NyarkoaPayload.h"

  void setup() {
    // Initialize the NyarkoaPayload instance
    NyarkoaPayload nyarkoa;

    // Enable the beacon feature
    nyarkoa.enableBeacon();

    // Your setup code here
  }

  void loop() {
    // Your loop code here
  }
  ```

### disableBeacon()

- **Description:** Disable the beacon feature.
- **Details:** The `disableBeacon` method is used to deactivate the beacon feature in the NyarkoaPayload class. Beacons are signals or indicators used for various purposes, such as location tracking or communication. When you call this method, it turns off the beacon functionality, ensuring that the beacon signals are no longer transmitted.
- **Return Type:** None

- #### Sample Code: How to Disable the Beacon

  ```cpp
  #include <Arduino.h>
  #include "NyarkoaPayload.h"

  void setup() {
    // Initialize the NyarkoaPayload instance
    NyarkoaPayload nyarkoa;

    // Disable the beacon feature
    nyarkoa.disableBeacon();

    // Your setup code here
  }

  void loop() {
    // Your loop code here
  }
  ```

### getDate()

- **Description:** Get the current date.
- **Details:** The `getDate` method retrieves the current date using the NyarkoaPayload class. It provides you with the current date, which can be useful for various applications, such as time tracking, data logging, or displaying the date.
- **Return Type:** `String` - A string containing the current date.

- #### Sample Code: How to Get the Current Date

  ```cpp
  #include <Arduino.h>
  #include "NyarkoaPayload.h"

  void setup() {
    // Initialize the NyarkoaPayload instance
    NyarkoaPayload nyarkoa;

    // Get the current date
    String currentDate = nyarkoa.getDate();

    // Print the current date to the Serial Monitor
    Serial.println("Current Date: " + currentDate);

    // Your setup code here
  }

  void loop() {
    // Your loop code here
  }
  ```

### getTime()

- **Description:** Get the current time.
- **Details:** The `getTime` method retrieves the current time using the NyarkoaPayload class. It provides you with the current time, which can be useful for various applications, such as time tracking, data logging, or displaying the time.
- **Return Type:** `String` - A string containing the current time.

- #### Sample Code: How to Get the Current Time

  ```cpp
  #include <Arduino.h>
  #include "NyarkoaPayload.h"

  void setup() {
    // Initialize the NyarkoaPayload instance
    NyarkoaPayload nyarkoa;

    // Get the current time
    String currentTime = nyarkoa.getTime();

    // Print the current time to the Serial Monitor
    Serial.println("Current Time: " + currentTime);

    // Your setup code here
  }

  void loop() {
    // Your loop code here
  }
  ```

### getTimestamp()

- **Description:** Get the current timestamp.
- **Details:** The `getTimestamp` method retrieves the current timestamp using the NyarkoaPayload class. A timestamp represents a specific point in time and is typically expressed as the number of seconds elapsed since a reference time, such as the Unix epoch. This method allows you to obtain a timestamp, which can be useful for various time-related tasks.
- **Return Type:** `String` - A string containing the current timestamp.

- #### Sample Code: How to Get the Current Timestamp

  ```cpp
  #include <Arduino.h>
  #include "NyarkoaPayload.h"

  void setup() {
    // Initialize the NyarkoaPayload instance
    NyarkoaPayload nyarkoa;

    // Get the current timestamp
    String timestamp = nyarkoa.getTimestamp();

    // Print the current timestamp to the Serial Monitor
    Serial.println("Current Timestamp: " + timestamp);

    // Your setup code here
  }

  void loop() {
    // Your loop code here
  }
  ```

### getTimeAfter(int sec = 30, int mins = 0, int hours = 0, int days = 0)

- **Description:** Calculate a future timestamp.
- **Parameters:**

  - `sec` (int, optional): The number of seconds to add. Default is 30.
  - `mins` (int, optional): The number of minutes to add. Default is 0.
  - `hours` (int, optional): The number of hours to add. Default is 0.
  - `days` (int, optional): The number of days to add. Default is 0.
- **Details:** The `getTimeAfter` method calculates a future timestamp by adding a specified number of seconds, minutes, hours, and days to the current timestamp. This can be useful for scheduling events or actions to occur at a future time. You can customize the time duration by providing values for the parameters `sec`, `mins`, `hours`, and `days`.
- **Return Type:** `String` - A string containing the future timestamp in milliseconds.

- #### Sample Code: How to Calculate a Future Timestamp

  ```cpp
  #include <Arduino.h>
  #include "NyarkoaPayload.h"

  void setup() {
    // Initialize the NyarkoaPayload instance
    NyarkoaPayload nyarkoa;

    // Define the time intervals for the future timestamp
    int secondsToAdd = 60; // 60 seconds
    int minutesToAdd = 5; // 5 minutes
    int hoursToAdd = 1;   // 1 hour
    int daysToAdd = 2;    // 2 days

    // Calculate the future timestamp
    String futureTimestamp = nyarkoa.getTimeAfter(secondsToAdd, minutesToAdd, hoursToAdd, daysToAdd);

    // Print the future timestamp to the Serial Monitor
    Serial.println("Future Timestamp (ms): " + futureTimestamp);

    // Your setup code here
  }

  void loop() {
    // Your loop code here
  }
  ```

### getMPLData()

- **Description:** Retrieve pressure, altitude, and temperature data from the MPL.
- **Details:** The `getMPLData` method is used to retrieve pressure, altitude, and temperature data from the MPL (Micropressure Sensor). The MPL is commonly used to measure atmospheric pressure and calculate altitude. This method collects data on atmospheric pressure, altitude, and temperature.
- **Return Type:** `MPLData` - A `MPLData` object containing the following data:

  - `pressure` (float): Atmospheric pressure in pascals.
  - `altitude` (float): Altitude above sea level in meters.
  - `temperature` (float): Temperature in degrees Celsius.

- #### Sample Code: How to Retrieve MPL Data

  ```cpp
  #include <Arduino.h>
  #include "NyarkoaPayload.h"

  void setup() {
    // Initialize the NyarkoaPayload instance
    NyarkoaPayload nyarkoa;

    // Retrieve MPL data
    MPLData mplData = nyarkoa.getMPLData();

    // Display MPL data
    Serial.println("Atmospheric Pressure (Pa): " + String(mplData.pressure));
    Serial.println("Altitude (m): " + String(mplData.altitude));
    Serial.println("Temperature (°C): " + String(mplData.temperature));

    // Your setup code here
  }

  void loop() {
    // Your loop code here
  }
  ```

### getGPSData()

- **Description:** Retrieve GPS data.
- **Details:** The `getGPSData` method is used to retrieve GPS (Global Positioning System) data. This method retrieves information such as the number of satellites, latitude, longitude, date, time, speed, and distance from home location.
- **Return Type:** `GPSData` - A `GPSData` object containing the following data:

  - `nSats` (String): Number of satellites detected.
  - `lat` (String): Latitude.
  - `lon` (String): Longitude.
  - `date` (String): Date information.
  - `time` (String): Time information.
  - `speed` (String): Speed information.
  - `distanceFromHome` (String): Distance from the home location.

- #### Sample Code: How to Retrieve GPS Data

  ```cpp
  #include <Arduino.h>
  #include "NyarkoaPayload.h"

  void setup() {
    // Initialize the NyarkoaPayload instance
    NyarkoaPayload nyarkoa;

    // Retrieve GPS data
    GPSData gpsData = nyarkoa.getGPSData();

    // Display GPS data
    Serial.println("Number of Satellites: " + gpsData.nSats);
    Serial.println("Latitude: " + gpsData.lat);
    Serial.println("Longitude: " + gpsData.lon);
    Serial.println("Date: " + gpsData.date);
    Serial.println("Time: " + gpsData.time);
    Serial.println("Speed: " + gpsData.speed);
    Serial.println("Distance from Home: " + gpsData.distanceFromHome);

    // Your setup code here
  }

  void loop() {
    // Your loop code here
  }
  ```

## License

<!-- OpenCanSatGH - NyarkoaPayload Library -->

<!-- Copyright (c) 2023 CanSAT Ghana -->

<!-- Copyright (c) 2023 CanSAT Ghana -->

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

1. The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
2. **Author and Contact Information:**

   - **Author:** Eric Obeng (Profesir) @Erictronics Systems
   - **Email:** [Write to me](mailto:professor.obeng@gmail.com)
3. The software, code, and documentation are provided "as is," without warranty of any kind, express or implied, including but not limited to the warranties of merchantability, fitness for a particular purpose, and non-infringement. In no event shall the authors or copyright holders be liable for any claim, damages, or other liability, whether in an action of contract, tort, or otherwise, arising from, out of, or in connection with the software or the use or other dealings in the software.
