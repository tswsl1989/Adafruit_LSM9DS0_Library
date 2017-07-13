#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS0.h>
#include <Adafruit_Sensor.h>  // not used in this demo but required!

/***** Dual IMU test program

Requires two LSM9DS0 boards to be connected, or will hang at startup.
The second board (lsm1) needs to have SDOXM and SDOG shorted to ground.

Otherwise this is very similar to the lsm9dof test program, which it is based on.
***/

// i2c
Adafruit_LSM9DS0 lsm0 = Adafruit_LSM9DS0(0, true);
Adafruit_LSM9DS0 lsm1 = Adafruit_LSM9DS0(1, false);

long i = 0;
void setupSensor()
{
  // 1.) Set the accelerometer range
  lsm0.setupAccel(lsm0.LSM9DS0_ACCELRANGE_2G);
  lsm1.setupAccel(lsm1.LSM9DS0_ACCELRANGE_2G);

  // 2.) Set the magnetometer sensitivity
  lsm0.setupMag(lsm0.LSM9DS0_MAGGAIN_2GAUSS);
  lsm1.setupMag(lsm1.LSM9DS0_MAGGAIN_2GAUSS);

  // 3.) Setup the gyroscope
  lsm0.setupGyro(lsm0.LSM9DS0_GYROSCALE_245DPS);
  lsm1.setupGyro(lsm1.LSM9DS0_GYROSCALE_245DPS);
}

void setup() 
{
  while (!Serial); // flora & leonardo

  Serial.begin(115200);
  Serial.println("LSM raw read demo");

  // Try to initialise and warn if we couldn't detect the chip
  Serial.print("LSM0 Startup...");
  if (!lsm0.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM9DS0. Check your wiring!");
    while (1);
  }
  Serial.println("Done.");

  Serial.print("LSM1 Startup...");
  if (!lsm1.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM9DS0. Check your wiring!");
    while (1);
  }
  Serial.println("Done.");
  Serial.println("Found LSM9DS0 9DOF");
  Serial.println("");
  Serial.println("INDEX,CARD,AX,AY,AZ,MX,MY,MZ,GX,GY,GZ,TEMP");

}

void loop() 
{
  lsm0.read();
  lsm1.read();
// An incrementing index is used - this and the card IDs make this easy to feed into other software
  i++;
// Output values for first card
  Serial.print(i);
  Serial.print(",");
  Serial.print("A");
  Serial.print(",");
  Serial.print((int)lsm0.accelData.x);
  Serial.print(",");
  Serial.print((int)lsm0.accelData.y);
  Serial.print(",");
  Serial.print((int)lsm0.accelData.z);
  Serial.print(",");
  Serial.print((int)lsm0.magData.x);
  Serial.print(",");
  Serial.print((int)lsm0.magData.y);
  Serial.print(",");
  Serial.print((int)lsm0.magData.z);
  Serial.print(",");
  Serial.print((int)lsm0.gyroData.x);
  Serial.print(",");
  Serial.print((int)lsm0.gyroData.y);
  Serial.print(",");
  Serial.print((int)lsm0.gyroData.z);
  Serial.print(",");
  Serial.println((int)lsm0.temperature);
// Now output values for second card
  Serial.print(i);
  Serial.print(",");
  Serial.print("B");
  Serial.print(",");
  Serial.print((int)lsm1.accelData.x);
  Serial.print(",");
  Serial.print((int)lsm1.accelData.y);
  Serial.print(",");
  Serial.print((int)lsm1.accelData.z);
  Serial.print(",");
  Serial.print((int)lsm1.magData.x);
  Serial.print(",");
  Serial.print((int)lsm1.magData.y);
  Serial.print(",");
  Serial.print((int)lsm1.magData.z);
  Serial.print(",");
  Serial.print((int)lsm1.gyroData.x);
  Serial.print(",");
  Serial.print((int)lsm1.gyroData.y);
  Serial.print(",");
  Serial.print((int)lsm1.gyroData.z);
  Serial.print(",");
  Serial.println((int)lsm1.temperature);
  delay(200);
}
