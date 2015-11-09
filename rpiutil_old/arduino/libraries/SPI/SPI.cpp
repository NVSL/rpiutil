/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@bug.st>
 * SPI Master library for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#include <Arduino.h>
#include "SPI.h"

SPIClass SPI;

#define DEBUG 0
const static char       *spiDev0  = "/dev/spidev0.0" ;
//const static char       *spiDev1  = "/dev/spidev0.1" ;
const static int        fullSpeed = 16000000;
static uint8_t spiMode = 0x0;
static uint8_t spiBPW = 8;
static int fd;
static int spiSpeed = fullSpeed;

static int __spidev_set_mode( int fd, __u8 mode) {
    __u8 test;
    if(DEBUG){
        printf("__spidev_set_mode 0x%02X\n", mode);
    }
    if (ioctl(fd, SPI_IOC_WR_MODE, &mode) == -1) {
        return -1;
    }
    if (ioctl(fd, SPI_IOC_RD_MODE, &test) == -1) {
        return -1;
    }
    if (test != mode) {
        return -1;
    }
    return 0;
}

void SPIClass::begin() 
{
    if ((fd = open ( spiDev0, O_RDWR)) < 0){
        printf("Unable to open SPI device: %s\n", spiDev0);
        exit(1);
    }

    if (ioctl (fd, SPI_IOC_WR_MODE, &spiMode) < 0){
        printf("SPI Mode Change failure!\n");
        exit(1);
    }

    if (ioctl (fd, SPI_IOC_WR_BITS_PER_WORD, &spiBPW) < 0){
        printf("Failed to change BPW!\n");
        exit(1);
    }

    if (ioctl (fd, SPI_IOC_WR_MAX_SPEED_HZ, &spiSpeed)   < 0){
        printf("Failed to change SPI speed.\n");
        exit(1);
    }
}

void SPIClass::end() 
{
    if(close( fd ) < 0){
        printf("Failed to close SPI dev!\n");
        exit(1);
    }
}

void SPIClass::setBitOrder(uint8_t bitOrder)
{
    if(DEBUG){
        printf("setBitOrder %s\n", bitOrder == LSBFIRST ? 
        "LSBFIRST" : "MSBFIRST");
    }
    if(bitOrder == LSBFIRST)
        spiMode |= SPI_LSB_FIRST;
    else if(bitOrder == MSBFIRST)
        spiMode &= ~SPI_LSB_FIRST;
    __spidev_set_mode(fd, spiMode);
}

void SPIClass::setDataMode(uint8_t mode)
{
    if(DEBUG){
        printf("setDataMode 0x%02X\n", mode);
    }
    if(mode <= 3){
        spiMode &= ~SPI_MODE_MASK;
        spiMode |= mode;
        __spidev_set_mode(fd, mode);
    }
}

void SPIClass::setClockDivider(uint8_t rate)
{
    if(DEBUG){
        printf("setClockDivider %d\n", rate);
    }
    if(rate > SPI_CLOCK_DIV64)
        rate = SPI_CLOCK_DIV64;
    spiSpeed = fullSpeed >> rate;
    if (ioctl (fd, SPI_IOC_WR_MAX_SPEED_HZ, &spiSpeed)   < 0){
        printf("Failed to change SPI speed.\n");
        exit(1);
    }
}

byte SPIClass::transfer(byte data){
    struct spi_ioc_transfer spi ;
    if(DEBUG){
        printf("sent 0x%02X\n", data);
    }

    spi.tx_buf        = (unsigned long)&data ;
    spi.rx_buf        = (unsigned long)&data ;
    spi.len           = 1 ;
    spi.delay_usecs   = 0 ;
    spi.speed_hz      = spiSpeed ;
    spi.bits_per_word = spiBPW ;

    if(ioctl (fd, SPI_IOC_MESSAGE(1), &spi) < 0)
        return 0;
    if(DEBUG){
        printf("got 0x%02x\n", data);
    }
    return data;
}
