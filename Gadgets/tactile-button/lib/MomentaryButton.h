#ifndef MOMENTARY_BUTTON_INCLUDED
#define MOMENTARY_BUTTON_INCLUDED

#include <Arduino.h>
#include <cstdio>

class MomentaryButton {

     int isDown;
     int pin;
     //bool state;
public:
     MomentaryButton(int pin): pin(pin) {
	  pinMode(pin, INPUT);
	  digitalWrite(pin, HIGH);
	  isDown = false;
	  //state = startState;
     }
     
     bool buttonPressed() {
	  if (!isDown && getValueFast()) {
	       isDown = true;
	       return true;
	  }
	  return false;
     }
     int buttonReleased() {
	  if (isDown && !getValue()) {
	       isDown = false;
	       return true;
	  }
	  return false;
     }
     int buttonDown() {
	  if (getValue()) {
	       isDown = true;
	  } else {
	       isDown = false;
	  }
	  return isDown;
     }
     
     int getValue() {
	  int v = getValueFast();
	  delay(1); // debounce
	  if (v == getValueFast()) {
	       return v;
	  } else {
	       return LOW;
	  }
     }

     int getValueFast() {
	  return !digitalRead(pin);
     }
};
#endif
