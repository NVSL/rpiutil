all:

	echo "Building SparkFun16x2SerLCD"
	swig -c++ -python SparkFun16x2SerLCD.i
	g++ -fPIC -Wall -Wextra -shared -lstdc++ -lrt -pthread -I../include/ serLCD.cpp -o libSparkFun16x2SerLCD.so
	g++ -fPIC -Wall -Wextra -shared SparkFun16x2SerLCD_wrap.cxx -o _SparkFun16x2SerLCD.so -L../ -L. -lstdc++ -lrt -pthread -larduPi -lSparkFun16x2SerLCD -I/usr/include/python2.7/ -lpython2.7  -I../include/ -L../lib/
	cp libSparkFun16x2SerLCD.so ../lib
	cp _SparkFun16x2SerLCD.so ../lib
	cp SparkFun16x2SerLCD.py ../lib
	cp serLCD.h ../include
	
clean:
	
	echo "Cleaning up SparkFun16x2SerLCD"
	rm -rf ../lib/SparkFun16x2SerLCD.py* SparkFun16x2SerLCD.py*
	rm -rf SparkFun16x2SerLCD_wrap*
	rm -rf ../lib/_SparkFun16x2SerLCD.so _SparkFun16x2SerLCD.so
	rm -rf ../lib/libSparkFun16x2SerLCD* libSparkFun16x2SerLCD*
