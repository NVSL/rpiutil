/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@bug.st>
 * SPI Master library for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

#include <stdio.h>
#include <Arduino.h>
#include <linux/spi/spidev.h>
//#include <avr/pgmspace.h>

#define SPI_CLOCK_DIV4 0x02
#define SPI_CLOCK_DIV16 0x04
#define SPI_CLOCK_DIV64 0x06
#define SPI_CLOCK_DIV128 0x07
#define SPI_CLOCK_DIV2 0x01
#define SPI_CLOCK_DIV8 0x03
#define SPI_CLOCK_DIV32 0x05
//#define SPI_CLOCK_DIV64 0x06

#define SPI_MODE0 SPI_MODE_0
#define SPI_MODE1 SPI_MODE_1
#define SPI_MODE2 SPI_MODE_2
#define SPI_MODE3 SPI_MODE_3

#define SPI_MODE_MASK (SPI_CPOL|SPI_CPHA) 
//#define SPI_CLOCK_MASK 0x03
//#define SPI_2XCLOCK_MASK 0x01

uint8_t SPCR = 0;
uint8_t SPDR = 0;

class SPIClass {
public:
  static byte transfer(byte _data);

  // SPI Configuration methods

//  inline static void attachInterrupt();
//  inline static void detachInterrupt(); // Default

  static void begin(); // Default
  static void end();

  static void setBitOrder(uint8_t);
  static void setDataMode(uint8_t);
  static void setClockDivider(uint8_t);
};

extern SPIClass SPI;
/*
void SPIClass::attachInterrupt() {
  SPCR |= _BV(SPIE);
}

void SPIClass::detachInterrupt() {
  SPCR &= ~_BV(SPIE);
}
*/
#endif
