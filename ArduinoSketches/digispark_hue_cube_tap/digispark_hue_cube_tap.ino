// sources: https://playground.arduino.cc/Main/MPU-6050
#include <Wire.h>
#include <WS2812.h>

WS2812 LED(3);
cRGB value;
#define MAX_BRIGHTNESS 64
#define MPUADDR 0x68

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
  LED.setOutput(3);
}

int16_t acX, acY, acZ, Tmp, GyX, GyY, GyZ;
int16_t acXf, acYf, acZf;

int8_t i = -1;

void loop() {
  Wire.beginTransmission(MPUADDR);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPUADDR, 14); // request a total of 14 registers
  acX = (Wire.read() << 8 | Wire.read()); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  acY = (Wire.read() << 8 | Wire.read()); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  acZ = (Wire.read() << 8 | Wire.read()); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  // low pass filter to remove noise:
  acXf = acXf * 0.7 + 0.3 * (acX); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  acYf = acYf * 0.7 + 0.3 * (acY); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  acZf = acZf * 0.7 + 0.3 * (acZ); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

  if ( abs(acX - acXf) > 8000 || abs(acX - acXf) > 8000 || abs(acX - acXf) > 8000) {
    i++;
    switch (i) {
      case 0:
        value.r = 255;
        value.g = 1;
        value.b = 1;
        break;
      case 1:
        value.r = 1;
        value.g = 255;
        value.b = 1;
        break;
      case 2:
        value.r = 255;
        value.g = 255;
        value.b = 1;
        break;
      case 3:
        value.r = 1;
        value.g = 1;
        value.b = 255;
        break;
      case 4:
        value.r = 255;
        value.g = 1;
        value.b = 255;
        break;
      case 5:
        value.r = 255;
        value.g = 255;
        value.b = 255;
        break;
      default:
        value.r = 255;
        value.g = 1;
        value.b = 1;
        i = 0;
    }
    LED.set_crgb_at(0, value);
    LED.set_crgb_at(1, value);
    LED.set_crgb_at(2, value);
    LED.sync();
    
    delay(1500); // debounce
  }

  delay(1000 / 200);
}
