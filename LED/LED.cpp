#include "LED.h"

LED::LED(int pin): 
	pin(pin), 
	onTime(onTime), 
	offTime(offTime) {
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
	state = OFF;
	powered = false;
	blinking = false;
}
     
void LED::update() {
	if (blinking == true) {
		if (millis() > nextTransition) {
			toggle();
			if (state == OFF)
			{
				nextTransition = millis() + offTime;
			}
			else if (state == ON)
			{
				nextTransition = millis() + onTime;
			}
		}
	}
}

void LED::blink(int on, int off) {
	onTime = on;
	offTime = off;
	blink();
}

void LED::blink() {
	blinking = true;
	nextTransition = millis() + onTime;
}

bool LED::isBlinking() {
	return blinking;
}

void LED::toggle() {
	if (state == ON) {
	   turnOff();
	} else if (state == OFF) {
	   turnOn();
	}
}

void LED::turnOn() {
	state = ON;
	digitalWrite(pin, HIGH);
}

void LED::turnOff() {
	state = OFF;
	digitalWrite(pin, LOW);
}

void LED::setup() {
	blink(500, 500);
}

void LED::loop() {
	update();
}
