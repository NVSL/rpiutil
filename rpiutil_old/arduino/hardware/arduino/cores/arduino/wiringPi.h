/*
 * wiringPi:
 *	Arduino compatable (ish) Wiring library for the Raspberry Pi
 *	Copyright (c) 2012 Gordon Henderson
 ***********************************************************************
 * This file is part of wiringPi:
 *	https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 *    wiringPi is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    wiringPi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with wiringPi.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */

#ifndef	__WIRING_PI_H__
#define	__WIRING_PI_H__
#include <stdint.h>

// Handy defines

// Deprecated
#define	NUM_PINS	17

#define	WPI_MODE_PINS		 0
#define	WPI_MODE_GPIO		 1
#define	WPI_MODE_GPIO_SYS	 2
#define	WPI_MODE_PHYS		 3
#define	WPI_MODE_PIFACE		 4
#define	WPI_MODE_UNINITIALISED	-1

// Pin modes

#ifndef INPUT
#define	INPUT			 0
#endif
#ifndef OUTPUT
#define	OUTPUT			 1
#endif
#define	PWM_OUTPUT		 2
#define	GPIO_CLOCK		 3
#define	SOFT_PWM_OUTPUT		 4
#define	SOFT_TONE_OUTPUT	 5
#define	PWM_TONE_OUTPUT		 6

#ifndef LOW
#define	LOW			 0
#endif
#ifndef HIGH
#define	HIGH			 1
#endif

// Pull up/down/none

#define	PUD_OFF			 0
#define	PUD_DOWN		 1
#define	PUD_UP			 2

// PWM

#define	PWM_MODE_MS		0
#define	PWM_MODE_BAL		1

// Interrupt levels

#define	INT_EDGE_SETUP		0
#define	INT_EDGE_FALLING	1
#define	INT_EDGE_RISING		2
#define	INT_EDGE_BOTH		3

// Pi model types and version numbers
//	Intended for the GPIO program Use at your own risk.

#define	PI_MODEL_UNKNOWN	0
#define	PI_MODEL_A		1
#define	PI_MODEL_B		2
#define	PI_MODEL_BP		3
#define	PI_MODEL_CM		4

#define	PI_VERSION_UNKNOWN	0
#define	PI_VERSION_1		1
#define	PI_VERSION_1_1		2
#define	PI_VERSION_1_2		3
#define	PI_VERSION_2		4

#define	PI_MAKER_UNKNOWN	0
#define	PI_MAKER_EGOMAN		1
#define	PI_MAKER_SONY		2
#define	PI_MAKER_QISDA		3

extern const char *piModelNames    [5] ;
extern const char *piRevisionNames [5] ;
extern const char *piMakerNames    [4] ;


//	Intended for the GPIO program Use at your own risk.

// Threads

#define	PI_THREAD(X)	void *X (void *dummy)

// Failure modes

#define	WPI_FATAL	(1==1)
#define	WPI_ALMOST	(1==2)


// wiringPiNodeStruct:
//	This describes additional device nodes in the extended wiringPi
//	2.0 scheme of things.
//	It's a simple linked list for now, but will hopefully migrate to 
//	a binary tree for efficiency reasons - but then again, the chances
//	of more than 1 or 2 devices being added are fairly slim, so who
//	knows....

struct wiringPiNodeStruct
{
  int     pinBase ;
  int     pinMax ;

  int          fd ;	// Node specific
  unsigned int data0 ;	//  ditto
  unsigned int data1 ;	//  ditto
  unsigned int data2 ;	//  ditto
  unsigned int data3 ;	//  ditto

  void   (*pinMode)         (struct wiringPiNodeStruct *node, int pin, int mode) ;
  void   (*pullUpDnControl) (struct wiringPiNodeStruct *node, int pin, int mode) ;
  int    (*digitalRead)     (struct wiringPiNodeStruct *node, int pin) ;
  void   (*digitalWrite)    (struct wiringPiNodeStruct *node, int pin, int value) ;
  void   (*pwmWrite)        (struct wiringPiNodeStruct *node, int pin, int value) ;
  int    (*analogRead)      (struct wiringPiNodeStruct *node, int pin) ;
  void   (*analogWrite)     (struct wiringPiNodeStruct *node, int pin, int value) ;

  struct wiringPiNodeStruct *next ;
} ;

extern struct wiringPiNodeStruct *wiringPiNodes ;

// Function prototypes
//	c++ wrappers thanks to a comment by Nick Lott
//	(and others on the Raspberry Pi forums)

#ifdef __cplusplus
extern "C" {
#endif

// Data

//extern const char *piModelNames [] ;
//extern const char *piRevisionNames[] ;

// Internal

extern int wiringPiFailure (int fatal, const char *message, ...) ;

// Core wiringPi functions

extern struct wiringPiNodeStruct *wiringPiFindNode (int pin) ;
extern struct wiringPiNodeStruct *wiringPiNewNode  (int pinBase, int numPins) ;

extern void initWiringPi        (void) ;
extern int  wiringPiSetup       (void) ;
extern int  wiringPiSetupSys    (void) ;
extern int  wiringPiSetupGpio   (void) ;
extern int  wiringPiSetupPhys   (void) ;

extern void pinModeAlt          (int pin, int mode) ;
extern void pullUpDnControl     (int pin, int pud) ;
extern void pwmWrite            (int pin, int value) ;
extern int  digitalReadQuick    (uint8_t pin) ;
extern void digitalWriteQuick   (uint8_t pin, uint8_t value) ;
#ifndef Arduino_h
extern void pinMode             (uint8_t pin, uint8_t mode) ;
extern int  digitalRead         (uint8_t pin) ;
extern void digitalWrite        (uint8_t pin, uint8_t value) ;
extern int  analogRead          (uint8_t pin) ;
extern void analogWrite         (uint8_t pin, int value) ;
#endif

// PiFace specifics 
//	(Deprecated)

extern int  wiringPiSetupPiFace (void) ;
extern int  wiringPiSetupPiFaceForGpioProg (void) ;	// Don't use this - for gpio program only

// On-Board Raspberry Pi hardware specific stuff

extern int  piBoardRev          (void) ;
extern void piBoardId           (int *model, int *rev, int *mem, int *maker, int *overVolted) ;
extern int  wpiPinToGpio        (int wpiPin) ;
extern int  physPinToGpio       (int physPin) ;
extern void setPadDrive         (int group, int value) ;
extern int  getAlt              (int pin) ;
extern void pwmToneWrite        (int pin, int freq) ;
extern void digitalWriteByte    (int value) ;
extern void pwmSetMode          (int mode) ;
extern void pwmSetRange         (unsigned int range) ;
extern void pwmSetClock         (int divisor) ;
extern void gpioClockSet        (int pin, int freq) ;

// Interrupts
//	(Also Pi hardware specific)

extern int  waitForInterrupt    (int pin, int mS) ;
extern int  wiringPiISR         (int pin, int mode, void (*function)(void)) ;

// Threads

extern int  piThreadCreate      (void *(*fn)(void *)) ;
extern void piLock              (int key) ;
extern void piUnlock            (int key) ;

// Schedulling priority

extern int piHiPri (const int pri) ;

// Extras from arduino land

extern uint64_t tick            (void) ;
#ifndef Arduino_h
extern void         delay             (unsigned long howLong) ;
extern void         delayMicroseconds (unsigned int howLong) ;
extern unsigned long millis            (void) ;
extern unsigned long micros            (void) ;
#endif

#ifdef __cplusplus
}
#endif

#endif
