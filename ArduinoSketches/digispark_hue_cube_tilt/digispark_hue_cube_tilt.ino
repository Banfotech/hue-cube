// sources: https://playground.arduino.cc/Main/MPU-6050
#include <Wire.h>
#define USE_HSV // enable hsv mode
#include <WS2812.h>

#define MAX_BRIGHTNESS 255
#define MPUADDR 0x68

#define CHANGE_FACTOR 2400
#define DEBOUNCE_DELAY 66

WS2812 LED(3);
cRGB value;

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPUADDR);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  LED.setOutput(3); // Digital Pin 9
}

int16_t acX, acY, acZ, Temp, GyX, GyY, GyZ;
int16_t acXf, acYf, acZf, temp;
int16_t h = 0, s = 0, v = 60;
float change;

void loop() {
  Wire.beginTransmission(MPUADDR);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPUADDR, 14); // request a total of 14 registers
  acX = (Wire.read() << 8 | Wire.read()); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  acY = (Wire.read() << 8 | Wire.read()); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  acZ = (Wire.read() << 8 | Wire.read()); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Temp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  // low pass filter to remove noise:
  acXf = acXf * 0.7 + 0.3 * (acX); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  acYf = acYf * 0.7 + 0.3 * (acY); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  acZf = acZf * 0.7 + 0.3 * (acZ); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

  if (abs(acXf) > CHANGE_FACTOR) {
    h = h + (acXf * (1.0 / CHANGE_FACTOR));
    h = h >= 360 ? 1 : h;
    h = h <= 0 ? 359 : h;
    delay(DEBOUNCE_DELAY); // debounce
  }

  if (abs(acYf) > CHANGE_FACTOR) {
    s = s + (acYf * (1.0 / CHANGE_FACTOR));
    s = s >= 254 ? 245 : s;
    s = s <= 10 ? 10 : s;
    delay(DEBOUNCE_DELAY); // debounce
  }

  v = MAX_BRIGHTNESS;

  value.SetHSV(h, s, v);

  LED.set_crgb_at(0, value);
  LED.set_crgb_at(1, value);
  LED.set_crgb_at(2, value);
  LED.sync();

  delay(1000 / 200);
}
