// sources: https://playground.arduino.cc/Main/MPU-6050
#include <Wire.h>
#define USE_HSV // enable hsv mode
#include <WS2812.h>

#define MAX_BRIGHTNESS 255
#define MPUADDR 0x68

#define CHANGE_FACTOR 2400
#define DEBOUNCE_DELAY 66
#define NUM_MODES 2

WS2812 LED(3);
uint8_t mode = 0;

int16_t acX, acY, acZ, GyX, GyY, GyZ; // Temp
int16_t acXf, acYf, acZf; // temp

// HUE MODE
int16_t hue = 0, sat = 255, val = 64;
float change;

// FIRE MODE
cRGB led1;
cRGB led2;
cRGB led3;
int16_t s; // anim speed
int16_t r; // amount of red
float f, rf, gf;

void flicker(cRGB *rgb) {
  f = random(64) - 20; // colors get brighter
  rf = random(16) - 8;
  gf = random(16) - 6; // yellows are more often
  rgb->r += rf + f;
  rgb->g += gf + f;

  // darker colors have more reds
  if (rgb->r <= r) {
    rgb->g = rgb->g - rgb->r / 2;
  }

  // bright colors flicker to darker colors
  rgb->r = rgb->r >= 254 ? 10 : (rgb->r <= 0 ? 0 : rgb->r);
  rgb->g = rgb->g >= 254 ? 10 : (rgb->g <= 0 ? 0 : rgb->g);

  // there is never a green flame (not even slightly)
  rgb->g = rgb->g > rgb->r ? rgb->r : rgb->g;
  // there is never a red flame (but a little is ok)
  rgb->r = rgb->r - 100 >= rgb->g ? rgb->r - 50 : rgb->r;

}
void setup() {
  Wire.begin();
  Wire.beginTransmission(MPUADDR);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  LED.setOutput(3); // Digital Pin 9

  // fire mode
  s = 33;
  r = 120;
}

void loop() {
  Wire.beginTransmission(MPUADDR);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPUADDR, 14); // request a total of 14 registers
  acX = (Wire.read() << 8 | Wire.read()); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  acY = (Wire.read() << 8 | Wire.read()); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  acZ = (Wire.read() << 8 | Wire.read()); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  // Temp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  // GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  // GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  // GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  // low pass filter to remove noise:
  acXf = acXf * 0.7 + 0.3 * (acX); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  acYf = acYf * 0.7 + 0.3 * (acY); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  acZf = acZf * 0.7 + 0.3 * (acZ); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)


  if ( abs(acX - acXf) > 8000 || abs(acY - acYf) > 8000 || abs(acZ - acZf) > 8000) {
    mode = (mode + 1) % NUM_MODES;
    led1.SetHSV(1, 1, 1);
    LED.set_crgb_at(0, led1);
    LED.set_crgb_at(1, led1);
    LED.set_crgb_at(2, led1);
    LED.sync();
    delay(3000);
  }

  switch (mode) {
    case 1: // fire

      if (abs(acXf) > CHANGE_FACTOR) {
        r = r + (acXf * (1.0 / CHANGE_FACTOR));
        r = r >= 180 ? 180 : r;
        r = r <= 0 ? 0 : r;
        delay(DEBOUNCE_DELAY); // debounce
      }

      if (abs(acYf) > CHANGE_FACTOR) {
        s = s + (acYf * (1.0 / CHANGE_FACTOR));
        s = s >= 1000 ? 1000 : s;
        s = s <= 10 ? 10 : s;
        delay(DEBOUNCE_DELAY); // debounce
      }

      delay(1000 / s);

      switch (random(0, 3)) {
        case 0:
          flicker(&led1);
          break;
        case 1:
          flicker(&led2);
          break;
        case 2:
          flicker(&led3);
          break;
      }

      LED.set_crgb_at(0, led1);
      LED.set_crgb_at(1, led2);
      LED.set_crgb_at(2, led3);
      LED.sync();
      break;
    case 0:
    default:
      if (abs(acXf) > CHANGE_FACTOR) {
        hue = hue + (acXf * (1.0 / CHANGE_FACTOR));
        hue = hue >= 360 ? 1 : hue;
        hue = hue <= 0 ? 359 : hue;
        delay(DEBOUNCE_DELAY); // debounce
      }

      if (abs(acYf) > CHANGE_FACTOR) {
        val = val + (acYf * (1.0 / CHANGE_FACTOR));
        val = val >= MAX_BRIGHTNESS ? MAX_BRIGHTNESS : val;
        val = val <= 5 ? 5 : val;
        delay(DEBOUNCE_DELAY); // debounce
      }
      led1.SetHSV(hue, sat, val);
      LED.set_crgb_at(0, led1);
      LED.set_crgb_at(1, led1);
      LED.set_crgb_at(2, led1);
      LED.sync();
  }


  delay(1000 / 200);
}
