all:

	echo "Building DistanceSensor"
	swig -c++ -python DistanceSensor.i
	g++ -fPIC -Wall -Wextra -shared -lstdc++ -lrt -pthread  -I../include/ DistanceSensor.cpp -o libDistanceSensor.so
	g++ -fPIC -Wall -Wextra -shared DistanceSensor_wrap.cxx -o _DistanceSensor.so -L../ -L. -lstdc++ -lrt -pthread -larduPi -lDistanceSensor -I/usr/include/python2.7/ -lpython2.7  -I../include/ -L../lib/
	cp libDistanceSensor.so ../lib
	cp _DistanceSensor.so ../lib
	cp DistanceSensor.py ../lib
	cp DistanceSensor.h ../include
	
clean:
	
	echo "Cleaning up DistanceSensor"
	rm DistanceSensor.py*
	rm DistanceSensor_wrap*
	rm _DistanceSensor.so
	rm libDistanceSensor*
