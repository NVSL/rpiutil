all: install

.PHONEY: include
include:
	@mkdir include

.PHONEY: lib
lib:
	@mkdir lib

.PHONEY: install
install: include lib
	@echo "Installing wiringPi"
	@cd wiringPi; ./build uninstall; ./build
	@echo "Install libArduino"
	$(MAKE) -C arduino/hardware/arduino/cores/arduino uninstall
	$(MAKE) -C arduino/hardware/arduino/cores/arduino install
	@echo "Install libWire"
	$(MAKE) -C arduino/libraries/Wire uninstall
	$(MAKE) -C arduino/libraries/Wire install
	@echo "Install libSPI"
	$(MAKE) -C arduino/libraries/SPI uninstall
	$(MAKE) -C arduino/libraries/SPI install

clean:
	@echo "Uninstall wiringPi"
	@cd wiringPi; ./build uninstall; ./build clean
	@echo "Uninstall libArduino"
	$(MAKE) -C arduino/hardware/arduino/cores/arduino uninstall
	$(MAKE) -C arduino/hardware/arduino/cores/arduino clean
	@echo "Uninstall libWire"
	$(MAKE) -C arduino/libraries/Wire uninstall
	$(MAKE) -C arduino/libraries/Wire clean
	@echo "Uninstall libSPI"
	$(MAKE) -C arduino/libraries/SPI uninstall
	$(MAKE) -C arduino/libraries/SPI clean
	@rm -rf lib
	@rm -rf include
