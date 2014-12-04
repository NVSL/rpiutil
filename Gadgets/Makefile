all: libs

LIBS =  tactile-button          \
        LED                     \
        Adafruit_GFX            \
        Adafruit_Sensor			\
        Adafruit_CAP1188        \
        Adafruit_LEDBackpack    \
        Adafruit_LSM9DS0

.PHONY: libs
libs:
	for i in $(LIBS); do if  [ -f $$i/Makefile ]; then (echo $$i; $(MAKE) -C $$i default);fi;done

.PHONY: clean
clean:
	for i in $(LIBS); do if  [ -f $$i/Makefile ]; then (echo $$i; $(MAKE) -C $$i clean);fi;done

