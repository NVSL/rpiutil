LIBDIR="/home/gadgetron/Gadgetron/Gadgets/Designs/GadgetronSketchBook/libraries"

default:

build:

all: install

.PHONEY: include
include:
	@mkdir include

.PHONEY: lib
lib:
	@mkdir lib
	@mkdir lib/python

.PHONEY: serial
serial: inittab cmdline.txt
	@disable_ttyAMA0

.PHONEY: install
install: include lib
	@echo "Install libArduino"
	$(MAKE) -C arduino/hardware/arduino/cores/arduino uninstall
	$(MAKE) -C arduino/hardware/arduino/cores/arduino clean
	$(MAKE) -C arduino/hardware/arduino/cores/arduino install
	@echo "Install libWire"
	$(MAKE) -C arduino/libraries/Wire uninstall
	$(MAKE) -C arduino/libraries/Wire clean
	$(MAKE) -C arduino/libraries/Wire install
	@echo "Install libSPI"
	$(MAKE) -C arduino/libraries/SPI uninstall
	$(MAKE) -C arduino/libraries/SPI clean
	$(MAKE) -C arduino/libraries/SPI install
	@echo "Install libSoftwareSerial"
	$(MAKE) -C arduino/libraries/SoftwareSerial uninstall
	$(MAKE) -C arduino/libraries/SoftwareSerial clean
	$(MAKE) -C arduino/libraries/SoftwareSerial install
	@echo "Install libLiquidCrystal"
	$(MAKE) -C arduino/libraries/LiquidCrystal uninstall
	$(MAKE) -C arduino/libraries/LiquidCrystal clean
	$(MAKE) -C arduino/libraries/LiquidCrystal install
	@echo "Install libLED"
	$(MAKE) -C libraries/LED uninstall
	$(MAKE) -C libraries/LED clean
	$(MAKE) -C libraries/LED install

.PHONEY: clean
clean:
	@echo "Uninstall libArduino"
	$(MAKE) -C arduino/hardware/arduino/cores/arduino uninstall
	$(MAKE) -C arduino/hardware/arduino/cores/arduino clean
	@echo "Uninstall libWire"
	$(MAKE) -C arduino/libraries/Wire uninstall
	$(MAKE) -C arduino/libraries/Wire clean
	@echo "Uninstall libSPI"
	$(MAKE) -C arduino/libraries/SPI uninstall
	$(MAKE) -C arduino/libraries/SPI clean
	@echo "Uninstall libSoftwareSerial"
	$(MAKE) -C arduino/libraries/SoftwareSerial uninstall
	$(MAKE) -C arduino/libraries/SoftwareSerial clean
	@echo "Uninstall libLiquidCrystal"
	$(MAKE) -C arduino/libraries/LiquidCrystal uninstall
	$(MAKE) -C arduino/libraries/LiquidCrystal clean
	@echo "Uninstall libLED"
	if [ -d $(LIBDIR) ]; then \
		$(MAKE) -C libraries/LED uninstall; \
		$(MAKE) -C libraries/LED clean; \
	fi
	@rm -rf lib
	@rm -rf include

test:
	true
