# ;
# Makefile:
#   arduinoPi - Arduino core library for RaspberryPi
###############################################################################
DYN_VERS_MAJ=1
DYN_VERS_MIN=0

VERSION=$(DYN_VERS_MAJ).$(DYN_VERS_MIN)
DESTDIR=$(GADGETRON_RASPI_PATH)
PREFIX=

#STATIC=libArduino.a
DYNAMIC=libArduino.so.$(VERSION)
PYTHON=_Arduino.so 
PYTHON_WRAPPER=Arduino_wrap.o

#DEBUG	= -g -O0
DEBUG	= -O2
CC	= g++
INCLUDE	= -I.
DEFS	= -D_GNU_SOURCE
CFLAGS	= $(DEBUG) $(DEFS) -Wformat=2 -Wall -Winline $(INCLUDE) -pipe -fPIC

LIBS    =

# Should not alter anything below this line
###############################################################################

SRC	=	 WString.cpp			\
		 Print.cpp				\
		 Stream.cpp				\
         WMath.cpp              \
         HardwareSerial.cpp     \
         wiring_shift.c         \
         wiringPulse.c          \
		 wiringPi.c             \
         softTone.c             \
         softPwm.c              \
         piHiPri.c

OBJ	= WString.o Print.o Stream.o WMath.o HardwareSerial.o wiring_shift.o \
      wiringPulse.o wiringPi.o softTone.o softPwm.o piHiPri.o

all:		$(DYNAMIC) $(PYTHON)

#static:		$(STATIC)

#$(STATIC):	$(OBJ)
#	@echo "[Link (Static)]"
#	@ar rcs $(STATIC) $(OBJ)
#	@ranlib $(STATIC)
#	@size   $(STATIC)

$(DYNAMIC):	$(OBJ)
	@echo "[Link (Dynamic)]" 
	@$(CC) -shared -Wl,-soname,libArduino.so -o libArduino.so.$(VERSION) -lpthread -lrt $(OBJ)

.cpp.o:
	@echo [Compile] $<
	@$(CC) -c $(CFLAGS) $< -o $@

.c.o:
	@echo [Compile] $<
	@$(CC) -c $(CFLAGS) $< -o $@

$(PYTHON): $(DYNAMIC) $(PYTHON_WRAPPER)
	@echo [Linking python binding]
	@$(CC) -shared -I/usr/include/python2.7 -I. libArduino.so.$(VERSION) Arduino_wrap.o -o _Arduino.so 

$(PYTHON_WRAPPER): Arduino.i
	@echo [Making python binding]
	@swig -c++ -python -I/usr/include Arduino.i
	@$(CC) -c $(CFLAGS) -I/usr/include/python2.7 Arduino_wrap.cxx

.PHONEY:	clean
clean:
	@echo "[Clean]"
	@rm -f $(OBJ) *~ core tags Makefile.bak libArduino.* Arduino.py* Arduino_wrap.* _Arduino.so

.PHONEY:	tags
tags:	$(SRC)
	@echo [ctags]
	@ctags $(SRC)

$(DESTDIR)$(PREFIX)/include/avr:
	@mkdir $(DESTDIR)$(PREFIX)/include/avr

.PHONEY:	install-headers
install-headers: $(DESTDIR)$(PREFIX)/include/avr
	@echo "[Install Headers]"
	@echo $(DESTDIR)$(PREFIX)/include
	@install -m 0755 -d		    	$(DESTDIR)$(PREFIX)/include
	@install -m 0644 avr/pgmspace.h		$(DESTDIR)$(PREFIX)/include/avr
	@install -m 0644 wiringPi.h		$(DESTDIR)$(PREFIX)/include
	@install -m 0644 Arduino.h		$(DESTDIR)$(PREFIX)/include
	@install -m 0644 Printable.h	$(DESTDIR)$(PREFIX)/include
	@install -m 0644 HardwareSerial.h	$(DESTDIR)$(PREFIX)/include
	@install -m 0644 Print.h		$(DESTDIR)$(PREFIX)/include
	@install -m 0644 Stream.h		$(DESTDIR)$(PREFIX)/include
	@install -m 0644 WCharacter.h	$(DESTDIR)$(PREFIX)/include
	@install -m 0644 WString.h		$(DESTDIR)$(PREFIX)/include

.PHONEY:	install
install:	$(DYNAMIC) $(PYTHON) install-headers
	@echo "[Install Dynamic Lib]"
	@echo $(DESTDIR)$(PREFIX)/lib
	@install -m 0755 -d						$(DESTDIR)$(PREFIX)/lib
	@install -m 0755 _Arduino.so			$(DESTDIR)$(PREFIX)/lib/python/_Arduino.so
	@install -m 0755 Arduino.py				$(DESTDIR)$(PREFIX)/lib/python/Arduino.py
	@install -m 0755 libArduino.so.$(VERSION)			$(DESTDIR)$(PREFIX)/lib/libArduino.so.$(VERSION)
	@ln -sf $(DESTDIR)$(PREFIX)/lib/libArduino.so.$(VERSION)	$(DESTDIR)/lib/libArduino.so
#	@ldconfig

#.PHONEY:	install-static
#install-static:	$(STATIC) install-headers
#	@echo "[Install Static Lib]"
#	@install -m 0755 -d			$(DESTDIR)$(PREFIX)/lib
#	@install -m 0755 libArduino.a		$(DESTDIR)$(PREFIX)/lib

.PHONEY:	uninstall
uninstall:
	@echo "[UnInstall]"
	@echo $(DESTDIR)$(PREFIX)
	@rm -rf $(DESTDIR)$(PREFIX)/include/avr
	@rm -f $(DESTDIR)$(PREFIX)/include/wiringPi.h
	@rm -f $(DESTDIR)$(PREFIX)/include/Arduino.h
	@rm -f $(DESTDIR)$(PREFIX)/include/Printable.h
	@rm -f $(DESTDIR)$(PREFIX)/include/HardwareSerial.h
	@rm -f $(DESTDIR)$(PREFIX)/include/Print.h
	@rm -f $(DESTDIR)$(PREFIX)/include/Stream.h
	@rm -f $(DESTDIR)$(PREFIX)/include/WCharacter.h
	@rm -f $(DESTDIR)$(PREFIX)/include/WString.h
	@rm -f $(DESTDIR)$(PREFIX)/lib/libArduino.*
	@rm -f $(DESTDIR)$(PREFIX)/lib/python/_Arduino.so
	@rm -f $(DESTDIR)$(PREFIX)/lib/python/Arduino.py*
	@rm -f $(DESTDIR)/lib/libArduino.*
#	@ldconfig

.PHONEY:	depend
depend:
	makedepend -Y $(SRC)

# DO NOT DELETE
WString.o: WString.h
Print.o: Arduino.h Print.h
Stream.o: Arduino.h Stream.h
HardwareSerial.o: Arduino.h Stream.h HardwareSerial.h
WMath.o: 
wiring_shift.o: Arduino.h
wiringPulse.o: Arduino.h
wiringPi.o: softTone.h softPwm.h wiringPi.h Arduino.h
softTone.o: wiringPi.h softTone.h
softPwm.o: softPwm.h wiringPi.h
piHiPri.o: wiringPi.h
