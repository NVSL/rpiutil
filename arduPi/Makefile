all:
	echo "Building arduPi"
	swig -c++ -python arduPi.i
	g++ -fPIC -Wall -Wextra -shared -lstdc++ -lrt -pthread arduPi.cpp -o libarduPi.so
	g++ -fPIC -Wall -Wextra -shared arduPi_wrap.cxx -o _arduPi.so -L. -lstdc++ -lrt -pthread -larduPi -I/usr/include/python2.7/ -lpython2.7
	cp libarduPi.so ../lib
	cp _arduPi.so ../lib
	cp arduPi.py ../lib
	cp arduPi.h ../include

clean:
	echo "Cleaning up arduPi"
	rm ../lib/arduPi.py*
	rm arduPi_wrap*
	rm ../lib/_arduPi.so
	rm ../lib/libarduPi*
