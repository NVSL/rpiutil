
default:
	true
all:
	mkdir -p ${ARDUPI_HOME}/lib
	mkdir -p ${ARDUPI_HOME}/include
	$(MAKE) -C arduPi
	$(MAKE) -C LED
	$(MAKE) -C SparkFun16x2SerLCD
	$(MAKE) -C DistanceSensor

clean:
	$(MAKE) -C arduPi clean
	$(MAKE) -C LED clean
	$(MAKE) -C SparkFun16x2SerLCD clean
	$(MAKE) -C DistanceSensor clean
	./shellutils/clean.sh

test:
	true	
