#ifndef BUZZER_INCLUDED
#define BUZZER_INCLUDED

#include <Arduino.h>

class LED {
     enum {BLINK, ON, OFF};

     int pin;
     int onTime;
     int offTime;
     int state;
     bool powered;
     unsigned int nextTransition;

public:
     LED(int pin): 
	  pin(pin), 
	  onTime(onTime), 
	  offTime(offTime) {
	  pinMode(pin, OUTPUT);
	  digitalWrite(pin, LOW);
	  state = OFF;
	  powered = false;
     }
     
     void update() {
	  if (state == BLINK) {
	       if (millis() > nextTransition) {
		    toggle();
		    nextTransition = millis() + offTime;
	       }
	  }
     }

     void blink(int on, int off) {
	  onTime = on;
	  offTime = off;
	  blink();
     }

     void blink() {
	  state = BLINK;
	  nextTransition = millis() + onTime;
     }

     bool isBlinking() {
	  return state == BLINK;
     }

     void toggle() {
	  if (digitalRead(pin) == LOW) {
	       digitalWrite(pin, HIGH);
	  } else {
	       digitalWrite(pin, LOW);
	  }
     }

     void turnOn() {
	  state = ON;
	  digitalWrite(pin, HIGH);
     }

     void turnOff() {
	  state = OFF;
	  digitalWrite(pin, LOW);
     }
};
#endif
