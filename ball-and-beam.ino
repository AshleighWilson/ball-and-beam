#include <Arduino.h>
#include <Wire.h>

// Arduino Wire library uses 7-bit I2C addresses, however the TOF10120 uses an
// 8-bit address. So we need to bit-shift to the right to turn into a 7-bit
// address. TOF101 default slave address as defined in the datasheet is 0xA4,
// so this becomes 0x52 after bit-shifting.
// For more info: https://www.arduino.cc/en/Reference/Wire
#define TOF10120_ADDR 0x52

int tofMeasure() {
  unsigned char i2cBuffer[1];

  // Transmit to device to receive response.
  Wire.beginTransmission(TOF10120_ADDR);
  Wire.write(0x00);
  Wire.endTransmission();

  // Request two bytes from the sensor.
  Wire.requestFrom(TOF10120_ADDR, 2);

  // If two bytes have been received then store them into buffer.
  if(Wire.available() >= 2) {
    i2cBuffer[0] = Wire.read();
    i2cBuffer[1] = Wire.read();
  }

  // Combine both received bytes before returning.
  return (i2cBuffer[0] << 8) | i2cBuffer[1];
}

void setup() {
  // Initiate the I2C bus and join as a master.
  Wire.begin();

  Serial.begin(9600);
  Serial.println("TOF10120 Sensor Test Ready!");
}

void loop() {
  int distance = tofMeasure();
  Serial.print(distance);
  Serial.println(" mm");
}

