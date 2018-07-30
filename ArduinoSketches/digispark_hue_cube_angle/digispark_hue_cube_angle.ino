// sources: https://playground.arduino.cc/Main/MPU-6050
#include <Wire.h>
#include <WS2812.h>

WS2812 LED(3);
cRGB value;
#define MAX_BRIGHTNESS 128
#define MPUADDR 0x68
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

void setup() {
  delay(200);
  digitalWrite(1, HIGH);
  delay(200);
  digitalWrite(1, LOW);
  delay(200);
  digitalWrite(1, HIGH);
  delay(200);
  digitalWrite(1, LOW);
  delay(200);
  digitalWrite(1, HIGH);
  delay(200);
  digitalWrite(1, LOW);

  Wire.begin();
  Wire.beginTransmission(MPUADDR);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  LED.setOutput(3); // Digital Pin 9
}

void loop() {
  Wire.beginTransmission(MPUADDR);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPUADDR, 14); // request a total of 14 registers
  
  // low pass filter to remove noise:
  AcX = AcX * 0.95 + 0.05 * (Wire.read() << 8 | Wire.read()); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = AcY * 0.95 + 0.05 * (Wire.read() << 8 | Wire.read()); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = AcZ * 0.95 + 0.05 * (Wire.read() << 8 | Wire.read()); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  // Tmp/340.00+36.53  //equation for temperature in degrees C from datasheet

  if (AcX > 1000) {
    digitalWrite(1, HIGH);
  } else {
    digitalWrite(1, LOW);
  }

  value.r = abs(AcX) >= 32768 / 2 ? MAX_BRIGHTNESS : map(abs(AcX), 0, 32768 / 2, 0, MAX_BRIGHTNESS);
  value.g = abs(AcY) >= 32768 / 2 ? MAX_BRIGHTNESS : map(abs(AcY), 0, 32768 / 2, 0, MAX_BRIGHTNESS);
  value.b = abs(AcZ) >= 32768 / 2 ? MAX_BRIGHTNESS : map(abs(AcZ), 0, 32768 / 2, 0, MAX_BRIGHTNESS);

  LED.set_crgb_at(0, value);
  LED.set_crgb_at(1, value);
  LED.set_crgb_at(2, value);
  LED.sync();

  delay(1000 / 100);
}
