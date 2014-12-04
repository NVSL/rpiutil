# ;
# Makefile:
#   arduinoPi - SoftwareSerial core library for RaspberryPi
###############################################################################
DYN_VERS_MAJ=1
DYN_VERS_MIN=0

VERSION=$(DYN_VERS_MAJ).$(DYN_VERS_MIN)
DESTDIR=$(GADGETRON_RASPI_PATH)
PREFIX=

#STATIC=libSoftwareSerial.a
DYNAMIC=libSoftwareSerial.so.$(VERSION)
PYTHON=_SoftwareSerial.so 
PYTHON_WRAPPER=SoftwareSerial_wrap.o SoftwareSerial.py

#DEBUG	= -g -O0
DEBUG	= -O2
CC	= g++
INCLUDE	= -I. -I$(GADGETRON_RASPI_PATH)/include
DEFS	= -D_GNU_SOURCE
CFLAGS	= $(DEBUG) $(DEFS) -Wformat=2 -Wall -Winline $(INCLUDE) $(LIBS) -pipe -fPIC

LIBS    = -L$(GADGETRON_RASPI_PATH)/lib

# Should not alter anything below this line
###############################################################################

SRC	=	 SoftwareSerial.cpp

OBJ	= $(SRC:.cpp=.o)

all:		$(DYNAMIC) $(PYTHON)

#static:		$(STATIC)

#$(STATIC):	$(OBJ)
#	@echo "[Link (Static)]"
#	@ar rcs $(STATIC) $(OBJ)
#	@ranlib $(STATIC)
#	@size   $(STATIC)

$(DYNAMIC):	$(OBJ)
	@echo "[Link (Dynamic)]" 
	@$(CC) -shared -Wl,-soname,libSoftwareSerial.so -o libSoftwareSerial.so.$(VERSION) -lpthread -lArduino $(LIBS) $(OBJ)

.cpp.o:
	@echo [Compile] $<
	@$(CC) -c $(CFLAGS) $< -o $@

$(PYTHON): $(DYNAMIC) $(PYTHON_WRAPPER)
	@echo [Linking python binding]
	@$(CC) -shared -I/usr/include/python2.7 -I. libSoftwareSerial.so.$(VERSION) SoftwareSerial_wrap.o -o _SoftwareSerial.so 

$(PYTHON_WRAPPER): SoftwareSerial.i
	@echo [Making python binding]
	@swig -c++ -python -I/usr/include -I$(GADGETRON_RASPI_PATH)/include SoftwareSerial.i
	@$(CC) -c $(CFLAGS) -I/usr/include/python2.7 -I$(GADGETRON_RASPI_PATH)/include SoftwareSerial_wrap.cxx

.PHONEY:	clean
clean:
	@echo "[Clean]"
	@rm -f $(OBJ) *~ core tags Makefile.bak libSoftwareSerial.* SoftwareSerial.py* SoftwareSerial_wrap.* _SoftwareSerial.so

.PHONEY:	tags
tags:	$(SRC)
	@echo [ctags]
	@ctags $(SRC)


.PHONEY:	install-headers
install-headers:
	@echo "[Install Headers]"
	@install -m 0755 -d		    	$(DESTDIR)$(PREFIX)/include
	@install -m 0644 SoftwareSerial.h		$(DESTDIR)$(PREFIX)/include

.PHONEY:	install
install:	$(DYNAMIC) $(PYTHON) install-headers
	@echo "[Install Dynamic Lib]"
	@install -m 0755 -d						$(DESTDIR)$(PREFIX)/lib
	@install -m 0755 _SoftwareSerial.so			$(DESTDIR)$(PREFIX)/lib/python/_SoftwareSerial.so
	@install -m 0755 SoftwareSerial.py				$(DESTDIR)$(PREFIX)/lib/python/SoftwareSerial.py
	@install -m 0755 libSoftwareSerial.so.$(VERSION)			$(DESTDIR)$(PREFIX)/lib/libSoftwareSerial.so.$(VERSION)
	@ln -sf $(DESTDIR)$(PREFIX)/lib/libSoftwareSerial.so.$(VERSION)	$(DESTDIR)/lib/libSoftwareSerial.so
#	@ldconfig

#.PHONEY:	install-static
#install-static:	$(STATIC) install-headers
#	@echo "[Install Static Lib]"
#	@install -m 0755 -d			$(DESTDIR)$(PREFIX)/lib
#	@install -m 0755 libSoftwareSerial.a		$(DESTDIR)$(PREFIX)/lib

.PHONEY:	uninstall
uninstall:
	@echo "[UnInstall]"
	@rm -f $(DESTDIR)$(PREFIX)/include/SoftwareSerial.h
	@rm -f $(DESTDIR)$(PREFIX)/lib/libSoftwareSerial.*
	@rm -f $(DESTDIR)$(PREFIX)/lib/python/_SoftwareSerial.so
	@rm -f $(DESTDIR)$(PREFIX)/lib/python/SoftwareSerial.py*
#	@ldconfig

.PHONEY:	depend
depend:
	makedepend -Y $(SRC) $(SRC_I2C)

# DO NOT DELETE
SoftwareSerial.o: SoftwareSerial.h
