# ;
# Makefile:
#   arduinoPi - SPI core library for RaspberryPi
###############################################################################
DYN_VERS_MAJ=1
DYN_VERS_MIN=0

VERSION=$(DYN_VERS_MAJ).$(DYN_VERS_MIN)
DESTDIR=$(GADGETRON_RASPI_PATH)
PREFIX=

#STATIC=libSPI.a
DYNAMIC=libSPI.so.$(VERSION)
PYTHON=_SPI.so
PYTHON_WRAPPER=SPI_wrap.o SPI.py

#DEBUG	= -g -O0
DEBUG	= -O2
CC	= g++
INCLUDE	= -I. -I$(GADGETRON_RASPI_PATH)/include
DEFS	= -D_GNU_SOURCE
CFLAGS	= $(DEBUG) $(DEFS) -Wformat=2 -Wall -Winline $(INCLUDE) $(LIBS) -pipe -fPIC

LIBS    = -L$(GADGETRON_RASPI_PATH)/lib

# Should not alter anything below this line
###############################################################################

SRC	=	 SPI.cpp

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
	@$(CC) -shared -Wl,-soname,libSPI.so -o libSPI.so.$(VERSION) -lpthread -lArduino $(LIBS) $(OBJ)

.cpp.o:
	@echo [Compile] $<
	@$(CC) -c $(CFLAGS) $< -o $@

$(PYTHON): $(DYNAMIC) $(PYTHON_WRAPPER)
	@echo [Linking python binding]
	@$(CC) -shared -I/usr/include/python2.7 -I. libSPI.so.$(VERSION) SPI_wrap.o -o _SPI.so 

$(PYTHON_WRAPPER): SPI.i
	@echo [Making python binding]
	@swig -c++ -python -I/usr/include SPI.i
	@$(CC) -c $(CFLAGS) -I/usr/include/python2.7 SPI_wrap.cxx

.PHONEY:	clean
clean:
	@echo "[Clean]"
	@rm -f $(OBJ) *~ core tags Makefile.bak libSPI.* SPI.py* SPI_wrap.* _SPI.so

.PHONEY:	tags
tags:	$(SRC)
	@echo [ctags]
	@ctags $(SRC)


.PHONEY:	install-headers
install-headers:
	@echo "[Install Headers]"
	@install -m 0755 -d		    	$(DESTDIR)$(PREFIX)/include
	@install -m 0644 SPI.h		$(DESTDIR)$(PREFIX)/include

.PHONEY:	install
install:	$(DYNAMIC) $(PYTHON) install-headers
	@echo "[Install Dynamic Lib]"
	@install -m 0755 -d						$(DESTDIR)$(PREFIX)/lib
	@install -m 0755 _SPI.so			$(DESTDIR)$(PREFIX)/lib/python/_SPI.so
	@install -m 0755 SPI.py				$(DESTDIR)$(PREFIX)/lib/python/SPI.py
	@install -m 0755 libSPI.so.$(VERSION)			$(DESTDIR)$(PREFIX)/lib/libSPI.so.$(VERSION)
	@ln -sf $(DESTDIR)$(PREFIX)/lib/libSPI.so.$(VERSION)	$(DESTDIR)/lib/libSPI.so
#	@ldconfig

#.PHONEY:	install-static
#install-static:	$(STATIC) install-headers
#	@echo "[Install Static Lib]"
#	@install -m 0755 -d			$(DESTDIR)$(PREFIX)/lib
#	@install -m 0755 libSPI.a		$(DESTDIR)$(PREFIX)/lib

.PHONEY:	uninstall
uninstall:
	@echo "[UnInstall]"
	@rm -f $(DESTDIR)$(PREFIX)/include/SPI.h
	@rm -f $(DESTDIR)$(PREFIX)/lib/libSPI.*
	@rm -f $(DESTDIR)$(PREFIX)/lib/python/_SPI.so
	@rm -f $(DESTDIR)$(PREFIX)/lib/python/SPI.py*
#	@ldconfig

.PHONEY:	depend
depend:
	makedepend -Y $(SRC) $(SRC_I2C)

# DO NOT DELETE
SPI.o: SPI.h
