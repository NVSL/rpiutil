%module DistanceSensor
%{

class DistanceSensor{
public:
    /* Make a new distance sensor that will be attached to the corresponding pin */
    DistanceSensor(int analog_pin);

    /* Call this before doing anything! */
    void setup();

    /* Get the distance (cm) that the sensor reads */
    int get_distance();
private:
    int _pin;

};

%}

class DistanceSensor{
public:
    /* Make a new distance sensor that will be attached to the corresponding pin */
    DistanceSensor(int analog_pin);

    /* Call this before doing anything! */
    void setup();

    /* Get the distance (cm) that the sensor reads */
    int get_distance();
private:
    int _pin;

};
