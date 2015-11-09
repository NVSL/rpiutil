#include "DistanceSensor.h"

DistanceSensor::DistanceSensor(int analog_pin){
    _pin = analog_pin;
}


void DistanceSensor::setup(){
    pinMode(_pin, INPUT);
}


int DistanceSensor::get_distance(){
    uint16_t sense = analogRead(_pin);

    if(sense > 900)
        return 0;
    if(sense < 12)
        return 100;

    return (18859/sense - 14) / 16;
}

