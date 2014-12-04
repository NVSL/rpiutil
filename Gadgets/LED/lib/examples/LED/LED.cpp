#include"LED.h"
#include<stdio.h>

LED led(4);

void setup() {
     led.turnOn();
     delay(10);
     led.turnOff();
     delay(1000);
     led.blink(100, 900);
}

void loop() {
     led.update();
     delay(1);
}
