all:

	echo "Building LED"
	swig -c++ -python LED.i
	g++ -fPIC -Wall -Wextra -shared -lstdc++ -lrt -pthread -I../include/ LED.cpp -o libLED.so
	g++ -fPIC -Wall -Wextra -shared LED_wrap.cxx -o _LED.so -L../ -L. -lstdc++ -lrt -pthread -larduPi -lLED -I/usr/include/python2.7/ -lpython2.7  -I../include/ -L../lib/
	cp libLED.so ../lib
	cp _LED.so ../lib
	cp LED.py ../lib
	cp LED.h ../include
	
clean:
	
	echo "Cleaning up LED"
	rm -rf ../lib/LED.py* LED.py*
	rm -rf LED_wrap*
	rm -rf ../lib/_LED.so _LED.so
	rm -rf ../lib/libLED* libLED*
