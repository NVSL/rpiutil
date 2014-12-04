#include<stdio.h>
#include<MomentaryButton.h>

MomentaryButton button(18);

void setup() {
}

void loop() {
  if (button.buttonPressed()) {
       printf("Button pressed\n");
  }
  if (button.buttonReleased()) {
       printf("Button released\n");
  }
  
  if (button.buttonDown()) {
       printf("Button is down\n");
  }
  delay(10);
}
