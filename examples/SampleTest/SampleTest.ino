#include <NyarkoaPayloadTest.h>
MPUData mpu;
MPLData mpl;
GPSData gps;
NyarkoaPayloadTest nyarkoa;

void setup() {
  Serial.begin(115200);
  nyarkoa.setPinMode(nyarkoa.LED, OUTPUT);

  // Try to connect comm module
  Response resp = nyarkoa.connectToCommModule();
  if (!resp.isOk) {
    nyarkoa.debug(resp.message);
    nyarkoa.debug("Resetting payload.");
    nyarkoa.resetPayload();
  }
  nyarkoa.debug(resp.message);

  // Test bed
  nyarkoa.ejectBalloon();
  nyarkoa.alert(100);
  nyarkoa.enableBeacon();
  nyarkoa.disableBeacon();
  Serial.println("Date: " + nyarkoa.getDate());
  Serial.println("Time: " + nyarkoa.getTime());
  Serial.println("Timestamp: " + nyarkoa.getTimestamp());
  Serial.println("future time: " + nyarkoa.getTimeAfter());
}

void loop() {
  digitalWrite(nyarkoa.LED, HIGH);
  delay(500);
  digitalWrite(nyarkoa.LED, LOW);
  delay(500);

  mpu = nyarkoa.getMPUData();
  Serial.println("accelX: " + String(mpu.accelX) + " | accelY: " +
                 String(mpu.accelY) + " | accelZ: " + String(mpu.accelZ));

  Serial.println(
      "gyroX: " + String(mpu.gyroX) + " | gyroY: " + String(mpu.gyroY) +
      " | gyroZ: " + String(mpu.gyroZ) + " | temp: " + String(mpu.temp));

  mpl = nyarkoa.getMPLData();
  Serial.println("Pressure: " + String(mpl.pressure) +
                 " | altitude: " + String(mpl.altitude) +
                 " | temperature: " + String(mpl.temperature));

  gps = nyarkoa.getGPSData();
  Serial.println("nSats: " + gps.nSats + " | lat: " + gps.lat +
                 " | lon: " + gps.lon + " | Date: " + gps.date +
                 " | Time: " + gps.time + " | Speed: " + gps.speed +
                 " | Distance from home: " + gps.distanceFromHome);

  delay(10000);
}