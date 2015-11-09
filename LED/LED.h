#ifndef LED_INCLUDED
#define LED_INCLUDED

#include "arduPi.h"

class LED {
	enum {ON, OFF};

	int pin;
	int onTime;
	int offTime;
	int state;
	bool powered;
	bool blinking;
	unsigned long nextTransition;

public:
	LED(int);
	void blink(int on, int off);
	void blink();
	bool isBlinking();
	void toggle();

	void turnOn();
	void update();
	void turnOff();
	void setup();

	void loop();
};
#endif
