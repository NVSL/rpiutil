#include<stdio.h>
#include<wiringPi.h>
#include<MomentaryButton.h>
#include<LED.h>

MomentaryButton button(1);
LED led(4);

void setup() {
  printf("%d\n", random(123));
  int* gpioPinToWpi = new int[41];
  for(int i = -1; i++ < 40; ){
    int gpio = wpiPinToGpio(i);
    if( gpio >= 0 )
        gpioPinToWpi[ gpio ] = i;
  }
  for(int i = -1; i++ < 40; ){
    printf("%d,\t", gpioPinToWpi[ i ]);
  }
  printf("\n");
}


void loop() {
  button.buttonPressed();
  if (button.buttonReleased()) {
    led.toggle();
  }
  delay(1);
}
