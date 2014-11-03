
default:
	$(MAKE) -C wiringPi/wiringPi install
	$(MAKE) -C arduino/hardware/arduino/cores/arduino install
	$(MAKE) -C arduino/libraries/Wire install

clean:
	$(MAKE) -C wiringPi/wiringPi clean
	$(MAKE) -C arduino/hardware/arduino/cores/arduino clean
	$(MAKE) -C arduino/libraries/Wire clean
