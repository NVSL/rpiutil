#include "Arduino.h"

/* Measures the length (in microseconds) of a pulse on the pin; state is HIGH
 * or LOW, the type of pulse to measure.  Works on pulses from 2-3 microseconds
 * to 3 minutes in length, but must be called at least a few dozen microseconds
 * before the start of the pulse. */
unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout)
{
    unsigned long start = micros();
    while (digitalRead(pin) == state){
        if(micros() - start >= timeout)
            return 0;
    }

    start = micros();
    while (digitalRead(pin) != state){
        if(micros() - start >= timeout)
            return 0;
    }

    start = micros();
    while (digitalRead(pin) == state){
        if(micros() - start >= timeout)
            return 0;
    }
    
    return micros() - start;
}
