#include <SimpleFOC.h>

// Motor sensor configuration.
#define MS_PIN A5
#define MS_RAW_MIN 4
#define MS_RAW_MAX 926

// Create our magnetic sensor object.
MagneticSensorPWM motorSensor = MagneticSensorPWM(MS_PIN, MS_RAW_MIN, MS_RAW_MAX);

void setup() {
  Serial.begin(115200);

  // Initialise the magnetic sensor.
  motorSensor.init();
  _delay(1000);
}

void loop() {
  // Print the sensor angle and velocity every 100ms.
  Serial.print(motorSensor.getAngle());
  Serial.print("\t");
  Serial.println(motorSensor.getVelocity());
  _delay(100);
}
