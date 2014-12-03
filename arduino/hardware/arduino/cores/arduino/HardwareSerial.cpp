/*
  HardwareSerial.cpp - Hardware serial library for Wiring
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
  
  Modified 23 November 2006 by David A. Mellis
  Modified 28 September 2010 by Mark Sproul
  Modified 14 August 2012 by Alarus
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "Arduino.h"
#include "HardwareSerial.h"

//#define DEBUG_HARDWARESERIAL

#define SERIAL_BUFFER_SIZE 64

const char* dev = "/dev/ttyAMA0";
int fd = 0;

struct ring_buffer
{
  unsigned char buffer[SERIAL_BUFFER_SIZE];
  volatile unsigned int head;
  volatile unsigned int tail;
};

ring_buffer rx_buffer = { { 0 }, 0, 0};

// Constructors ////////////////////////////////////////////////////////////////

HardwareSerial::HardwareSerial(ring_buffer *rx_buffer) : _rx_buffer(rx_buffer)
{
  if ((fd = open (dev, O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK)) == -1){
    printf("Cannot open serial device %s!\n", dev);
    exit(1);
  }
}

// Public Methods //////////////////////////////////////////////////////////////

void HardwareSerial::begin(unsigned long baud)
{
  return begin(baud, SERIAL_8N1);
}

void HardwareSerial::begin(unsigned long baud, byte config)
{
#ifdef DEBUG_HARDWARESERIAL
  printf("HardwareSerial::begin baud: %ld, config: 0x%02X\n", baud, config);
#endif
  int status;
  speed_t myBaud;
  switch (baud)
  {
    case    300:	myBaud =    B300 ; break ;
    case    600:	myBaud =    B600 ; break ;
    case   1200:	myBaud =   B1200 ; break ;
    case   1800:	myBaud =   B1800 ; break ;
    case   2400:	myBaud =   B2400 ; break ;
    case   4800:	myBaud =   B4800 ; break ;
    case   9600:	myBaud =   B9600 ; break ;
    case  19200:	myBaud =  B19200 ; break ;
    case  38400:	myBaud =  B38400 ; break ;
    case  57600:	myBaud =  B57600 ; break ;
    case 115200:	myBaud = B115200 ; break ;
    default: printf("Illegal baud rate: %ld\n", baud); return;
  }
  struct termios setting;
  memset(&setting, 0, sizeof(setting));
  setting.c_cflag = CLOCAL | CREAD;
  switch(config){
    case SERIAL_5N1: case SERIAL_5N2: case SERIAL_5E1: 
    case SERIAL_5E2: case SERIAL_5O1: case SERIAL_5O2:
    setting.c_cflag |= CS5;
    break;
    case SERIAL_6N1: case SERIAL_6N2: case SERIAL_6E1: 
    case SERIAL_6E2: case SERIAL_6O1: case SERIAL_6O2:
    setting.c_cflag |= CS6;
    break;
    case SERIAL_7N1: case SERIAL_7N2: case SERIAL_7E1: 
    case SERIAL_7E2: case SERIAL_7O1: case SERIAL_7O2:
    setting.c_cflag |= CS7;
    break;
    case SERIAL_8N1: case SERIAL_8N2: case SERIAL_8E1: 
    case SERIAL_8E2: case SERIAL_8O1: case SERIAL_8O2:
    setting.c_cflag |= CS8;
  }
  switch(config){
    case SERIAL_5N1: case SERIAL_5N2: case SERIAL_6N1: case SERIAL_6N2:
    case SERIAL_7N1: case SERIAL_7N2: case SERIAL_8N1: case SERIAL_8N2:
    setting.c_cflag |= IGNPAR;
    break;
    case SERIAL_5E1: case SERIAL_5E2: case SERIAL_6E1: case SERIAL_6E2:
    case SERIAL_7E1: case SERIAL_7E2: case SERIAL_8E1: case SERIAL_8E2:
    setting.c_cflag |= PARENB;
    break;
    case SERIAL_5O1: case SERIAL_5O2: case SERIAL_6O1: case SERIAL_6O2:
    case SERIAL_7O1: case SERIAL_7O2: case SERIAL_8O1: case SERIAL_8O2:
    setting.c_cflag |= PARENB | PARODD;
  }
  switch(config){
    case SERIAL_5N2: case SERIAL_5E2: case SERIAL_5O2:
    case SERIAL_6N2: case SERIAL_6E2: case SERIAL_6O2:
    case SERIAL_7N2: case SERIAL_7E2: case SERIAL_7O2:
    case SERIAL_8N2: case SERIAL_8E2: case SERIAL_8O2:
    setting.c_cflag |= CSTOPB;
  }
  setting.c_iflag = IGNPAR;
  setting.c_oflag = 0;
  setting.c_lflag = 0;
  setting.c_cc[VMIN] = 0;
  setting.c_cc[VTIME] = 0;
  cfsetspeed(&setting, myBaud);
  tcflush(fd, TCIFLUSH);

  if(tcsetattr (fd, TCSANOW, &setting) == -1){
    printf("Unable to set attribute");
  }

#ifdef DEBUG_HARDWARESERIAL
  printf("cflag: 0x%08X\n", setting.c_cflag);
  printf("iflag: 0x%08X\n", setting.c_iflag);
  printf("oflag: 0x%08X\n", setting.c_oflag);
  printf("lflag: 0x%08X\n", setting.c_lflag);
  if(tcgetattr (fd, &setting) == -1)
    printf("Unable to getattribute");
  printf("cflag: 0x%08X\n", setting.c_cflag);
  printf("iflag: 0x%08X\n", setting.c_iflag);
  printf("oflag: 0x%08X\n", setting.c_oflag);
  printf("lflag: 0x%08X\n", setting.c_lflag);
#endif

  ioctl (fd, TIOCMGET, &status);

  status |= TIOCM_DTR ;
  status |= TIOCM_RTS ;

  ioctl (fd, TIOCMSET, &status);
  tcflush (fd, TCIOFLUSH) ;
  delay(1);

  return;
}

void HardwareSerial::end()
{
  // wait for transmission of outgoing data
  flush();
  // clear any received data
  _rx_buffer->head = _rx_buffer->tail;
  tcflush (fd, TCIOFLUSH) ;
  close(fd);
}

int HardwareSerial::available(void)
{
  if (_rx_buffer->head == _rx_buffer->tail) {
    int buflen;

    if (ioctl (fd, FIONREAD, &buflen) == -1){
      //printf("Cannot read buffer for %s!\n", dev);
      return 0 ;
    }
    if(buflen <= 0){
      return 0;
    }

    int n = ::read(fd, _rx_buffer->buffer, SERIAL_BUFFER_SIZE - 1);
    //tcflush (fd, TCIFLUSH) ;
#ifdef DEBUG_HARDWARESERIAL
    printf("Rx buffer length: %d\n", buflen);
    printf("Read %d bytes from %s.\n", n, dev);
#endif
    if(n <= 0)//In case something wrong happens
      return 0;
    _rx_buffer->head = n;
    _rx_buffer->tail = 0;
  }

  return (unsigned int)(SERIAL_BUFFER_SIZE + _rx_buffer->head - _rx_buffer->tail) % SERIAL_BUFFER_SIZE;
}

int HardwareSerial::peek(void)
{
  if(!available())
    return -1;
  return _rx_buffer->buffer[_rx_buffer->tail];
}

int HardwareSerial::read(void)
{
  // if the head isn't ahead of the tail, we don't have any characters
  if (_rx_buffer->head == _rx_buffer->tail) {
    if(!available())
      return -1;
    return read();
  } else {
    unsigned char c = _rx_buffer->buffer[_rx_buffer->tail];
    _rx_buffer->tail = (unsigned int)(_rx_buffer->tail + 1) % SERIAL_BUFFER_SIZE;
#ifdef DEBUG_HARDWARESERIAL
    printf("read 0x%02X\n", c);
#endif
    return c;
  }
}

void HardwareSerial::flush()
{
  tcdrain(fd);
}

size_t HardwareSerial::write(uint8_t c)
{
#ifdef DEBUG_HARDWARESERIAL
  printf("write 0x%02X\n", c);
#endif
  ::write(fd, &c, 1);
  printf("%c", c);
  if(c == '\n')
    fflush(stdout);
  
  return 1;
}

HardwareSerial::operator bool() {
	return true;
}

// Preinstantiate Objects //////////////////////////////////////////////////////

HardwareSerial Serial(&rx_buffer);
