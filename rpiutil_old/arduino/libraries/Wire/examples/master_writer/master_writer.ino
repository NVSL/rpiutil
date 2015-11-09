// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Arduino.h>
#include <Wire.h>
#include <cstdio>

void setup()
{
  Wire.begin(0x50); // join i2c bus (address optional for master)
}

byte x = 0;

void loop()
{
  Wire.beginTransmission(0x50); // transmit to device #4
  printf("%d\n", x);
  Wire.write("x is ");        // sends five bytes
  Wire.write(x++);              // sends one byte  
  Wire.endTransmission();    // stop transmitting
  delay(500);
}
