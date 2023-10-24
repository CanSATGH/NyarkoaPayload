```markdown
### Method: `debug(String text, bool newline = true)`

Prints debugging information.

- `text` (string): The text to print.
- `newline` (bool, optional): Whether to add a newline character. Default is `true`.

Example:```cpp
nyarkoa->debug("This is a test debug message", true);
```

### Method: `contains(String str, String substr)`

Checks if a string contains a substring.

- `str` (string): The string to search in.
- `substr` (string): The substring to search for.

Example:

```cpp
bool containsSubstring = nyarkoa->contains("Hello, world!", "world");
```

### Method: `simpleHash(String data)`

Generates a simple hash for the given data.

- `data` (string): The data to hash.

Returns the computed hash as a string.

Example:

```cpp
String hash = nyarkoa->simpleHash("myData123");
```

### Method: `compareHash(String data, String hash)`

Compares a data string with a hash.

- `data` (string): The data string to compare.
- `hash` (string): The hash to compare against.

Returns `true` if the data and hash match; otherwise, `false`.

Example:

```cpp
bool isMatching = nyarkoa->compareHash("myData123", "hashedValue");
```

### Method: `clearSerial()`

Clears the serial communication buffer.

Example:

```cpp
nyarkoa->clearSerial();
```

### Method: `activateDevMode()`

Activates development mode for debugging.

Example:

```cpp
nyarkoa->activateDevMode();
```

### Method: `activateProdMode()`

Activates production mode to disable debugging.

Example:

```cpp
nyarkoa->activateProdMode();
```

### Method: `setPinMode(byte pin, bool mode)`

Sets the mode of a pin.

- `pin` (byte): The pin to set the mode for.
- `mode` (bool): The mode to set (INPUT or OUTPUT).

Example:

```cpp
nyarkoa->setPinMode(13, OUTPUT);
```

### Method: `digitalWrite(byte pin, bool state)`

Writes a digital value to a pin.

- `pin` (byte): The pin to write to.
- `state` (bool): The state to set (HIGH or LOW).

Example:

```cpp
nyarkoa->digitalWrite(13, HIGH);
```

### Method: `setAnalogValue(byte pin, int value)`

Sets an analog value on a PWM (pulse-width modulation) pin.

- `pin` (byte): The PWM pin to set the value for.
- `value` (int): The value to set (0 to 255).

Example:

```cpp
nyarkoa->setAnalogValue(9, 128);
```

### Method: `transmit(String data)`

Transmits data through the serial communication.

- `data` (string): The data to transmit.

Example:

```cpp
nyarkoa->transmit("Hello, world!");
```

### Method: `request(String req)`

Sends a request and processes the response.

- `req` (string): The request to send.

Returns a `Response` object with success status and message.

Example:

```cpp
Response response = nyarkoa->request("GET /data");
```

### Method: `executeCmd(String cmd)`

Executes a command and handles the response.

- `cmd` (string): The command to execute.

Returns a `Response` object with success status and message.

Example:

```cpp
Response response = nyarkoa->executeCmd("AT_CHECK");
```

### Method: `receive()`

Receives data from the serial communication.

Returns the received data as a string.

Example:

```cpp
String receivedData = nyarkoa->receive();
```

### Method: `connect()`

Connects to the communication module.

Returns a `Response` object with success status and message.

Example:

```cpp
Response response = nyarkoa->connect();
```

### Method: `startCommunication()`

Starts the communication module and connects to it.

Returns a `Response` object with success status and message.

Example:

```cpp
Response response = nyarkoa->startCommunication();
```

### Method: `commAction(String cmd)`

Performs a communication module action.

- `cmd` (string): The command to execute.

Example:

```cpp
nyarkoa->commAction("AT_SEND");
```

### Method: `requestAction(String cmd)`

Sends a request action to the communication module.

- `cmd` (string): The request command to send.

Returns the response message if successful; otherwise, an empty string.

Example:

```cpp
String response = nyarkoa->requestAction("SEND_DATA");
```

### Method: `contactGroundStation(String cmd, String payload)`

Contacts the ground station with a command and payload.

- `cmd` (string): The command to send.
- `payload` (string): The payload data.

Returns `true` if the contact is successful; otherwise, `false`.

Example:

```cpp
bool contacted = nyarkoa->contactGroundStation("SEND", "Hello, ground!");
```

### Method: `readADC(byte pin)`

Reads an analog value from the specified pin.

- `pin` (byte): The analog pin to read.

Returns the analog value as an unsigned integer.

Example:

```cpp
unsigned int analogValue = nyarkoa->readADC(A0);
```

### Method: `ejectBalloon()`

Ejects the balloon in the payload.

Example:

```cpp
nyarkoa->ejectBalloon();
```

### Method: `alert(unsigned long duration = 100)`

Triggers an alert for a specified duration.

- `duration` (unsigned long, optional): The alert duration in milliseconds. Default is 100ms.

Example:

```cpp
nyarkoa->alert(500);
```

### Method: `enableBeacon()`

Enables the beacon for tracking.

Example:

```cpp
nyarkoa->enableBeacon();
```

### Method: `disableBeacon()`

Disables the beacon.

Example:

```cpp
nyarkoa->disableBeacon();
```

### Method: `getDate()`

Gets the current date.

Returns the current date as a string.

Example:

```cpp
String currentDate = nyarkoa->getDate();
```

### Method: `getTime()`

Gets the current time.

Returns the current time as a string.

Example:

```cpp
String currentTime = nyarkoa->getTime();
```

### Method: `getTimestamp()`

Gets the current timestamp.

Returns the current timestamp as a string.

Example:

```cpp
String timestamp = nyarkoa->getTimestamp();
```

### Method: `getTimeAfter(int sec = 30, int mins = 0, int hours = 0, int days = 0)`

Calculates the time after a specified duration.

- `sec` (int, optional): The number of seconds to add.
- `mins` (int, optional): The number of minutes to add.
- `hours` (int, optional): The number of hours to add.
- `days` (int, optional): The number of days to add.

Returns the calculated time as a string.

Example:

```cpp
String futureTime = nyarkoa->getTimeAfter(60, 30, 1);
```

### Method: `getMPUData()`

Gets MPU (Motion Processing Unit) sensor data.

Returns an `MPUData` structure with accelerometer, gyroscope, and temperature data.

Example:

```cpp
MPUData mpuData = nyarkoa->getMPUData();
```

### Method: `getMPLData()`

Gets MPL (Pressure and Altitude) sensor data.

Returns an `MPLData` structure with pressure, altitude, and temperature data.

Example:

```cpp
MPLData mplData = nyarkoa->getMPLData();
```

### Method: `getGPSData()`

Gets GPS sensor data.

Returns a `GPSData` structure with satellite count, latitude, longitude, date, time, speed, and distance data.

Example:

```cpp
GPSData gpsData = nyarkoa->getGPSData();
```

```markdown
### Method: `getInstance()`

Obtains an instance of the `NyarkoaPayloadTest` class. 

Returns a pointer to the class instance.

Example:

```cpp
NyarkoaPayloadTest* instance = NyarkoaPayloadTest::getInstance();
```

### Method: `pinInfo(byte pin)`

Checks if a pin has been assigned a specific function.

- `pin` (byte): The pin number to check.

Returns `true` if the pin has been assigned a function; otherwise, `false`.

Example:

```cpp
bool isAssigned = nyarkoa->pinInfo(13);
```

### Method: `NyarkoaPayloadTest()`

Constructor for the `NyarkoaPayloadTest` class. Initializes the class instance.

Example:

```cpp
NyarkoaPayloadTest payload;
```

### Method: `~NyarkoaPayloadTest()`

Destructor for the `NyarkoaPayloadTest` class. Cleans up resources when an instance is destroyed.

Example:

```cpp
NyarkoaPayloadTest* payload = new NyarkoaPayloadTest();
delete payload;
```
